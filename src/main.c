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
//static Triangle *box_triangles = NULL;
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

    return true;
}

static void close_window(void) {
    SDL_SetWindowFullscreen(window, false);
    cleanup_color_buffer();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

static void setup(void) {
    setup_color_buffer(window_width, window_height);
    color_buffer_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_BGRA32, SDL_TEXTUREACCESS_STREAMING, window_width / 4, window_height / 4);
    if(!color_buffer_texture){ fprintf(stderr, "error while creating the texture!\n"); }

    // copy data to mesh object
    const int vertex_count = sizeof(cube_vertices)/sizeof(Vector3);
    box_vertices = malloc(sizeof(cube_vertices));
    if (NULL != box_vertices) {
        for (int i = 0; i < vertex_count; ++i) {
            box_vertices[i].x = cube_vertices[i].x;
            box_vertices[i].y = cube_vertices[i].y;
            box_vertices[i].z = cube_vertices[i].z;
        }
    }
    box_rotations = (Vector3){0};
}

static void cleanup(void) {
    if (NULL != box_vertices) { free(box_vertices); }
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
    for (int i = 0; i < 8; ++i) {
        Vector3 point = box_vertices[i];
        point = rotate_x(point, box_rotations.x);
        point = rotate_y(point, box_rotations.y);
        point = rotate_z(point, box_rotations.z);
        point.z -= camera_position.z;
        IVector2 coord = project_point(point, 260.0f);
        draw_pixel(coord.x, coord.y, WHITE);
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
