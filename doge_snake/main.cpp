#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>


class Snake;

const int MAP_WIDTH = 35;
const int MAP_HEIGHT = 21;
const int TILE_SIZE = 35;
const int SCREEN_WIDTH = MAP_WIDTH * TILE_SIZE + 150;
const int SCREEN_HEIGHT = MAP_HEIGHT * TILE_SIZE;
const char* TITLE = "Doge Snake";
const int MAX_IMAGE = 5;


int SPEED = 120;
SDL_Window* wind = NULL;
SDL_Renderer* rend = NULL;
SDL_Event evt;

bool isRunning;
Snake* player;
std::vector<SDL_Texture*> doge_image;
SDL_Texture* image_food;
SDL_Texture* bg;
std::vector<int> wall;
// position in map
SDL_Rect block_food = {0, 0, TILE_SIZE, TILE_SIZE};
int score;
TTF_Font* font;
Mix_Music *bgSound = NULL;
Mix_Chunk *eatSound = NULL;

int init();
int update();
int render();
int handle();
int exit();

class Snake{
public:
	Snake(){
		std::cout << "Snake start" << std::endl;
		this->image.push_back(doge_image[0]);
		// position in map
		SDL_Rect head = {MAP_WIDTH/2, MAP_HEIGHT/2, TILE_SIZE, TILE_SIZE};
		this->blocks.push_back(head);
		this->last_block = head;
		this->isDead = false;
		this->last_update = SDL_GetTicks();
	}

	void update(){
		if (!this->isDead && SDL_GetTicks() - this->last_update > SPEED){

			if (this->blocks[0].x == block_food.x && this->blocks[0].y == block_food.y){
			
				// eat
				Mix_PlayChannel( -1, eatSound, 0 );
				score++;
				if (score % 10 == 0){
					if (SPEED > 20) SPEED -= 20;
				}
				this->add_block();
				// generate food
				block_food = {1+rand()%(MAP_WIDTH-2), 1 + rand()%(MAP_HEIGHT-2), TILE_SIZE, TILE_SIZE};
				image_food = doge_image[rand()%MAX_IMAGE];
			}

			// check collision 
			// wall
			SDL_Rect head = this->blocks[0];
			if (head.x == 0 || head.y == 0 || head.x == MAP_WIDTH-1 || head.y == MAP_HEIGHT-1){
				this->isDead = true;
			}

			// self
			int i = 1;
			while (i < this->blocks.size() && !this->isDead){
				if (head.x == this->blocks[i].x && head.y == this->blocks[i].y){
					this->isDead = true;
				
				}
				++i;
			}

			// move
		
			this->last_block = this->blocks[this->blocks.size()-1];
			for (int i = this->blocks.size()-1; i > 0; --i){
				this->blocks[i] = this->blocks[i-1];
			}
			this->blocks[0].x += this->direction.x;
			this->blocks[0].y += this->direction.y;
			this->last_update = SDL_GetTicks();
		}
	}
	

	void render(){
		// draw snake
		if (!this->isDead){
			for (int i = 0; i < this->blocks.size(); ++i){
				SDL_Rect block = this->blocks[i];
				block.x *= TILE_SIZE;
				block.y *= TILE_SIZE;
				SDL_RenderCopy(rend, this->image[i], NULL, &block);
			}
		}
	}
	
	void handle(){
		switch (evt.key.keysym.scancode){
			case SDL_SCANCODE_LEFT:
				player->direction = {-1, 0};
				break;

			case SDL_SCANCODE_RIGHT:
				player->direction = {1, 0};
				break;

			case SDL_SCANCODE_UP:
				player->direction = {0, -1};
				break;

			case SDL_SCANCODE_DOWN:
				player->direction = {0, 1};
				break;

		}
	}

	void add_block(){
		this->blocks.push_back(last_block);
		this->image.push_back(image_food);
	}

	std::vector<SDL_Texture*> image;
	std::vector<SDL_Rect> blocks;
	SDL_Rect last_block;
	bool isDead;	
	SDL_Point direction = {1, 0};
	long int last_update;
};



int init(){
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1){
		std::cout << SDL_GetError() << std::endl;
		return -1;
	}
	if (TTF_Init() == -1){
		std::cout << TTF_GetError() << std::endl;
		return -1;
	}

	if (Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) == -1){
		std::cout << Mix_GetError() << std::endl;
		return -1;
	}

	wind = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	rend = SDL_CreateRenderer(wind, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	score = 0;
	isRunning = true;

	// load doge image
	SDL_Texture* image;
	image = IMG_LoadTexture(rend, "1.png");
	doge_image.push_back(image);
	image = IMG_LoadTexture(rend, "2.png");
	doge_image.push_back(image);
	image = IMG_LoadTexture(rend, "3.png");
	doge_image.push_back(image);
	image = IMG_LoadTexture(rend, "4.png");
	doge_image.push_back(image);
	image = IMG_LoadTexture(rend, "5.png");
	doge_image.push_back(image);

	for (int i = 0; i < (MAP_WIDTH+MAP_HEIGHT)*2; ++i){
		wall.push_back(rand()%MAX_IMAGE);
	}

	bg = IMG_LoadTexture(rend, "bg.jpg");
	font = TTF_OpenFont("font.ttf", 50);
	bgSound = Mix_LoadMUS("doge.wav");
	eatSound = Mix_LoadWAV("eat.wav");	
	Mix_PlayMusic( bgSound, -1 );
	Mix_PauseMusic();
	player = new Snake();

	// generate food
	block_food = {1 + rand()%(MAP_WIDTH-2), 1 + rand()%(MAP_HEIGHT-2), TILE_SIZE, TILE_SIZE};
	image_food = doge_image[rand()%MAX_IMAGE];
	std::cout << block_food.x << " " << block_food.y << std::endl;

	std::cout << "Init complete" << std::endl;
	return 1;

}

