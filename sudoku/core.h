#ifndef CORE_H
#define CORE_H

#include <stdio.h>


void generate_permutations(u_int8_t, u_int8_t**);

u_int8_t v_in_col(u_int8_t, u_int8_t, u_int8_t***, u_int8_t);

u_int8_t v_in_row(u_int8_t, u_int8_t, u_int8_t***, u_int8_t);

u_int8_t v_in_block(u_int8_t, u_int8_t, u_int8_t, u_int8_t***, u_int8_t);

u_int8_t v_valid(u_int8_t, u_int8_t, u_int8_t, u_int8_t***, u_int8_t);

void backtrack(u_int8_t, u_int8_t***, u_int8_t**, u_int8_t*, u_int8_t);

void generate_board(u_int8_t***, u_int8_t);

#endif
