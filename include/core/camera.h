#ifndef CORE_CAMERA_H
#define CORE_CAMERA_H

#include <math.h>

#include <core/ray.h>
#include <maths/vec3.h>
#include <maths/utils.h>

typedef struct {
    vec3 origin;
    vec3 lower_left_corner;
    vec3 horizontal, vertical;
    vec3 u, v, w;
    double lens_radius;
} camera;

camera* camera_setup(
    vec3* lookfrom, vec3* lookat, vec3* vup,
    double* vfov, double* aspect_ratio, double* aperture, double* focus_dist,
    camera* cam
);

ray* camera_ray(double* s, double* t, camera* cam, ray* r);

#endif