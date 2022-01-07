#include <stdio.h>
#include <stdlib.h>
#include "life.h"

int cell_lives(const int submatrix[3][3], const int rule[3])
{
    int cell = submatrix[1][1];
    int alive_cells = 0;

    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            alive_cells += submatrix[row][col];
        }
    }

    return (cell && (alive_cells >= rule[1] && alive_cells <= rule[0])) ||
           (!cell && alive_cells == rule[2]);
}

void init_world(int world[][MAX_COLS + 2], int rows_count, int cols_count)
{
    if (cols_count > MAX_COLS || rows_count < 2 || cols_count < 2)
        return;

    world[rows_count + 2][cols_count + 2];

    for (size_t row = 0; row < rows_count; row++)
    {
        for (size_t col = 0; col < cols_count; col++)
        {
            world[row][col] = 0;
        }
    }
}

void set_cell(int world[][MAX_COLS + 2], int row, int col, int value)
{
    world[row][col] = value;
}

int get_cell(const int world[][MAX_COLS + 2], int row, int col)
{
    return world[row][col];
}

int *get_sub_matrix(int world[][MAX_COLS + 2], int row, int col)
{
    // To be implemented
}

void update_world(
    int world[][MAX_COLS + 2], int rows_count, int cols_count,
    int world_aux[][MAX_COLS + 2], const int rule[3])
{
    for (size_t row = 0; row < rows_count; row++)
    {
        for (size_t col = 0; col < cols_count; col++)
        {
            int submatrix[3][3]; // = get_sub_matrix(world, row, col);
            world[row][col] = cell_lives(submatrix, rule);
        }
    }
}

void update_world_n_generations(
    int n, int world[][MAX_COLS + 2],
    int rows_count, int cols_count,
    int world_aux[][MAX_COLS + 2],
    const int rule[3])
{
    if (n <= 0)
        return;

    for (size_t i = 0; i <= n; i++)
    {
        update_world(world, rows_count, cols_count, world_aux, rule);
    }
}

void shows_world(const int world[][MAX_COLS + 2], int rows_count, int cols_count)
{
    for (size_t row = 0; row < rows_count; row++)
    {
        for (size_t col = 0; col < cols_count; col++)
        {
            putchar((world[row][col]) ? "X" : ".");
            if (col == cols_count - 1)
                putchar("\n");
        }
    }
}

void write_world(
    const int world[][MAX_COLS + 2],
    int rows_count, int cols_count, const char *filename)
{
}

void read_world(
    int world[FILE_MAX_LINES + 2][MAX_COLS + 2],
    int world_size[2], const char *filename)
{
}
