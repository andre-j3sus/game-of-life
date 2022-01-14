#include <stdio.h>
#include <string.h>
#include "animations.h"
#include "life.h"

/*
 * Game of life entry point.
 */
int main()
{
	int rule[3] = {3, 2, 3}; // Default rule

	int world_read[FILE_MAX_LINES + 2][MAX_COLS];
	int world_read_size[2];

	int aux_world[FILE_MAX_LINES + 2][MAX_COLS];

	int n;
	int delay_in_seconds;
	char filename[40];

	printf("\nFile path (max 34 chars) or insert ENTER: ");

	fgets(filename, 39, stdin);
	filename[strlen(filename) - 1] = '\0';
	if (strcmp(filename, "") == 0)
	{
		strcpy(filename, "../docs/initial_worlds/six_bars.txt");
		puts("The six_bars.txt will be used.");
	}

	printf("\nNumber of iterations: ");
	scanf("%d", &n);
	printf("\nTime between frames (in seconds): ");
	scanf("%d", &delay_in_seconds);

	read_world(world_read, world_read_size, filename);

	int rows_count = world_read_size[0];
	int cols_count = world_read_size[1];

	animate_world(n, world_read, rows_count, cols_count, aux_world,
				  rule, delay_in_seconds);

	return 0;
}
