//
// Created by josue on 2025-08-05.
//

#include "obj_parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/stat.h>
#include "geometry.h"
#include "external/stb_ds.h"

typedef struct Slice {
    char *start;
    size_t count;
} Slice;

static size_t get_file_size(FILE *file) {
    struct stat buf;
    fstat(fileno(file), &buf);
    return buf.st_size;
}

static Slice get_line(char *buffer) {
    // WARNING: unsafe function. buffers must contain a new line or an EOF character.
    // Slice slice = {
    //     .start = buffer,
    //     .count = 0,
    // };
    // while (buffer[slice.count] != '\n' || buffer[slice.count] != '\0') { slice.count++; }

    char *start = buffer;
    const char *end = buffer;
    while (*(++end) != '\n' || *end != '\0');
    return (Slice){start, (end - start)};
}

static size_t read_vector2(const char *buffer, Vector3 *vector) {
    char *start = buffer;
    char *end;
    vector->x = strtof(start, &end);
    start = end;
    vector->y = strtof(start, &end);
    return end - buffer;
}

static size_t read_vector3(const char *buffer, Vector3 *vector) {
    char *start = buffer;
    char *end;
    vector->x = strtof(start, &end);
    start = end;
    vector->y = strtof(start, &end);
    start = end;
    vector->z = strtof(start, &end);
    return end - buffer;
}

static void read_file(const char *filename) {
#define ADV_NEXT_SPACE() {do { ++i; } while (buffer[i] != '\n');}

    FILE *file = fopen(filename, "rb");
    if (NULL == file) {
        fprintf(stderr, "Error while opening %s!", filename);
        return; // TODO: display actual error (errno)
    }

    const size_t file_size = get_file_size(file);
    const size_t count = file_size / sizeof(char);
    char *buffer = malloc(file_size);
    if (NULL == buffer) {
        fprintf(stderr, "Could not read %s", filename);
        fclose(file);
        return; // "file too large"?
    }
    // fill the buffer
    const size_t read_size = fread(buffer, sizeof(char), count, file);
    if (read_size < file_size) {
        fprintf(stderr, "error while reading file?");
    }

    // parse buffer
    Vector3 *position_list = NULL;
    Vector3 *normal_list = NULL;
    Vector2 *uv_list = NULL;
    Triangle *triangle_list = NULL;

    size_t i = 0;
    while (++i < read_size) {
        switch (buffer[i]) {
            case '#': // comment
                ADV_NEXT_SPACE();
                break;
            case 'o': // object
                i++; // advance one white space
                // TODO: handle retrieving the name
                ADV_NEXT_SPACE();
                break;
            case 'v':
                i++;
                if (buffer[i] == 'n') { // a vertex normal
                    i++;
                    Vector3 normal;
                    i += read_vector3(&buffer[i], &normal);
                    arrput(normal_list, normal);
                } else if (buffer[i] == 't') { // a vertex texture coordinate
                    i++;
                    Vector2 uv;
                    i += read_vector2(&buffer[i], &uv);
                    arrput(uv_list, uv);
                } else { // a vertex position
                    i++; // advance one white space
                    Vector3 position;
                    i += read_vector3(&buffer[i], &position);
                    arrput(position_list, position);
                }
                break;
            case 's': break;
            case 'f': // faces
                i+=2;
                // f (v)/(vt)/(vn)
                int vertex_index = 0;
                int vertex_uv = 0;
                int vertex_normal = 0;
                vertex_index = atoi(&buffer[i]); i++;
                if (buffer[i] == '\\' && !buffer[i + 1] == '\\') {
                    vertex_uv = atoi(&buffer[i++]);
                    i++;
                }
                if (buffer[i] == '\\' && !buffer[i + 1] == '\\') {
                    vertex_normal = atoi(&buffer[i++]);
                    i++;
                }

                break;
            default: break;
        }
    }

    free(buffer);
    fclose(file);
}

Mesh load_obj(const char* filename) {
    Mesh mesh = {0};

    read_file(filename);

    return mesh;
}
