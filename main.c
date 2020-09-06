#include <stdint.h>
#include <stdio.h>

#include <core.h>
#include <color.h>
#include <maths.h>
#include <bitmap.h>

#define WIDTH  1920//3840
#define HEIGHT 1080//2160

int main() {
    random_init();

    vec3     LOOKFROM             = {  0,  3, 10 };
    vec3     LOOKAT               = {  0,  0,  0 };
    vec3     VUP                  = {  0,  1,  0 };
    double   FOCUS_DIST           = 10;
    double   VFOV                 = 45;
    double   ASPECT_RATIO         = (double)WIDTH / HEIGHT;
    double   APERTURE             = 0.2;
    uint32_t SAMPLES_PER_PIXELS   = 10;
    double   SAMPLES_PER_PIXELS_D = (double)SAMPLES_PER_PIXELS;
    double   ZERO                 = 0;
    double   ONE                  = 1;
    int      MAX_DEPTH            = 100;

    camera cam;
    camera_setup(&LOOKFROM, &LOOKAT, &VUP, &VFOV, &ASPECT_RATIO, &APERTURE, &FOCUS_DIST, &cam);

    world w;
    world_create(&w);

    bitmap img;
    bitmap_create(WIDTH, HEIGHT, &img);

    ray r;
    for(uint32_t y = 0; y < img.height; y++) {
        for(uint32_t x = 0; x < img.width; x++) {
            vec3 c = vec3_zeros();
            for(uint32_t s = 0; s < SAMPLES_PER_PIXELS; s++) {
                double u = (x + random_double()) / (img.width - 1);
                double v = (y + random_double()) / (img.height - 1);
                
                vec3 sc = ray_color(camera_ray(&u, &v, &cam, &r), &w, MAX_DEPTH);
                vec3_add(&c, &sc, &c);
            }
            vec3_div_scalar(&c, &SAMPLES_PER_PIXELS_D, &c);
            vec3_clamp(&c, &ZERO, &ONE, &c);            
            vec3_sqrt(&c, &c);

            color* pixel = bitmap_pixel_at(&img, x, y);
            *pixel = color_vec3(&c);
        }
    }

    bitmap_to_png_file(&img, "../test.png");
    bitmap_free(&img);
    world_free(&w);

    return 0;
}