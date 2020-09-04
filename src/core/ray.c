#include <core/ray.h>

vec3* ray_at(ray* r, double* t, vec3* dest) {
    vec3_mul_scalar(&r->direction, t, dest);
    vec3_add(&r->origin, dest, dest);
    return dest; 
}

color* ray_color(ray* r, color* c) {
    sphere s = { vec3_zeros(), 1.5 };
    double t = ray_hit_sphere(&s, r);
    if(t > 0.0) {
        vec3 hit_point;
        ray_at(r, &t, &hit_point);

        vec3 normal;
        double one  = 1.0;
        double half = 0.5;

        vec3_sub(&hit_point, &s.position, &normal);
        vec3_normalize(&normal, &normal);
        
        vec3_add_scalar(&normal, &one, &normal);
        vec3_mul_scalar(&normal, &half, &normal);
        
        *c = color_vec3(&normal);
        return c;
    }

    vec3 sky = { 0.5, 0.7, 1.0 };
    color sky_color = color_vec3(&sky);
    color white = WHITE;
    color_lerp(&white, &sky_color, 0.5 * (r->direction.y + 1.0), c);
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