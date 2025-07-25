build:
	export SDL_RENDER_DRIVER="opengles2"
	gcc -Wall -std=c17 src/*.c -lSDL3 -lm -o pikuma3d

run:
	./pikuma3d

clean:
	rm ./pikuma3d

# export LD_LIBRARY_PATH=/usr/local/lib/aarch64-linux-gnu/
# export SDL_RENDER_DRIVER=opengles2
