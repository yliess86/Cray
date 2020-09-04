#include <core/camera.h>

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
    vec3 rd, u_rdx, v_rdy, offset;
    vec3 rand = vec3_random_uint_disk();
    vec3_mul_scalar(&rand, &cam->lens_radius, &rd);
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