#include <SDL3/SDL_init.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "SDL3/SDL.h"

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
int window_width = 800;
int window_height = 600;

static bool is_running = false;

static uint32_t *color_buffer = NULL;

static bool initialize_window(void) {
    if(!SDL_Init(SDL_INIT_VIDEO)){
        fprintf(stderr, "Cannot initialize SDL!");
        return false;
    }

    // SDL_SetHint(SDL_HINT_VIDEO_DRIVER, "opengles2");
    if(!SDL_CreateWindowAndRenderer("Pikuma3D", window_width, window_height, SDL_WINDOW_BORDERLESS, &window, &renderer)) {
        fprintf(stderr, "Cannot create window and renderer!");
        return false;
    }

    return true;
}

static void close_window(void) {
    if(NULL == color_buffer) { free(color_buffer); }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

static void setup(void) {
    color_buffer = SDL_malloc(sizeof(uint32_t) * window_width * window_height);
    if(NULL == color_buffer) {
        fprintf(stderr, "Cannot allocate color buffer!");
        return;
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

static void render(void) {
    SDL_SetRenderDrawColor(renderer, 0x15, 0x15, 0x15, 0xFF);
    SDL_RenderClear(renderer);

    // ...
     
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
