#include <maths/utils.h>

void random_init() { srand((int) time(NULL)); }
double random_double() { return (double)rand() / ((double)RAND_MAX + 1); }
double random_double_a_b(double a, double b) { return a + random() * (b - a); }

double degree_to_radian(const double degree) {
    return degree * DEG2RAD;
}