#pragma once

#include "life.h"

/*
 * Function: animate_world
 * ----------------------------
 * Shows the world animation in the standart output.
 *
 * n: number of generations to update
 * world: matrix of 0s and 1s
 * rows_count: number of rows
 * cols_count: number of columns
 * world_aux: auxiliary world
 * rule: life game rule -> {maxNeighbors, minNeighbors, neighborsToBorn}
 * delay_in_seconds: seconds between animation transition
 */
void animate_world(
	int n, int world[][MAX_COLS],
	int rows_count, int cols_count,
	int aux_world[][MAX_COLS],
	const int rule[RULE_SIZE], int delay_in_seconds);
