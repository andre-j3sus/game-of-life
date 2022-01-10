#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "life.h"

int cell_lives(const int submatrix[3][3], const int rule[RULE_SIZE])
{
	int cell = submatrix[1][1];
	int live_cells = 0;

	for (int row = 0; row < 3; row++)
	{
		for (int col = 0; col < 3; col++)
		{
			if (col == 1 && row == 1)
				continue;

			live_cells += submatrix[row][col];
		}
	}

	return (cell == 1 && (live_cells >= rule[1] && live_cells <= rule[0])) ||
		   (cell == 0 && live_cells == rule[2]);
}

void clear_world(int world[][MAX_COLS], int rows_count, int cols_count)
{
	if (cols_count > VIRTUAL_MAX_COLS || rows_count < 2 || cols_count < 2)
		return;

	for (size_t row = 1; row < rows_count + 1; row++)
	{
		for (size_t col = 1; col < cols_count + 1; col++)
		{
			world[row][col] = 0;
		}
	}
}

void set_cell(int world[][MAX_COLS], int row, int col, int value)
{
	world[row][col] = value;
}

int get_cell(const int world[][MAX_COLS], int row, int col)
{
	return world[row][col];
}

void copy_world(
	int world1[][MAX_COLS], int rows_count, int cols_count,
	int world2[][MAX_COLS])
{
	for (size_t row = 1; row < rows_count + 1; row++)
	{
		for (size_t col = 1; col < cols_count + 1; col++)
		{
			world1[row][col] = world2[row][col];
		}
	}
}

void update_world(
	int world[][MAX_COLS],
	int rows_count, int cols_count,
	int world_aux[][MAX_COLS], const int rule[RULE_SIZE])
{
	for (size_t row = 1; row < rows_count + 1; row++)
	{
		for (size_t col = 1; col < cols_count + 1; col++)
		{
			int pre_row = row - 1;
			if (pre_row == 0)
				pre_row = rows_count;

			int pos_row = row + 1;
			if (pos_row == rows_count + 1)
				pos_row = 1;

			int pre_col = col - 1;
			if (pre_col == 0)
				pre_col = cols_count;

			int pos_col = col + 1;
			if (pos_col == cols_count + 1)
				pos_col = 1;

			int submatrix[3][3];
			submatrix[0][0] = get_cell(world, pre_row, pre_col);
			submatrix[0][1] = get_cell(world, pre_row, col);
			submatrix[0][2] = get_cell(world, pre_row, pos_col);
			submatrix[1][0] = get_cell(world, row, pre_col);
			submatrix[1][1] = get_cell(world, row, col);
			submatrix[1][2] = get_cell(world, row, pos_col);
			submatrix[2][0] = get_cell(world, pos_row, pre_col);
			submatrix[2][1] = get_cell(world, pos_row, col);
			submatrix[2][2] = get_cell(world, pos_row, pos_col);

			set_cell(world_aux, row, col, cell_lives(submatrix, rule));
		}
	}

	copy_world(world, rows_count, cols_count, world_aux);
}

void update_world_n_generations(
	int n, int world[][MAX_COLS],
	int rows_count, int cols_count,
	int world_aux[][MAX_COLS],
	const int rule[RULE_SIZE])
{
	if (n <= 0)
		return;

	for (size_t i = 0; i <= n; i++)
	{
		update_world(world, rows_count, cols_count, world_aux, rule);
	}
}

void fprint_world(const int world[][MAX_COLS], int rows_count, int cols_count, FILE *__restrict__ __stream)
{
	for (size_t row = 1; row < rows_count + 1; row++)
	{
		for (size_t col = 1; col < cols_count + 1; col++)
		{
			fputs((world[row][col]) ? "X " : ". ", __stream);
		}
		fputc('\n', __stream);
	}
}

void print_world(const int world[][MAX_COLS], int rows_count, int cols_count)
{
	fprint_world(world, rows_count, cols_count, stdout);
}

void write_world(const int world[][MAX_COLS], int rows_count, int cols_count, const char *filename)
{
	FILE *file = fopen(filename, "w");
	if (file == NULL)
	{
		printf("Error!\n");
		exit(-1);
	}

	fprint_world(world, rows_count, cols_count, file);

	fclose(file);
}

void read_world(int world[FILE_MAX_LINES + 2][MAX_COLS], int world_size[2], const char *filename)
{
	FILE *file = fopen(filename, "r");
	if (file == NULL)
	{
		printf("Error!\n");
		exit(1);
	}

	int row = 1;
	int col = 1;

	for (char c = getc(file); c != EOF; c = getc(file))
	{
		switch (c)
		{
		case '\n':
			if (row == 1)
				world_size[1] = col - 1;

			row++;
			col = 1;
			break;
		case '.':
		case 'X':
			set_cell(world, row, col++, c == 'X');
			break;
		default:
			break;
		}
	}

	world_size[0] = row - 1;

	fclose(file);
}
