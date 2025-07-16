build:
	gcc -Wall -std=c17 src/*.c -lSDL3 -o pikuma3d

run:
	export LD_LIBRARY_PATH=/usr/local/lib/aarch64-linux-gnu/
	# export SDL_RENDER_DRIVER=opengles2
	./pikuma3d

clean:
	rm ./pikuma3d

