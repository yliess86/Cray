#include <core.h>

// ============ [START] RAY METHODS ============
void ray_at(ray* r, double t, vec3* dest) {
    vec3_mul_scalar(&r->direction, t, dest);
    vec3_add(&r->origin, dest, dest);
}

vec3 ray_color(ray* r, world* w, int depth) {
    vec3 col = vec3_zeros();
    if(depth <= 0)
        return col;

    hit h;
    if(world_hit(w, r, 0.001, (double)INFINITY, &h)) {
        ray r_scattered;
        vec3 attenuation;
        if(material_scatter(h.m, r, &h, &attenuation, &r_scattered)) {
            col = ray_color(&r_scattered, w, depth - 1);
            vec3_mul(&col, &attenuation, &col);
            return col;
        }
        return col;
    }

    vec3 sky   = { 0.5, 0.7, 1.0 };
    vec3 white = vec3_ones();
    double t = 0.5 * (r->direction.y + 1.0);
    vec3_lerp(&sky, &white, t, &col);
    return col;
}

void ray_hit_face_normal(ray* r, hit* h) {
    h->front_face = vec3_dot(&r->direction, &h->normal) < 0;
    if(!h->front_face)
        vec3_neg(&h->normal, &h->normal);
}
// ============ [END] RAY METHODS ============

// ============ [START] MATERIAL METHODS ============
void lambertian_create(vec3* albedo, material* dest) {
    lambertian* l = (lambertian*)malloc(sizeof(lambertian));
    l->albedo = *albedo;
    dest->type = LAMBERTIAN;
    dest->data.l = l;
}

void metalic_create(vec3* albedo, material* dest) {
    metalic* m = (metalic*)malloc(sizeof(metalic));
    m->albedo = *albedo;
    dest->type = METALIC;
    dest->data.m = m;
}

bool lambertian_scatter(lambertian* l, hit* h, vec3* attenuation, ray* r_scattered) {
    vec3 scatter_dir = vec3_random_unit_vector();
    vec3_add(&h->normal, &scatter_dir, &scatter_dir);
    vec3_normalize(&scatter_dir, &scatter_dir);
    *r_scattered = (ray){ h->point, scatter_dir };
    *attenuation = l->albedo;
    return true;
}

bool metalic_scatter(metalic* m, ray* r_in, hit* h, vec3* attenuation, ray* r_scattered) {
    vec3 reflected, unit_dir;
    vec3_normalize(&r_in->direction, &unit_dir);
    vec3_reflect(&unit_dir, &h->normal, &reflected);
    *r_scattered = (ray){ h->point, reflected };
    *attenuation = m->albedo;
    return vec3_dot(&r_scattered->direction, &h->normal) > 0;
}

bool material_scatter(material* m, ray* r_in, hit* h, vec3* attenuation, ray* r_scattered) {
    switch(m->type)
    {
        case LAMBERTIAN:
            return lambertian_scatter(m->data.l, h, attenuation, r_scattered);
        case METALIC:
            return metalic_scatter(m->data.m, r_in, h, attenuation, r_scattered);
    }
    
    return true;
}

// ============ [END] MATERIAL METHODS ============

// ============ [START] SPHERE METHODS ============
void sphere_create(vec3* position, double radius, material* m, sphere* dest) {
    dest->position = *position;
    dest->radius = radius;
    dest->m = m;
}

bool sphere_ray_hit(sphere* s, ray* r, double t_min, double t_max, hit* h) {
    vec3 oc;
    vec3_sub(&r->origin, &s->position, &oc);

    double a = vec3_sqr_length(&r->direction);
    double half_b = vec3_dot(&oc, &r->direction);
    double c = vec3_sqr_length(&oc) - s->radius * s->radius;
    double discriminant = half_b * half_b - a * c;
    
    if(discriminant > 0) {
        double root = sqrt(discriminant);

        double temp = (-half_b - root) / a;
        if(temp < t_max && temp > t_min) {
            h->m = s->m;
            h->t = temp;
            ray_at(r, h->t, &h->point);
            vec3_sub(&h->point, &s->position, &h->normal);
            vec3_div_scalar(&h->normal, s->radius, &h->normal);
            ray_hit_face_normal(r, h);
            return true;
        }

        temp = (-half_b + root) / a;
        if(temp < t_max && temp > t_min) {
            h->m = s->m;
            h->t = temp;
            ray_at(r, h->t, &h->point);
            vec3_sub(&h->point, &s->position, &h->normal);
            vec3_div_scalar(&h->normal, s->radius, &h->normal);
            ray_hit_face_normal(r, h);
            return true;
        }
    }

    return false;
}
// ============ [END] SPHERE METHODS ============

