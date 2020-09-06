#ifndef MATHS_H
#define MATHS_H

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// ============ CONSTANTS ============
#define DEG2RAD 0.01745329252
#define PI      3.14159265359
#define M2PI    6.28318530718

// ============ STRUCTS ============
typedef struct { double x, y; }       vec2;
typedef struct { double x, y, z; }    vec3;
typedef struct { double x, y, z, w; } vec4;

// ============ RANDOM METHODS ============
void   random_init           ();
double random_double         ();
double random_double_a_b     (double a, double b);

// ============ ANGLES METHODS ============
double degree_to_radian      (const double degree);

// ============ VEC2 METHODS ============
vec2   vec2_zeros            ();
vec2   vec2_ones             ();
vec2   vec2_scalar           (double s);
void   vec2_print            (vec2* v);
double vec2_sqr_length       (vec2* v);
double vec2_length           (vec2* v);
double vec2_dot              (vec2* a, vec2* b);
vec2*  vec2_neg              (vec2* v, vec2* dest);
vec2*  vec2_add              (vec2* a, vec2* b, vec2* dest);
vec2*  vec2_sub              (vec2* a, vec2* b, vec2* dest);
vec2*  vec2_mul              (vec2* a, vec2* b, vec2* dest);
vec2*  vec2_div              (vec2* a, vec2* b, vec2* dest);
vec2*  vec2_add_scalar       (vec2* v, double* s, vec2* dest);
vec2*  vec2_sub_scalar       (vec2* v, double* s, vec2* dest);
vec2*  vec2_mul_scalar       (vec2* v, double* s, vec2* dest);
vec2*  vec2_div_scalar       (vec2* v, double* s, vec2* dest);
vec2*  vec2_normalize        (vec2* v, vec2* dest);

// ============ VEC3 METHODS ============
vec3   vec3_zeros            ();
vec3   vec3_ones             ();
vec3   vec3_scalar           (double s);
vec3   vec3_random_uint_disk ();
void   vec3_print            (vec3* v);
double vec3_sqr_length       (vec3* v);
double vec3_length           (vec3* v);
double vec3_dot              (vec3* a, vec3* b);
vec3*  vec3_neg              (vec3* v, vec3* dest);
vec3*  vec3_add              (vec3* a, vec3* b, vec3* dest);
vec3*  vec3_sub              (vec3* a, vec3* b, vec3* dest);
vec3*  vec3_mul              (vec3* a, vec3* b, vec3* dest);
vec3*  vec3_div              (vec3* a, vec3* b, vec3* dest);
vec3*  vec3_cross            (vec3* a, vec3* b, vec3* dest);
vec3*  vec3_add_scalar       (vec3* v, double* s, vec3* dest);
vec3*  vec3_sub_scalar       (vec3* v, double* s, vec3* dest);
vec3*  vec3_mul_scalar       (vec3* v, double* s, vec3* dest);
vec3*  vec3_div_scalar       (vec3* v, double* s, vec3* dest);
vec3*  vec3_normalize        (vec3* v, vec3* dest);

// ============ VEC4 METHODS ============
vec4   vec4_zeros            ();
vec4   vec4_ones             ();
vec4   vec4_scalar           (double s);
void   vec4_print            (vec4* v);
double vec4_sqr_length       (vec4* v);
double vec4_length           (vec4* v);
double vec4_dot              (vec4* a, vec4* b);
vec4*  vec4_neg              (vec4* v, vec4* dest);
vec4*  vec4_add              (vec4* a, vec4* b, vec4* dest);
vec4*  vec4_sub              (vec4* a, vec4* b, vec4* dest);
vec4*  vec4_mul              (vec4* a, vec4* b, vec4* dest);
vec4*  vec4_div              (vec4* a, vec4* b, vec4* dest);
vec4*  vec4_add_scalar       (vec4* v, double* s, vec4* dest);
vec4*  vec4_sub_scalar       (vec4* v, double* s, vec4* dest);
vec4*  vec4_mul_scalar       (vec4* v, double* s, vec4* dest);
vec4*  vec4_div_scalar       (vec4* v, double* s, vec4* dest);
vec4*  vec4_normalize        (vec4* v, vec4* dest);

#endif