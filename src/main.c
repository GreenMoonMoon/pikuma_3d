#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "SDL3/SDL.h"
#include "draw.h"
#include "vector.h"

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static SDL_Texture *color_buffer_texture = NULL;
static int window_width;
static int window_height;

static bool is_running = false;

static Vector3 points[9 * 9 * 9];

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

    // build point array
    for (int z = 0; z < 9; ++z) {
        for (int y = 0; y < 9; ++y) {
            for (int x = 0; x < 9; ++x) {
                points[z * 89 + y * 9 + x] = (Vector3){x * 0.2f - 1.0f, y * 0.2f - 1.0f, z * 0.2f - 1.0f};
            }
        }
    }
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

}

static void render_color_buffer(void) {
    SDL_UpdateTexture(color_buffer_texture, NULL, color_buffer, (int)(window_width / 4) * sizeof(uint32_t));
    SDL_RenderTexture(renderer, color_buffer_texture, NULL, NULL);
}

static void render(void) {
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x15, 0x15, 0xFF);
    SDL_RenderClear(renderer);

    // draw
    for (int i = 0; i < 9*9*9; ++i) {
        IVector2 coord = project_point(points[i]);
        draw_pixel(coord.x, coord.y, 0xFF000000);
    }

    render_color_buffer();
    // AA BB GG RR
    clear_color_buffer(0xFFFFFF00);
     
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

    close_window();

    return 0;
}
