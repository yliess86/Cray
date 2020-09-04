#ifndef MATHS_UTILS_H
#define MATHS_UTILS_H

#include <math.h>
#include <stdlib.h>
#include <time.h>

#define DEG2RAD 0.01745329252
#define PI 3.14159265358979323846
#define M2PI 6.283185307179586

void   random_init();
double random_double();
double random_double_a_b(double a, double b);

double degree_to_radian(const double degree);

#endif