#include <stdint.h>
#include <stdio.h>
#include <pthread.h>

#include <core.h>
#include <color.h>
#include <maths.h>
#include <bitmap.h>

#define WIDTH             3840
#define HEIGHT            2160
#define TILE_SIZE         128
#define SAMPLES_PER_PIXEL 256
#define MAX_DEPTH         256
#define N_THREADS         8
#define PROGRESS_BAR_SIZE 50

void print_progress(uint32_t value, uint32_t total, uint8_t size) {
    double progress = (double)value / total;
    uint8_t n_bars = (uint8_t)(progress * size);
    char* progress_bar = (char*)calloc(size, sizeof(char));
    for(uint8_t i = 0; i < size; i++)
        progress_bar[i] = (i < n_bars)? '#': ' ';
    printf("\rClay Rendering Tiles ... [%s] %2.2f%%", progress_bar, progress * 100);
    fflush(stdout);
    free(progress_bar);
}

typedef struct { bitmap* img; world* w; camera* cam; }              targs;
typedef struct { uint32_t id; vec2 origin; }                        tile;
typedef struct { tile* tiles; uint32_t n_tiles; uint32_t current; } tile_queue;

void tile_queue_generate(bitmap* img, tile_queue* dest) {
    uint32_t n_rows = img->height / TILE_SIZE;
    uint32_t n_cols = img->width / TILE_SIZE;
    n_rows += (img->height - n_rows * TILE_SIZE > 0)? 1: 0;
    n_cols += (img->width - n_cols * TILE_SIZE > 0)? 1: 0;

    uint32_t n_tiles = n_rows * n_cols;
    tile* tiles = (tile*)calloc(n_tiles, sizeof(tile));
    for(uint32_t r = 0; r < n_rows; r++) {
        for(uint32_t c = 0; c < n_cols; c++) {
            uint32_t id = r * n_cols + c;
            tiles[id] = (tile){ id, (vec2){ c * TILE_SIZE, r * TILE_SIZE } };
        }
    }

    dest->tiles = tiles;
    dest->n_tiles = n_tiles;
    dest->current = 0;
}

void tile_queue_free(tile_queue* tq) {
    free(tq->tiles);
    tq->current = 0;
    tq->n_tiles = 0;
    tq = NULL;
}

void tile_render(bitmap* img, world* w, camera* cam, tile* t) {
    ray r;
    for(uint32_t y = t->origin.y; y < t->origin.y + TILE_SIZE; y++) {
        if(y > img->height - 1)
            continue;

        for(uint32_t x = t->origin.x; x < t->origin.x + TILE_SIZE; x++) {
            if(x > img->width - 1)
                continue;

            vec3 col = vec3_zeros();
            for(uint32_t s = 0; s < SAMPLES_PER_PIXEL; s++) {
                double u = (x + random_double()) / (img->width - 1);
                double v = (y + random_double()) / (img->height - 1);
                
                camera_ray(u, v, cam, &r);
                vec3 sample_col = ray_color(&r, w, MAX_DEPTH);
                vec3_add(&col, &sample_col, &col);
            }
            vec3_div_scalar(&col, (double)SAMPLES_PER_PIXEL, &col);
            vec3_clamp(&col, 0, 1, &col);            
            vec3_sqrt(&col, &col);

            color* pixel = bitmap_pixel_at(img, x, y);
            *pixel = color_vec3(&col);
        }
    }
}

tile_queue      tq;
pthread_t       tthreads[N_THREADS];
pthread_mutex_t tlock;
targs           ta;

void* tiles_render(void* args) {
    targs* ta = (targs*)args;

    while(tq.current < tq.n_tiles) {
        pthread_mutex_lock(&tlock);
        tile* t = &tq.tiles[tq.current++];
        pthread_mutex_unlock(&tlock);
        tile_render(ta->img, ta->w, ta->cam, t);
        print_progress(tq.current, tq.n_tiles, PROGRESS_BAR_SIZE);
    }

    return NULL;
}

int main() {
    // Initialize Random Seed to Current Timestamp
    random_init();

    // Camera Setup
    vec3     LOOKFROM            = {  0,  3, 10 };
    vec3     LOOKAT              = {  0,  0,  0 };
    vec3     VUP                 = {  0,  1,  0 };
    double   FOCUS_DIST          = 10;
    double   VFOV                = 45;
    double   ASPECT_RATIO        = (double)WIDTH / HEIGHT;
    double   APERTURE            = 0.2;

    camera cam;
    camera_setup(&LOOKFROM, &LOOKAT, &VUP, VFOV, ASPECT_RATIO, APERTURE, FOCUS_DIST, &cam);

    // World Setup
    world w;
    world_create(&w);

    vec3 dark_gray  = { 0.1, 0.1, 0.1 };
    vec3 gold       = { 0.5, 0.5, 0.1 };
    vec3 blue       = { 0.1, 0.2, 0.7 };
    vec3 green      = { 0.2, 0.4, 0.1 };
    vec3 water      = { 1.0, 1.0, 1.0 };

    material m_gray, m_gold, m_blue, m_green, m_water;
    metalic_create   (&dark_gray,  0.1, &m_gray);
    metalic_create   (&gold,       0.5, &m_gold);
    lambertian_create(&green,           &m_green);
    lambertian_create(&blue,            &m_blue);
    dielectric_create(&water,     1.33, &m_water);

    vec3 p_gray  = {    0,    0,   0 };
    vec3 p_gold  = { -1.5, -1.5, 1.5 };
    vec3 p_green = {    0, -102,   0 };
    vec3 p_blue  = {  1.5, -1.5, 1.5 };
    vec3 p_water = {    0, -1.5,   2 };

    sphere s_gray, s_gold, s_green, s_blue, s_water;
    sphere_create(&p_gray,  2.0, &m_gray,  &s_gray);
    sphere_create(&p_gold,  0.5, &m_gold,  &s_gold);
    sphere_create(&p_green, 100, &m_green, &s_green);
    sphere_create(&p_blue,  0.5, &m_blue,  &s_blue);
    sphere_create(&p_water, 0.5, &m_water, &s_water);
    
    world_add_sphere(&w, &s_gray);
    world_add_sphere(&w, &s_gold);
    world_add_sphere(&w, &s_green);
    world_add_sphere(&w, &s_blue);
    world_add_sphere(&w, &s_water);

    // PNG Initialization
    bitmap img;
    bitmap_create(WIDTH, HEIGHT, &img);

    // Generate Tiles
    tile_queue_generate(&img, &tq);
    print_progress(tq.current, tq.n_tiles, PROGRESS_BAR_SIZE);

    // Render each Tile
    ta = (targs){ &img, &w, &cam };
    pthread_mutex_init(&tlock, NULL);
    for(uint32_t i = 0; i < N_THREADS; i++)
        pthread_create(&tthreads[i], NULL, tiles_render, (void*)&ta);
    for(uint32_t i = 0; i < N_THREADS; i++)
        pthread_join(tthreads[i], NULL);

    printf("\n");
    
    // Save PNG
    bitmap_to_png_file(&img, "../test.png");
    
    // Destroy
    pthread_mutex_destroy(&tlock);
    tile_queue_free(&tq);
    bitmap_free(&img);
    world_free(&w);

    return 0;
}