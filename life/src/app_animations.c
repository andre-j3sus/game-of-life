#include <stdio.h>
#include <string.h>
#include "animations.h"

/*
 * Game of life entry point.
 */
int main()
{
	int rule[3] = {3, 2, 3}; // Default rule

	int world_read[FILE_MAX_LINES + 2][MAX_COLS + 2];
	int world_read_size[2];

	int aux_world[FILE_MAX_LINES + 2][MAX_COLS + 2];

	int n;
	double delay_in_seconds;
	char filename[35];

	puts("File name (max 34 chars)");
	printf("%s", "or insert ENTER: ");

	fgets(filename, 35, stdin);
	filename[strlen(filename) - 1] = '\0';
	if (strcmp(filename, "") == 0)
	{
		strcpy(filename, "seis_barras.txt");
		puts("The seis_barras.txt will be used.");
	}

	printf("%s", "Number of iterations: ");
	scanf("%d", &n);
	printf("%s", "Time between frames (in seconds): ");
	scanf("%lf", &delay_in_seconds);

	read_world(world_read, world_read_size, filename);

	int rows_count = world_read_size[0];
	int cols_count = world_read_size[1];

	animate_world(n, world_read, rows_count, cols_count, aux_world,
				  rule, delay_in_seconds);

	return 0;
}
