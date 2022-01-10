#include <stdio.h>
#include "life.h"

/*
 * Game of life unit tests.
 */
int main(void)
{
	int rule[3] = {3, 2, 3}; // Default rule

	// -------------------------------------------------------------------------------
	// Testing cell_lives with rule = {3, 2, 3}

	// Survives?

	int sub1[3][3] = {{0, 0, 0},
					  {0, 1, 0},
					  {0, 1, 0}}; // Doesn't survive
	if (cell_lives(sub1, rule))
		puts("cell_lives sub1 failed");

	int sub2[3][3] = {{0, 0, 0},
					  {0, 1, 0},
					  {1, 0, 1}}; // Survives
	if (!cell_lives(sub2, rule))
		puts("cell_lives sub2 failed");

	int sub3[3][3] = {{0, 1, 0},
					  {0, 1, 1},
					  {1, 0, 0}}; // Survives
	if (!cell_lives(sub3, rule))
		puts("cell_lives sub3 failed");

	int sub4[3][3] = {{0, 1, 1},
					  {1, 1, 0},
					  {1, 0, 0}}; // Doesn't survive
	if (cell_lives(sub4, rule))
		puts("cell_lives sub4 failed");

	// Reborns?

	int sub5[3][3] = {{0, 0, 1},
					  {0, 0, 0},
					  {0, 1, 0}}; // Doesn't reborn
	if (cell_lives(sub5, rule))
		puts("cell_lives sub5 failed");

	int sub6[3][3] = {{0, 1, 0},
					  {0, 0, 0},
					  {1, 0, 1}}; // Reborns
	if (!cell_lives(sub6, rule))
		puts("cell_lives sub6 failed");

	int sub7[3][3] = {{0, 1, 0},
					  {1, 0, 0},
					  {1, 0, 1}}; // Doesn't reborn
	if (cell_lives(sub7, rule))
		puts("cell_lives sub7 failed");

	// -------------------------------------------------------------------------------
	// Testing clear_world

	// World with virtual size 3 x 5 and effective size 5 x 7
	int small_world[][MAX_COLS + 2] =
		{{0, 0, 0, 0, 0, 0, 0},	 // Rest of the line with 0s
		 {0, 1, 1, 1, 1, 1, 0},	 // idem
		 {0, 1, 1, 1, 1, 1, 0},	 // idem
		 {0, 1, 1, 1, 1, 1, 0},	 // idem
		 {0, 0, 0, 0, 0, 0, 0}}; // idem

	clear_world(small_world, 3, 5);
	int row, col;
	for (row = 1; row <= 3; row++)
		for (col = 1; col <= 5; col++)
			if (small_world[row][col] != 0)
				puts("clear_world failed");

	// -------------------------------------------------------------------------------
	// Testing set_cell

	set_cell(small_world, 3, 5, 1); // Only one live cell
	if (small_world[3][5] != 1)
		puts("set_cell failed");
	for (row = 1; row <= 2; row++)
		for (col = 1; col <= 5; col++)
			if (small_world[row][col] != 0)
				puts("set_cell failed");
	for (col = 1; col <= 4; col++)
		if (small_world[3][col] != 0)
			puts("set_cell failed");

	// -------------------------------------------------------------------------------
	// Testing get_cell

	if (get_cell(small_world, 3, 5) != 1)
		puts("get_cell failed");
	if (get_cell(small_world, 3, 4) != 0)
		puts("get_cell failed");

	// -------------------------------------------------------------------------------
	// Creating new world for tests

	// World with virtual size 11 x 11 and effective size 13 x 13
	int test_world[13][MAX_COLS + 2] =
		{{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // Rest of the line with 0s
		 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // idem
		 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // etc...
		 {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
		 {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
		 {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
		 {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
		 {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
		 {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
		 {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
		 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

	// -------------------------------------------------------------------------------
	// Testing print_world

	puts("\nTesting print_world");
	print_world(test_world, 11, 11);

	// -------------------------------------------------------------------------------
	// Testing write_world

	puts("\nTesting write_world");
	write_world(test_world, 11, 11, "../docs/life_test_output/wrote_world.txt");

	// -------------------------------------------------------------------------------
	// Testing read_world

	puts("\nTesting read_world with print_world");

	// Where the read world will be saved
	int world_read[FILE_MAX_LINES + 2][MAX_COLS + 2];

	// Where the read world virtual size will be saved
	int read_world_size[2];

	read_world(world_read, read_world_size, "../docs/life_test_output/wrote_world.txt");

	// Confirming if read_world_size is correct
	int rows_read = read_world_size[0];
	int cols_read = read_world_size[1];
	if (rows_read != 11 || cols_read != 11)
		puts("read_world failed in read_world_size");

	// Confirming if world_read is correct
	print_world(world_read, 11, 11);

	// -------------------------------------------------------------------------------
	// Testing update_world

	puts("\nTesting update_world with print_world");

	int aux_world[13][MAX_COLS + 2];

	for (int iterations = 1; iterations <= 5; iterations++)
	{
		update_world(test_world, 11, 11, aux_world, rule);
		puts("");
		print_world(test_world, 11, 11);
	}

	// -------------------------------------------------------------------------------
	// Testing update_world_n_generations

	puts("\nTesting update_world_n_generations with print_world");
	puts("\n5 Iterations");

	// Redo test_world
	clear_world(test_world, 11, 11);
	for (row = 3; row <= 9; row++)
		set_cell(test_world, row, 6, 1);
	for (col = 3; col <= 9; col++)
		set_cell(test_world, 6, col, 1);

	update_world_n_generations(5, test_world, 11, 11, aux_world, rule);
	puts("");
	print_world(test_world, 11, 11);

	return 0;
}
