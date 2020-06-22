#ifndef SUDOKU_H
#define SUDOKU_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

u_int8_t sudoku();

void draw_board(u_int8_t**, SDL_Renderer*);

void put_text_to(SDL_Renderer* ren, TTF_Font* font, char* text, u_int16_t x, u_int16_t y);


#endif
