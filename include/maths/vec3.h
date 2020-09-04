#ifndef MATHS_VEC3_H
#define MATHS_VEC3_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <maths/utils.h>

typedef struct {
    double x, y, z;
} vec3;

vec3 vec3_zeros           ();
vec3 vec3_ones            ();
vec3 vec3_scalar          (double s);
vec3 vec3_random_uint_disk();

void vec3_print(vec3* v);

double vec3_sqr_length(vec3* v);
double vec3_length    (vec3* v);
double vec3_dot       (vec3* a, vec3* b);

vec3* vec3_neg  (vec3* v, vec3* dest);
vec3* vec3_add  (vec3* a, vec3* b, vec3* dest);
vec3* vec3_sub  (vec3* a, vec3* b, vec3* dest);
vec3* vec3_mul  (vec3* a, vec3* b, vec3* dest);
vec3* vec3_div  (vec3* a, vec3* b, vec3* dest);
vec3* vec3_cross(vec3* a, vec3* b, vec3* dest);

vec3* vec3_add_scalar  (vec3* v, double* s, vec3* dest);
vec3* vec3_sub_scalar  (vec3* v, double* s, vec3* dest);
vec3* vec3_mul_scalar  (vec3* v, double* s, vec3* dest);
vec3* vec3_div_scalar  (vec3* v, double* s, vec3* dest);

vec3* vec3_normalize(vec3* v, vec3* dest);

#endif