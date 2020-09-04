#include <core/ray.h>

vec3* ray_at(ray* r, double* t, vec3* dest) {
    return vec3_mul_scalar(&r->direction, t, dest); 
}

color* ray_color(ray* r, color* c) {
    sphere s = { vec3_zeros(), 1.5 };
    double t = ray_hit_sphere(&s, r);
    if(t > 0.0) {
        vec3 hit_point, normal, col;
        double one  = 1.0;
        double half = 0.5;
        ray_at(r, &t, &hit_point);
        vec3_sub(&hit_point, &s.position, &normal);
        vec3_normalize(&normal, &normal);
        vec3_add_scalar(&normal, &one, &col);
        vec3_mul_scalar(&col, &half, &col);
        *c = color_vec3(&normal);
        return c;
    }

    vec3 cv = { 0.5, 0.7, 1.0 };
    *c = color_vec3(&cv);
    return c;
}

double ray_hit_sphere(sphere* s, ray* r) {
    vec3 oc;
    vec3_sub(&r->origin, &s->position, &oc);

    double a = vec3_sqr_length(&r->direction);
    double half_b = vec3_dot(&oc, &r->direction);
    double c = vec3_sqr_length(&oc) - s->radius * s->radius;
    double discriminant = half_b * half_b - a * c;
    
    if (discriminant < 0)
        return -1.0;
    return (-half_b - sqrt(discriminant)) / a;
}