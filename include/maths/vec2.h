#ifndef MATHS_VEC2_H
#define MATHS_VEC2_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double x, y;
} vec2;

vec2 vec2_zeros ();
vec2 vec2_ones  ();
vec2 vec2_scalar(double s);

void vec2_print(vec2* v);

double vec2_sqr_length (vec2* v);
double vec2_length     (vec2* v);
double vec2_dot        (vec2* a, vec2* b);

vec2* vec2_neg  (vec2* v, vec2* dest);
vec2* vec2_add  (vec2* a, vec2* b, vec2* dest);
vec2* vec2_sub  (vec2* a, vec2* b, vec2* dest);
vec2* vec2_mul  (vec2* a, vec2* b, vec2* dest);
vec2* vec2_div  (vec2* a, vec2* b, vec2* dest);

vec2* vec2_add_scalar  (vec2* v, double* s, vec2* dest);
vec2* vec2_sub_scalar  (vec2* v, double* s, vec2* dest);
vec2* vec2_mul_scalar  (vec2* v, double* s, vec2* dest);
vec2* vec2_div_scalar  (vec2* v, double* s, vec2* dest);

vec2* vec2_normalize(vec2* v, vec2* dest);

#endif