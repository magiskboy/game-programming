#include "sudoku.h"
#include "core.h"

#include <stdio.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>


#define WIN_HEIGHT  600
#define WIN_WIDTH   700
#define CELL_SIZE   50
#define BOARD_SIZE  3


u_int8_t sudoku() {
    SDL_Window* win;
    SDL_Renderer* ren;
    SDL_Event evt;
    u_int8_t alive = 1;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("%s", SDL_GetError());
        return 1;
    }
    TTF_Init();
    TTF_Font* font = TTF_OpenFont("SnesItalic-vmAPZ.ttf", 30);
    win = SDL_CreateWindow("Sudoku", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
    if (win == NULL) {
        printf("%s", SDL_GetError());
        return 1;
    }
    ren = SDL_CreateRenderer(win, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == NULL) {
        printf("%s", SDL_GetError());
        return 1;
    }

    u_int8_t** board;
    generate_board(&board, BOARD_SIZE);

    // game loop
    while (alive == 1) {
        // handler event and update data and logic
        while (SDL_PollEvent(&evt)){
            if (evt.type == SDL_QUIT){
                alive = 0;
            }
        }

        // update and render screen
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 0);
        SDL_RenderClear(ren);

        draw_board(board, ren);

        SDL_RenderPresent(ren);
    }

    SDL_DestroyWindow(win);
    SDL_DestroyRenderer(ren);
    SDL_Quit();
    return 0;
}

void put_text_to(SDL_Renderer* ren, TTF_Font* font, char* text, u_int16_t x, u_int16_t y) {
    SDL_Surface* sur = TTF_RenderText
}

void draw_board(u_int8_t** board, SDL_Renderer* ren) {
    u_int16_t map_size = BOARD_SIZE * BOARD_SIZE;
    u_int16_t xs = 10, ys = 10;
    SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
    // draw y-axis
    for (u_int16_t i = xs; i < xs + (map_size + 1) * CELL_SIZE; i += CELL_SIZE) {
        SDL_RenderDrawLine(ren, i, ys, i, CELL_SIZE * map_size + map_size);
    }
    // draw x-axis
    for (u_int16_t i = ys; i < ys + (map_size + 1) * CELL_SIZE; i += CELL_SIZE) {
        SDL_RenderDrawLine(ren, xs, i, CELL_SIZE * map_size + map_size, i);
    }

    // fill number
}
