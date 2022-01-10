#pragma once

#include <stdio.h>

#define RULE_SIZE 3
#define VIRTUAL_MAX_COLS 71
#define MAX_COLS VIRTUAL_MAX_COLS + 2
#define FILE_MAX_LINES 27

// More about game of life: https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life

/*
 * Function: cell_lives
 * ----------------------------
 * Checks if the center cell lives in the next generation:
 * 
 * Any live cell with:
 *  - more than "maxNeighbors" neighbors dies -> overpopulation
 *  - fewer than "minNeighbors" neighbors dies -> underpopulation
 *  - otherwise, lives
 * 
 * Any dead cell with exactly "neighborsToBorn" neighbors becomes a live cell -> reproduction
 *
 * submatrix: 3x3 matrix of 0s and 1s
 * rule: life game rule -> {maxNeighbors, minNeighbors, neighborsToBorn}
 *
 * returns: 1 (true) if the cell lives in the next generation; otherwise returns 0 (false)
 */
int cell_lives(const int submatrix[3][3], const int rule[RULE_SIZE]);

/*
 * Function: clear_world
 * ----------------------------
 * Initializes a world with dead cells and size rows_count x cols_count.
 *
 * world: (rows_count + 2) x (cols_count + 2) matrix of 0s and 1s
 * rows_count: number of rows
 * cols_count: number of columns
 */
void clear_world(int world[][MAX_COLS], int rows_count, int cols_count);

/*
 * Function: set_cell
 * ----------------------------
 * Sets the value to the cell.
 *
 * world: matrix of 0s and 1s
 * row: cell row
 * col: cell column
 * value: value to set
 */
void set_cell(int world[][MAX_COLS], int row, int col, int value);

/*
 * Function: get_cell
 * ----------------------------
 * Gets the cell value.
 *
 * world: matrix of 0s and 1s
 * row: cell row
 * col: cell column
 */
int get_cell(const int world[][MAX_COLS], int row, int col);

/*
 * Function: copy_world
 * ----------------------------
 * Copies the world2 to the world1.
 * 
 * world1: matrix of 0s and 1s
 * rows_count: number of rows
 * cols_count: number of columns
 * world2: world to copy
 */
void copy_world(
	int world1[][MAX_COLS], int rows_count, int cols_count,
	int world2[][MAX_COLS]);

/*
 * Function: update_world
 * ----------------------------
 * Updates the world.
 * 
 * Boundary conditions:
 *  world[i][cols_count + 1]    -> world[i][1]
 *  world[i][0]                 -> world[i][cols_count]
 *  world[rows_count + 1][j]    -> world[1][j]
 *  world[0][j]                 -> world[rows_count][j]
 *
 * world: matrix of 0s and 1s
 * rows_count: number of rows
 * cols_count: number of columns
 * world_aux: auxiliary world
 * rule: life game rule -> {maxNeighbors, minNeighbors, neighborsToBorn}
 */
void update_world(
	int world[][MAX_COLS], int rows_count, int cols_count,
	int world_aux[][MAX_COLS], const int rule[RULE_SIZE]);

/*
 * Function: update_world_n_generations
 * ----------------------------
 * Updates the world n generations.
 *
 * n: number of generations to update
 * world: matrix of 0s and 1s
 * rows_count: number of rows
 * cols_count: number of columns
 * world_aux: auxiliary world
 * rule: life game rule -> {maxNeighbors, minNeighbors, neighborsToBorn}
 */
void update_world_n_generations(
	int n, int world[][MAX_COLS], int rows_count, int cols_count,
	int world_aux[][MAX_COLS], const int rule[RULE_SIZE]);

/*
 * Function: fprint_world
 * ----------------------------
 * Prints the world in a STREAM.
 * 
 * - dead cell (0) is represented by ". "
 * - live cell (1) is represented by "X "
 *
 * world: matrix of 0s and 1s
 * rows_count: number of rows
 * cols_count: number of columns
 * __stream: FILE object that identifies the stream where the world is to be written
 */
void fprint_world(const int world[][MAX_COLS], int rows_count, int cols_count, FILE *__restrict__ __stream);

/*
 * Function: print_world
 * ----------------------------
 * Shows the world in the standart output.
 * 
 * - dead cell (0) is represented by ". "
 * - live cell (1) is represented by "X "
 *
 * world: matrix of 0s and 1s
 * rows_count: number of rows
 * cols_count: number of columns
 */
void print_world(const int world[][MAX_COLS], int rows_count, int cols_count);

/*
 * Function: write_world
 * ----------------------------
 * Writes the world in a file.
 * 
 * - dead cell (0) is represented by ". "
 * - live cell (1) is represented by "X "
 *
 * world: matrix of 0s and 1s
 * rows_count: number of rows
 * cols_count: number of columns
 * filename: name of the file
 */
void write_world(const int world[][MAX_COLS], int rows_count, int cols_count, const char *filename);

/*
 * Function: read_world
 * ----------------------------
 * Initializes a world from a text file.
 * 
 * - dead cell (0) is represented by ". "
 * - live cell (1) is represented by "X "
 *
 * world: matrix of 0s and 1s
 * world_size: size of the world -> {rows_count, cols_count}
 * filename: path to the file
 */
void read_world(int world[FILE_MAX_LINES + 2][MAX_COLS], int world_size[2], const char *filename);
