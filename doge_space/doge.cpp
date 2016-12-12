#include <iostream>
#include <sstream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

class Doge;
class Player;

const int DOGE_FRAME_SIZE = 150;
const int MAX_DOGE = 8;
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 1000;
const int DISTANCE = 900;
const int MAX_STAR = 500;

SDL_Window* wind;
SDL_Renderer* rend;
SDL_Event event;
std::vector<SDL_Texture*> doge_images;
std::vector<Doge*> doges;
std::vector<SDL_Point> stars;
Player* player;
TTF_Font* font;
Mix_Music *sound;
bool isRunning;
int score;

void render_score(){
	std::stringstream ss;
	ss << score;
	std::string str_score = ss.str();
	SDL_Color cl = {255, 255, 255};
	SDL_Surface* surface_score = TTF_RenderText_Solid( font, str_score.c_str(), cl );
	SDL_Texture* texture_score = SDL_CreateTextureFromSurface( rend, surface_score );
	SDL_Rect frame_score = {SCREEN_WIDTH-surface_score->w-20, 20, surface_score->w, surface_score->h};
	SDL_RenderCopy(rend, texture_score, NULL, &frame_score );
}

class Doge{
public:
	Doge(const int& n, const int& x, const int& y, const int& rate=20, const int& v=5){
		this->image = doge_images[n];
		this->px = x;
		this->py = y;
		this->v = v;
		this->rate = rate;
		this->last_time = SDL_GetTicks();
	}
	
	void update(){
		if (SDL_GetTicks() - this->last_time > this->rate){
			this->py += this->v; 
		}
		if (this->py >= SCREEN_HEIGHT){
			this->reset();
		}
	}

	void render(){
		SDL_Rect frame = {this->px, this->py, DOGE_FRAME_SIZE, DOGE_FRAME_SIZE};
		SDL_RenderCopy(rend, this->image, NULL, &frame);
	}

	void handle(){

	}

	void reset(){
		this->py = rand()%(DISTANCE)-DISTANCE;
		this->image = doge_images[rand()%4];
		score++;
	}

	SDL_Texture* image;
	int px, py;
	int last_time;
	int rate, v;
};

class Player{
public:
	Player(){
		this->image = IMG_LoadTexture(rend, "player.png");
		this->x = 3;
		score = 0;
	}

	void update(){
		if (doges[this->x]->py+DOGE_FRAME_SIZE > SCREEN_HEIGHT-200){
			std::cout << "Score: " << score << std::endl;
			for (int i = 0; i < MAX_DOGE; ++i){
				doges[i]->reset();
				this->reset();
			}
		}
	
	}

	void render(){
		this->frame = {this->x*DOGE_FRAME_SIZE, SCREEN_HEIGHT-200, DOGE_FRAME_SIZE, 200};
		SDL_RenderCopy(rend, this->image, NULL, &this->frame);
	}

	void control(){
		if (event.type == SDL_KEYDOWN && event.key.repeat == 0){
			if (event.key.keysym.scancode == SDL_SCANCODE_LEFT){
				if (this->x > 0) this->x--;
			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT){
				if (this->x < MAX_DOGE-1) this->x++;
			
			}
		}	
	}

	void reset(){
		this->x = 3;
		score = 0;
	}

	int x;
	SDL_Texture* image;
	SDL_Rect frame;
};

int init(){
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		return -1;
	}
	TTF_Init();
	Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 );
	wind = SDL_CreateWindow("Doge War", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	rend = SDL_CreateRenderer(wind, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	font = TTF_OpenFont("font.ttf", 50);
	sound = Mix_LoadMUS( "doge.wav" );
	Mix_PlayMusic( sound, -1 );
	isRunning = true;

	SDL_Texture* image;
	image = IMG_LoadTexture(rend, "1.png");
	doge_images.push_back(image);
	image = IMG_LoadTexture(rend, "2.png");
	doge_images.push_back(image);
	image = IMG_LoadTexture(rend, "3.png");
	doge_images.push_back(image);
	image = IMG_LoadTexture(rend, "4.png");
	doge_images.push_back(image);
	image = IMG_LoadTexture(rend, "5.png");
	doge_images.push_back(image);

	for (int i = 0; i < MAX_STAR; ++i){
		SDL_Point p;
		p.x = rand()%SCREEN_WIDTH;
		p.y = rand()%SCREEN_HEIGHT;
		stars.push_back(p);
	}

	for (int i = 0; i < MAX_DOGE; ++i){
		doges.push_back(new Doge(rand()%5, i*150, (rand()%(DISTANCE))-DISTANCE));
	}

	player = new Player();

	return 1;
}

int handle(){
	if (SDL_PollEvent(&event) > 0){
		if ( event.type == SDL_QUIT ){
			isRunning = false;
		}
		player->control();
	}

}

int update(){
	for (int i = 0; i < MAX_DOGE; ++i){
		doges[i]->update();
	}

	for (int i = 0; i < MAX_STAR; ++i){
		if (stars[i].y > SCREEN_HEIGHT) stars[i].y = rand()%DISTANCE-DISTANCE; 
		else stars[i].y += 5;
	}

	player->update();


}

int render(){
	SDL_SetRenderDrawColor(rend, 0, 0, 0, 0);
	SDL_RenderClear(rend);
	// update screen in here
	
	for (int i = 0; i < MAX_DOGE; ++i){
		doges[i]->render();
	}

	for (int i = 0; i < MAX_STAR; ++i){
		SDL_SetRenderDrawColor(rend, 255, 255, 255, 0);
		SDL_RenderDrawPoint(rend, stars[i].x, stars[i].y);
	}
	
	player->render();

	render_score();

	SDL_RenderPresent(rend);
}

int exit(){
	delete player;
	SDL_DestroyWindow(wind);
	SDL_DestroyRenderer(rend);
	SDL_Quit();
	return 1;
}

int main(int argc, char* argv[]){
	if (init() == -1){
		return -1;
	}

	while(isRunning){
		handle();
		update();
		render();
	}
	exit();
	return 0;
}
