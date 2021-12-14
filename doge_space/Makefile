all: deps
	@g++ main.cpp -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -o space

deps:
	@sudo apt install -y libsdl2-dev libsdl2-mixer-dev libsdl2-ttf-dev libsdl2-image-dev> /dev/null

clean:
	@rm -rf space
