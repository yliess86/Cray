#ifndef CORE_RAY_H
#define CORE_RAY_H

#include <stdbool.h>
#include <math.h>

#include <core/color.h>
#include <core/primitives.h>
#include <maths/vec3.h>

typedef struct {
    vec3 origin, direction;
} ray;

vec3*  ray_at   (ray* r, double* t, vec3* dest);
color* ray_color(ray* r, color* c);

double ray_hit_sphere(sphere* s, ray* r);

#endif