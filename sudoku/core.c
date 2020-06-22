#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include "core.h"



void generate_permutations(u_int8_t n, u_int8_t** arr) {
    srand(time(NULL));
    *arr = (u_int8_t*)malloc(sizeof(u_int8_t) * n);
    u_int8_t i, j, tmp;
    for (u_int8_t i = 0; i < n; ++i) (*arr)[i] = i + 1;
    for (u_int8_t l = 0; l < n; ++l) {
        i = rand() % n;
        j = rand() % n;
        tmp = (*arr)[i];
        (*arr)[i] = (*arr)[j];
        (*arr)[j] = tmp;
    }
}

u_int8_t v_in_col(u_int8_t v, u_int8_t i, u_int8_t*** board, u_int8_t m) {
    for (u_int8_t j = 0; j < m; ++j) {
        if ( (*board)[j][i] == v ) return 1;
    }
    return 0;
}

u_int8_t v_in_row(u_int8_t v, u_int8_t i, u_int8_t*** board, u_int8_t n) {
    for (u_int8_t j = 0; j < n; ++j) {
        if ( (*board)[i][j] == v ) return 1;
    }
    return 0;
}

u_int8_t v_in_block(u_int8_t v, u_int8_t i, u_int8_t j, u_int8_t*** board, u_int8_t size) {
    u_int8_t x, y;
    x = (i / size) * size;
    y = (j / size) * size;
    for (u_int8_t p = x; p < x + size; p++) {
        for (u_int8_t q = y; q < y + size; q++) {
            if ( v == (*board)[p][q] ) return 1;
        }
    }
    return 0;
}

u_int8_t v_valid(u_int8_t v, u_int8_t i, u_int8_t j, u_int8_t*** board, u_int8_t size) {
    if (v_in_col(v, j, board, size * size) == 1) return 0;
    if (v_in_row(v, i, board, size * size) == 1) return 0;
    if (v_in_block(v, i, j, board, size) == 1) return 0;
    return 1;
}

void backtrack(u_int8_t i, u_int8_t*** board, u_int8_t** candidates, u_int8_t* done, u_int8_t size) {
    if (i < (u_int8_t)pow(size, 4) && *done == 0){
        u_int8_t x, y, v, n;
        n = size * size;
        x = i / n;
        y = i % n;
        for (u_int8_t j = 0; j < n; ++j) {
            v = (*candidates)[j];
            if (v_valid(v, x, y, board, size) == 1) {
                (*board)[x][y] = v;

                if ( i == ((u_int8_t)pow(size, 4) - 1) ) {
                    *done = 1;
                    return;
                }
                else {
                    backtrack(i+1, board, candidates, done, size);
                    if (*done == 0) (*board)[x][y] = 0;
                }
            }
        }
    }
}

void generate_board(u_int8_t*** board, u_int8_t size) {
    // locate memory for board
    u_int8_t n = size * size;
    *board = (u_int8_t**)malloc(sizeof(u_int8_t*) * n);
    for (u_int8_t i = 0; i < n; ++i) {
        (*board)[i] = (u_int8_t*)malloc(sizeof(u_int8_t) * n);
    }

    // generate permutation candidates
    u_int8_t* candidates;
    generate_permutations(n, &candidates);

    // call backtracking procedure
    u_int8_t done = 0;
    backtrack(0, board, &candidates, &done, size);
}