// ============ [START] WORLD METHODS ============
void world_create(world* w) {
    w->objects = (object*)calloc(ARRAY_DEFAULT, sizeof(object));
    w->n_objects = 0;
    w->n_max_objects = ARRAY_DEFAULT;
}

void world_add_sphere(world* w, sphere* s) {
    if(w->n_objects == w->n_max_objects) {
        uint32_t n_max_objects = w->n_max_objects * ARRAY_GROWTH;
        uint32_t new_size = n_max_objects * sizeof(object);
        w->objects = (object*)realloc(w->objects, new_size);
        w->n_max_objects = n_max_objects;
    }
    w->objects[w->n_objects] = (object){ SPHERE, { s } };
    w->n_objects++;
}

void world_free(world* w) {
    free(w->objects);
    w->n_objects = 0;
    w->n_max_objects = ARRAY_DEFAULT;
    w = NULL;
}

bool world_hit(world* w, ray* r, double t_min, double t_max, hit* h) {
    hit temp_h;
    bool hitted = false;
    double closest = t_max;

    for(uint32_t i = 0; i < w->n_objects; i++) {
        object o = w->objects[i];
        switch(w->objects[i].type) {
            case SPHERE:
                if(sphere_ray_hit(o.data.s, r, t_min, closest, &temp_h)) {
                    hitted = true;
                    closest = temp_h.t;
                    *h = temp_h;
                }
                break;
        }
    }

    return hitted;
}
// ============ [END] WORLD METHODS ============

// ============ [START] CAMERA METHODS ============
void camera_setup(
    vec3* lookfrom, vec3* lookat, vec3* vup,
    double vfov, double aspect_ratio, double aperture, double focus_dist,
    camera* cam
) {
    double theta = degree_to_radian(vfov);
    double h = tan(theta * 0.5);
    double viewport_height = 2.0 * h;
    double viewport_width = aspect_ratio * viewport_height;

    vec3_sub(lookfrom, lookat, &cam->w);
    vec3_normalize(&cam->w, &cam->w);
    vec3_cross(vup, &cam->w, &cam->u);
    vec3_normalize(&cam->u, &cam->u);
    vec3_cross(&cam->w, &cam->u, &cam->v);

    double su = focus_dist * viewport_width;
    double sv = focus_dist * viewport_height;
    
    cam->origin = *lookfrom;
    vec3_mul_scalar(&cam->u, su, &cam->horizontal);
    vec3_mul_scalar(&cam->v, sv, &cam->vertical);
    
    vec3 half_horizontal, half_vertical;
    vec3_mul_scalar(&cam->horizontal, 0.5, &half_horizontal);
    vec3_mul_scalar(&cam->vertical, 0.5, &half_vertical);
    
    vec3 focus_w;
    vec3_mul_scalar(&cam->w, focus_dist, &focus_w);
    
    cam->lower_left_corner = cam->origin;
    vec3_sub(&cam->lower_left_corner, &half_horizontal, &cam->lower_left_corner);
    vec3_sub(&cam->lower_left_corner, &half_vertical, &cam->lower_left_corner);
    vec3_sub(&cam->lower_left_corner, &focus_w, &cam->lower_left_corner);

    cam->lens_radius = aperture * 0.5;
}

void camera_ray(double s, double t, camera* cam, ray* r) {
    vec3 rd = vec3_random_unit_disk();
    vec3_mul_scalar(&rd, cam->lens_radius, &rd);

    vec3 u_rdx, v_rdy, offset;
    vec3_mul_scalar(&cam->u, rd.x, &u_rdx);
    vec3_mul_scalar(&cam->v, rd.y, &v_rdy);
    vec3_add(&u_rdx, &v_rdy, &offset);

    vec3_add(&cam->origin, &offset, &r->origin);

    vec3 s_horizontal, t_vertical;
    vec3_mul_scalar(&cam->horizontal, s, &s_horizontal);
    vec3_mul_scalar(&cam->vertical, t, &t_vertical);
    
    r->direction = cam->lower_left_corner;
    vec3_add(&r->direction, &s_horizontal, &r->direction);
    vec3_add(&r->direction, &t_vertical, &r->direction);
    vec3_sub(&r->direction, &cam->origin, &r->direction);
    vec3_sub(&r->direction, &offset, &r->direction);
    vec3_normalize(&r->direction, &r->direction);
}
// ============ [END] CAMERA METHODS ============