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
Vec3 camera_position = {0, 0, -5.0f};

// Box
static Mesh mesh;

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

    // mesh = generate_cube_mesh();
    mesh = load_obj("../assets/meshes/monkey.obj");
}

static void cleanup(void) {
    free_mesh(mesh);
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
    mesh.transform.rotation.x += delta_time;
    mesh.transform.rotation.y += delta_time * 2.0f;
    mesh.transform.rotation.z += delta_time * 0.5f;

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
    for (int i = 0; i < mesh.triangle_count; ++i) {
        Vec3 point_a = mesh.vertices_list[mesh.triangles_list[i].a].position;
        Vec3 point_b = mesh.vertices_list[mesh.triangles_list[i].b].position;
        Vec3 point_c = mesh.vertices_list[mesh.triangles_list[i].c].position;

        point_a = vec3_rotate_x(point_a, mesh.transform.rotation.x);
        point_a = vec3_rotate_y(point_a, mesh.transform.rotation.y);
        point_a = vec3_rotate_z(point_a, mesh.transform.rotation.z);

        point_b = vec3_rotate_x(point_b, mesh.transform.rotation.x);
        point_b = vec3_rotate_y(point_b, mesh.transform.rotation.y);
        point_b = vec3_rotate_z(point_b, mesh.transform.rotation.z);

        point_c = vec3_rotate_x(point_c, mesh.transform.rotation.x);
        point_c = vec3_rotate_y(point_c, mesh.transform.rotation.y);
        point_c = vec3_rotate_z(point_c, mesh.transform.rotation.z);

        point_a.z -= camera_position.z;
        point_b.z -= camera_position.z;
        point_c.z -= camera_position.z;

        const IVec2 coord_a = project_point(point_a, camera_fov);
        const IVec2 coord_b = project_point(point_b, camera_fov);
        const IVec2 coord_c = project_point(point_c, camera_fov);

        Color color = mesh.vertices_list[0].color;
        draw_line(coord_a, coord_b, color);
        draw_line(coord_b, coord_c, color);
        draw_line(coord_c, coord_a, color);
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
