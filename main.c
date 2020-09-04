#include <stdint.h>
#include <stdio.h>

#include <core/camera.h>
#include <core/color.h>
#include <maths/vec3.h>
#include <maths/utils.h>
#include <utils.h>

#define WIDTH  1920
#define HEIGHT 1080

int main() {
    random_init();

    vec3   LOOKFROM     = { 13,  2,  3 };
    vec3   LOOKAT       = {  0,  0,  0 };
    vec3   VUP          = {  0,  1,  0 };
    double FOCUS_DIST   = 10;
    double VFOV         = 20;
    double ASPECT_RATIO = (double)WIDTH / HEIGHT;
    double APERTURE     = 0.2;

    camera cam;
    camera_setup(
        &LOOKFROM, &LOOKAT, &VUP,
        &VFOV, &ASPECT_RATIO, &APERTURE, &FOCUS_DIST,
        &cam
    );

    bitmap img;
    bitmap_create(WIDTH, HEIGHT, &img);

    ray r;
    for(uint32_t y = 0; y < img.height; y++) {
        for(uint32_t x = 0; x < img.width; x++) {
            double u = (double)x / (img.width - 1);
            double v = (double)y / (img.height - 1);
            camera_ray(&u, &v, &cam, &r);
            ray_color(&r, bitmap_pixel_at(&img, x, y));
        }
    }

    bitmap_to_png_file(&img, "../test.png");
    bitmap_free(&img);

    return 0;
}