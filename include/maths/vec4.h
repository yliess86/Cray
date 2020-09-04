#ifndef MATHS_VEC4_H
#define MATHS_VEC4_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double x, y, z, w;
} vec4;

vec4 vec4_zeros ();
vec4 vec4_ones  ();
vec4 vec4_scalar(double s);

void vec4_print(vec4* v);

double vec4_sqr_length (vec4* v);
double vec4_length     (vec4* v);
double vec4_dot        (vec4* a, vec4* b);

vec4* vec4_neg  (vec4* v, vec4* dest);
vec4* vec4_add  (vec4* a, vec4* b, vec4* dest);
vec4* vec4_sub  (vec4* a, vec4* b, vec4* dest);
vec4* vec4_mul  (vec4* a, vec4* b, vec4* dest);
vec4* vec4_div  (vec4* a, vec4* b, vec4* dest);

vec4* vec4_add_scalar  (vec4* v, double* s, vec4* dest);
vec4* vec4_sub_scalar  (vec4* v, double* s, vec4* dest);
vec4* vec4_mul_scalar  (vec4* v, double* s, vec4* dest);
vec4* vec4_div_scalar  (vec4* v, double* s, vec4* dest);

vec4* vec4_normalize(vec4* v, vec4* dest);

#endif