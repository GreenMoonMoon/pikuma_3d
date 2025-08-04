#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "SDL3/SDL.h"
#include "draw.h"
#include "vector.h"
#include "geometry.h"

#define TARGET_FPS 30
#define TARGET_STEP (1000 / TARGET_FPS)

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static SDL_Texture *color_buffer_texture = NULL;
static int window_width;
static int window_height;

static bool is_running = false;
//static double last = 0.0;
static int fixed_last = 0;


const float camera_fov = 260.0f;
Vector3 camera_position = {0, 0, -5.0f};

// Box
static Vector3 *box_vertices = NULL;
static Triangle *box_triangles = NULL;
static Vector3 box_rotations;

static bool initialize_window(void) {
    if(!SDL_Init(SDL_INIT_VIDEO)){
        fprintf(stderr, "Cannot initialize SDL!\n");
        return false;
    }

    // Query SDL for the screen width and height
    const SDL_DisplayMode *display_mode = SDL_GetCurrentDisplayMode(SDL_GetPrimaryDisplay());
    window_width = display_mode->w;
    window_height = display_mode->h;
    fprintf(stdout, "window size: %d x %d\n", window_width, window_height);

    // SDL_SetHint(SDL_HINT_VIDEO_DRIVER, "opengles2");
    if(!SDL_CreateWindowAndRenderer("Pikuma3D", window_width, window_height, SDL_WINDOW_BORDERLESS, &window, &renderer)) {
        fprintf(stderr, "Cannot create window and renderer!\n");
        return false;
    }

    SDL_SetWindowFullscreen(window, true);

    color_buffer_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_BGRA32, SDL_TEXTUREACCESS_STREAMING, window_width / 4, window_height / 4);
    SDL_SetTextureScaleMode(color_buffer_texture, SDL_SCALEMODE_NEAREST);
    if(!color_buffer_texture){ fprintf(stderr, "error while creating the texture!\n"); }

    return true;
}

static void close_window(void) {
    SDL_DestroyTexture(color_buffer_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

static void setup(void) {
    setup_color_buffer(window_width, window_height);

    // copy data to mesh object
    box_vertices = malloc(sizeof(cube_vertices));
    if (NULL != box_vertices) {
        for (int i = 0; i < CUBE_VERTEX_COUNT; ++i) {
            box_vertices[i] = cube_vertices[i];
        }
    }
    box_triangles = malloc(sizeof(cube_triangles));
    if (NULL != box_triangles) {
        for (int i = 0; i < CUBE_TRIANGLE_COUNT; ++i) {
            box_triangles[i] = cube_triangles[i];
        }
    }
    box_rotations = (Vector3){0};
}

static void cleanup(void) {
    if (NULL != box_vertices) { free(box_vertices); }
    cleanup_color_buffer();
}

static void process_inputs(void) {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_EVENT_QUIT:
                is_running = false;
                break;
            case SDL_EVENT_KEY_DOWN:
                if(event.key.key == SDLK_ESCAPE) { is_running = false; }
                break;
            default: break;
        }
    }
}

static void update(void) {
    // calculate delta time
    // const double now = SDL_GetPerformanceCounter();
    // const float delta_time = (float)((now - last) / SDL_GetPerformanceFrequency());
    const int fixed_now = SDL_GetTicks();
    int wait = TARGET_STEP - (fixed_now - fixed_last);
    if (wait > 0 && wait <= TARGET_STEP) {
        SDL_Delay(wait);
    }
    const float delta_time = 1.0f / (float)TARGET_FPS;

    // update objects
    box_rotations.x += delta_time;
    box_rotations.y += delta_time;
    box_rotations.z += delta_time;

    // update last value
    // last = now;
    fixed_last = fixed_now;
}

static void render_color_buffer(void) {
    SDL_UpdateTexture(color_buffer_texture, NULL, color_buffer, (int)(window_width / 4) * sizeof(uint32_t));
    SDL_RenderTexture(renderer, color_buffer_texture, NULL, NULL);
}

static void render(void) {
    // SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0x00);
    SDL_RenderClear(renderer);

    // draw
    for (int i = 0; i < CUBE_TRIANGLE_COUNT; ++i) {
        Vector3 point_a = box_vertices[box_triangles[i].a];
        Vector3 point_b = box_vertices[box_triangles[i].b];
        Vector3 point_c = box_vertices[box_triangles[i].c];

        point_a = rotate_x(point_a, box_rotations.x);
        point_a = rotate_y(point_a, box_rotations.y);
        point_a = rotate_z(point_a, box_rotations.z);

        point_b = rotate_x(point_b, box_rotations.x);
        point_b = rotate_y(point_b, box_rotations.y);
        point_b = rotate_z(point_b, box_rotations.z);

        point_c = rotate_x(point_c, box_rotations.x);
        point_c = rotate_y(point_c, box_rotations.y);
        point_c = rotate_z(point_c, box_rotations.z);

        point_a.z -= camera_position.z;
        point_b.z -= camera_position.z;
        point_c.z -= camera_position.z;

        IVector2 coord_a = project_point(point_a, camera_fov);
        IVector2 coord_b = project_point(point_b, camera_fov);
        IVector2 coord_c = project_point(point_c, camera_fov);

        draw_pixel(coord_a.x, coord_a.y, WHITE);
        draw_pixel(coord_b.x, coord_b.y, WHITE);
        draw_pixel(coord_c.x, coord_c.y, WHITE);

        draw_line(coord_a, coord_b, WHITE);
        draw_line(coord_b, coord_c, WHITE);
        draw_line(coord_c, coord_a, WHITE);
    }

    render_color_buffer();
    // AA BB GG RR
    clear_color_buffer(DARKGREY);
     
    SDL_RenderPresent(renderer);
}

int main(int argc, char *argv[]){
    is_running = initialize_window();

    setup();
    while(is_running) {
        process_inputs();
        update();
        render();
    }
    cleanup();

    close_window();

    return 0;
}
