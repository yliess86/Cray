#include <stdint.h>
#include <stdio.h>

#include <core.h>
#include <color.h>
#include <maths.h>
#include <bitmap.h>

#define WIDTH  800//1920//3840
#define HEIGHT 600//1080//2160

int main() {
    random_init();

    vec3   LOOKFROM     = {  0,  3, 10 };
    vec3   LOOKAT       = {  0,  0,  0 };
    vec3   VUP          = {  0,  1,  0 };
    double FOCUS_DIST   = 10;
    double VFOV         = 45;
    double ASPECT_RATIO = (double)WIDTH / HEIGHT;
    double APERTURE     = 0.2;

    camera cam;
    camera_setup(&LOOKFROM, &LOOKAT, &VUP, &VFOV, &ASPECT_RATIO, &APERTURE, &FOCUS_DIST, &cam);

    world w;
    world_create(&w);

    bitmap img;
    bitmap_create(WIDTH, HEIGHT, &img);

    ray r;
    for(uint32_t y = 0; y < img.height; y++) {
        for(uint32_t x = 0; x < img.width; x++) {
            double u = (double)x / (img.width - 1);
            double v = (double)y / (img.height - 1);
            ray_color(camera_ray(&u, &v, &cam, &r), &w, bitmap_pixel_at(&img, x, y));
        }
    }

    bitmap_to_png_file(&img, "../test.png");
    bitmap_free(&img);
    world_free(&w);

    return 0;
}