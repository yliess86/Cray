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
typedef struct { double x, y; }    vec2;
typedef struct { double x, y, z; } vec3;

// ============ RANDOM METHODS ============
void   random_init             ();
double random_double           ();
double random_double_a_b       (double a, double b);

// ============ UTILS METHODS ============
double degree_to_radian        (const double degree);
double clamp                   (const double s, const double a, const double b);

// ============ VEC3 METHODS ============
vec3   vec3_zeros              ();
vec3   vec3_ones               ();
vec3   vec3_scalar             (double s);
vec3   vec3_random_unit_disk   ();
vec3   vec3_random_unit_sphere ();
vec3   vec3_random_unit_vector ();
vec3   vec3_random_a_b         (double a, double b);
void   vec3_print              (vec3* v);
double vec3_sqr_length         (vec3* v);
double vec3_length             (vec3* v);
double vec3_dot                (vec3* a, vec3* b);
vec3*  vec3_sqrt               (vec3* v, vec3* dest);
vec3*  vec3_neg                (vec3* v, vec3* dest);
vec3*  vec3_add                (vec3* a, vec3* b, vec3* dest);
vec3*  vec3_sub                (vec3* a, vec3* b, vec3* dest);
vec3*  vec3_mul                (vec3* a, vec3* b, vec3* dest);
vec3*  vec3_div                (vec3* a, vec3* b, vec3* dest);
vec3*  vec3_lerp               (vec3* a, vec3* b, double* t, vec3* dest);
vec3*  vec3_clamp              (vec3* v, double* a, double* b, vec3* dest);
vec3*  vec3_cross              (vec3* a, vec3* b, vec3* dest);
vec3*  vec3_add_scalar         (vec3* v, double* s, vec3* dest);
vec3*  vec3_sub_scalar         (vec3* v, double* s, vec3* dest);
vec3*  vec3_mul_scalar         (vec3* v, double* s, vec3* dest);
vec3*  vec3_div_scalar         (vec3* v, double* s, vec3* dest);
vec3*  vec3_normalize          (vec3* v, vec3* dest);

#endif