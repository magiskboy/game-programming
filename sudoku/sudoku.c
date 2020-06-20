#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>


#define SIZE 3


void generate_permutations(u_int8_t n, u_int8_t** arr) {
    srand(time(NULL));
    *arr = (u_int8_t*)malloc(sizeof(u_int8_t) * n);
    u_int8_t i, j, tmp;
    for (u_int8_t i = 0; i < n; ++i) (*arr)[i] = i + 1;
    for (u_int8_t i = 0; i < n; ++i) {
        i = rand() % n;
        j = rand() % n;
        tmp = (*arr)[i];
        (*arr)[i] = (*arr)[j];
        (*arr)[j] = tmp;
    }
}

void print_board(u_int8_t*** board) {
    u_int8_t n = SIZE * SIZE;
    for (u_int8_t i = 0; i < n; ++i) {
        for (u_int8_t j = 0; j < n; ++j) {
            printf("%d, ", (*board)[i][j]);
        }
        printf("\n");
    }
}

u_int8_t check_board(u_int8_t*** board) {
    u_int8_t n = SIZE * SIZE;
    for (u_int8_t i = 0; i < n; ++i) {
        for (u_int8_t j = 0; j < n; ++j) {
            if ((*board)[i][j] == 0) return 0;
        }
    }
    return 1;
}

u_int8_t v_in_col(u_int8_t v, u_int8_t i, u_int8_t*** board) {
    u_int8_t m = SIZE * SIZE;
    for (u_int8_t j = 0; j < m; ++j) {
        if ( (*board)[j][i] == v ) return 1;
    }
    return 0;
}

u_int8_t v_in_row(u_int8_t v, u_int8_t i, u_int8_t*** board) {
    u_int8_t n = SIZE * SIZE;
    for (u_int8_t j = 0; j < n; ++j) {
        if ( (*board)[i][j] == v ) return 1;
    }
    return 0;
}

u_int8_t v_in_block(u_int8_t v, u_int8_t i, u_int8_t j, u_int8_t*** board) {
    u_int8_t x, y;
    x = (i / SIZE) * SIZE;
    y = (j / SIZE) * SIZE;
    for (u_int8_t p = x; p < x + SIZE; p++) {
        for (u_int8_t q = y; q < y + SIZE; q++) {
            if ( v == (*board)[p][q] ) return 1;
        }
    }
    return 0;
}

u_int8_t v_valid(u_int8_t v, u_int8_t i, u_int8_t j, u_int8_t*** board) {
    if (v_in_col(v, j, board) == 1) return 0;
    if (v_in_row(v, i, board) == 1) return 0;
    if (v_in_block(v, i, j, board) == 1) return 0;
    return 1;
}

void backtrack(u_int8_t i, u_int8_t*** board, u_int8_t** candidates, u_int8_t* done) {
    if (i < (u_int8_t)pow(SIZE, 4) && *done == 0){
        u_int8_t x, y, n, v;
        n = SIZE * SIZE;
        x = i / n;
        y = i % n;
        for (u_int8_t j = 0; j < n; ++j) {
            v = (*candidates)[j];
            if (v_valid(v, x, y, board) == 1) {
                (*board)[x][y] = v;

                if ( i == ((u_int8_t)pow(SIZE, 4) - 1) ) {
                    *done = 1;
                    return;
                }
                else {
                    backtrack(i+1, board, candidates, done);
                    if (*done == 0) (*board)[x][y] = 0;
                }
            }
        }
    }
}

void generate_board(u_int8_t*** board) {
    // locate memory for board
    u_int8_t n = SIZE * SIZE;
    *board = (u_int8_t**)malloc(sizeof(u_int8_t*) * n);
    for (u_int8_t i = 0; i < n; ++i) {
        (*board)[i] = (u_int8_t*)malloc(sizeof(u_int8_t) * n);
    }

    // generate permutation candidates
    u_int8_t* candidates;
    generate_permutations(n, &candidates);

    // call backtracking procedure
    u_int8_t done = 0;
    backtrack(0, board, &candidates, &done);
}

int main(int argc, char** argv) {
    u_int8_t** board;
    generate_board(&board);
    print_board(&board);
    return 0;
}
