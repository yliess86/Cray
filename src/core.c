#include <core.h>

// ============ [START] RAY METHODS ============
vec3* ray_at(ray* r, double* t, vec3* dest) {
    vec3_mul_scalar(&r->direction, t, dest);
    vec3_add(&r->origin, dest, dest);
    return dest;
}

vec3* ray_color(ray* r, world* w, vec3* c) {
    hit h;
    double t_min = 0;
    double t_max = (double)INFINITY;
    if(world_hit(w, r, &t_min, &t_max, &h)) {
        double half = 0.5;
        *c = vec3_ones();
        vec3_add(&h.normal, c, c);
        vec3_mul_scalar(c, &half, c);
        return c;
    }

    vec3 sky   = { 0.5, 0.7, 1.0 };
    vec3 white = vec3_ones();
    double t = 0.5 * (r->direction.y + 1.0);
    vec3_lerp(&sky, &white, &t, c);
    return c;
}

void ray_hit_face_normal(ray* r, hit* h) {
    h->front_face = vec3_dot(&r->direction, &h->normal) < 0;
    if(!h->front_face)
        vec3_neg(&h->normal, &h->normal);
}
// ============ [END] RAY METHODS ============

// ============ [START] SPHERE METHODS ============
sphere* sphere_create(vec3* position, double* radius, sphere* dest) {
    dest->position = *position;
    dest->radius = *radius;
    dest->type = SPHERE;
    return dest;
}

bool sphere_ray_hit(sphere* s, ray* r, double* t_min, double* t_max, hit* h) {
    vec3 oc;
    vec3_sub(&r->origin, &s->position, &oc);

    double a = vec3_sqr_length(&r->direction);
    double half_b = vec3_dot(&oc, &r->direction);
    double c = vec3_sqr_length(&oc) - s->radius * s->radius;
    double discriminant = half_b * half_b - a * c;
    
    if(discriminant > 0) {
        double root = sqrt(discriminant);

        double temp = (-half_b - root) / a;
        if(temp < *t_max && temp > *t_min) {
            h->t = temp;
            ray_at(r, &h->t, &h->point);
            vec3_sub(&h->point, &s->position, &h->normal);
            vec3_div_scalar(&h->normal, &s->radius, &h->normal);
            ray_hit_face_normal(r, h);
            return true;
        }

        temp = (-half_b + root) / a;
        if(temp < *t_max && temp > *t_min) {
            h->t = temp;
            ray_at(r, &h->t, &h->point);
            vec3_sub(&h->point, &s->position, &h->normal);
            vec3_div_scalar(&h->normal, &s->radius, &h->normal);
            ray_hit_face_normal(r, h);
            return true;
        }
    }

    return false;
}
// ============ [END] SPHERE METHODS ============

// ============ [START] WORLD METHODS ============
world* world_create(world* w) {
    w->spheres = (sphere*)malloc(2 * sizeof(sphere));

    vec3 p1 = { 0,    0,  0 }; double r1 =   2.0;
    vec3 p2 = { 0, -102,  0 }; double r2 = 100.0;

    sphere_create(&p1, &r1, &w->spheres[0]);
    sphere_create(&p2, &r2, &w->spheres[1]);
    w->n_spheres = 2;

    return w;
}

world* world_free(world* w) {
    free(w->spheres);
    w->n_spheres = 0;

    w = NULL;
    return w;
}

bool world_hit(world* w, ray* r, double* t_min, double* t_max, hit* h) {
    hit temp_h;
    bool hitted = false;
    double closest = *t_max;

    for(uint32_t i = 0; i < w->n_spheres; i++) {
        if(sphere_ray_hit(&w->spheres[i], r, t_min, &closest, &temp_h)) {
            hitted = true;
            closest = temp_h.t;
            *h = temp_h;
        }
    }

    return hitted;
}
// ============ [END] WORLD METHODS ============

// ============ [START] CAMERA METHODS ============
camera* camera_setup(
    vec3* lookfrom, vec3* lookat, vec3* vup,
    double* vfov, double* aspect_ratio, double* aperture, double* focus_dist,
    camera* cam
) {
    double half = 0.5;
    double theta = degree_to_radian(*vfov);
    double h = tan(theta * half);
    double viewport_height = 2.0 * h;
    double viewport_width = *aspect_ratio * viewport_height;

    vec3_sub(lookfrom, lookat, &cam->w);
    vec3_normalize(&cam->w, &cam->w);
    vec3_cross(vup, &cam->w, &cam->u);
    vec3_normalize(&cam->u, &cam->u);
    vec3_cross(&cam->w, &cam->u, &cam->v);

    double su = *focus_dist * viewport_width;
    double sv = *focus_dist * viewport_height;
    
    cam->origin = *lookfrom;
    vec3_mul_scalar(&cam->u, &su, &cam->horizontal);
    vec3_mul_scalar(&cam->v, &sv, &cam->vertical);
    
    vec3 half_horizontal, half_vertical;
    vec3 focus_w;

    vec3_mul_scalar(&cam->horizontal, &half, &half_horizontal);
    vec3_mul_scalar(&cam->vertical, &half, &half_vertical);
    vec3_mul_scalar(&cam->w, focus_dist, &focus_w);
    
    cam->lower_left_corner = cam->origin;
    vec3_sub(&cam->lower_left_corner, &half_horizontal, &cam->lower_left_corner);
    vec3_sub(&cam->lower_left_corner, &half_vertical, &cam->lower_left_corner);
    vec3_sub(&cam->lower_left_corner, &focus_w, &cam->lower_left_corner);

    cam->lens_radius = *aperture * half;

    return cam;
}

ray* camera_ray(double* s, double* t, camera* cam, ray* r) {
    vec3 rd = vec3_random_uint_disk();
    vec3_mul_scalar(&rd, &cam->lens_radius, &rd);

    vec3 u_rdx, v_rdy, offset;
    vec3_mul_scalar(&cam->u, &rd.x, &u_rdx);
    vec3_mul_scalar(&cam->v, &rd.y, &v_rdy);
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

    return r;
}
// ============ [END] CAMERA METHODS ============