int handle(){
	if (SDL_PollEvent(&evt) > 0){
		isRunning =  not (evt.type == SDL_QUIT);
		if (evt.type == SDL_KEYDOWN){
			isRunning = not (evt.key.keysym.scancode == SDL_SCANCODE_ESCAPE);
			player->handle();
			if (evt.key.keysym.scancode == SDL_SCANCODE_RETURN && player->isDead){
				score = 0;
				delete player;
				player = new Snake();
			}
		}
	}

}


int update(){
	player->update();
	
	if (player->isDead){
		Mix_ResumeMusic();
	}	
	else{
		bgSound = Mix_LoadMUS( "doge.wav");
		Mix_PlayMusic( bgSound, -1 );
		Mix_PauseMusic();
	}

	return 1;
}


int render(){
	SDL_SetRenderDrawColor(rend, 0x00, 0x00, 0x00, 0xff);
	SDL_RenderClear(rend);

	// draw grid map
	/*
	SDL_SetRenderDrawColor(rend, 0x00, 0xff, 0x00, 0xff);
	for (int i = 0; i < MAP_WIDTH; ++i){
		SDL_RenderDrawLine(rend, i*TILE_SIZE, 0, i*TILE_SIZE, SCREEN_HEIGHT);
	}
	for (int i = 0; i < MAP_HEIGHT; ++i){
		SDL_RenderDrawLine(rend, 0, i*TILE_SIZE, SCREEN_WIDTH, i*TILE_SIZE);
	}
	*/

	// draw wall
	if (!player->isDead){
		SDL_SetRenderDrawColor(rend, 0xff, 0xff, 0xff, 0xff);
		
		for (int i = 0; i < MAP_WIDTH; ++i){
			SDL_Rect tile = {i*TILE_SIZE, 0, TILE_SIZE, TILE_SIZE};
			// SDL_RenderFillRect(rend, &tile);
			SDL_RenderCopy(rend, doge_image[wall[i]], NULL, &tile);
			tile = {i*TILE_SIZE, SCREEN_HEIGHT-TILE_SIZE, TILE_SIZE, TILE_SIZE};
			// SDL_RenderFillRect(rend, &tile);
			SDL_RenderCopy(rend, doge_image[wall[i+MAP_WIDTH+MAP_HEIGHT]], NULL, &tile);
		}

		for (int i = 0; i < MAP_HEIGHT; ++i){
			SDL_Rect tile = {0, i*TILE_SIZE, TILE_SIZE, TILE_SIZE};
			// SDL_RenderFillRect(rend, &tile);
			SDL_RenderCopy(rend, doge_image[wall[i+MAP_WIDTH]], NULL, &tile);
			tile = {(MAP_WIDTH-1)*TILE_SIZE, i*TILE_SIZE, TILE_SIZE, TILE_SIZE};
			// SDL_RenderFillRect(rend, &tile);
			SDL_RenderCopy(rend, doge_image[wall[i+MAP_WIDTH*2+MAP_HEIGHT]], NULL, &tile);
		}

		SDL_Rect rect;
		rect = block_food;
		rect.x *= TILE_SIZE;
		rect.y *= TILE_SIZE;
		SDL_RenderCopy(rend, image_food, NULL, &rect);

		// draw score 
		std::stringstream ss;
		ss << score;
		SDL_Color cl = {0xff, 0xff, 0xff, 0xff};
		SDL_Surface* sur = TTF_RenderText_Solid(font, ss.str().c_str(), cl);
		rect = {MAP_WIDTH*TILE_SIZE + 10, 20, sur->w, sur->h};
		SDL_Texture* scoreTex = SDL_CreateTextureFromSurface(rend, sur);
		SDL_RenderCopy(rend, scoreTex, NULL, &rect);

	}
	else{
		SDL_RenderCopy(rend, bg, NULL, NULL);
	}


	player->render();

	SDL_RenderPresent(rend);
	return 1;
}

int exit(){
	SDL_DestroyWindow(wind);
	SDL_DestroyRenderer(rend);
	SDL_Quit();
	delete player;
}




int main(int argc, char* argv[]){
	std::cout << "Doge Snake" << std::endl;

	if (init() == -1) return -1;

	while (isRunning){
		update();
		render();
		handle();
	}
	exit();
	return 0;
}
