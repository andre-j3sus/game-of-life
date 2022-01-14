#include <stdlib.h>
#include <time.h>
#include "animations.h"
#include "life.h"

/*
 * Function: delays
 * ----------------------------
 * Delays the current thread.
 * 
 * delay_in_seconds: delay time
 */
void delays(int delay_in_seconds)
{
	int millis = 1000 * delay_in_seconds;

	clock_t initial = clock();
	clock_t final = initial + millis;

	while (clock() < final)
		;
}

void animate_world(int n, int world[][VIRTUAL_MAX_COLS + 2],
				   int rows_count, int cols_count,
				   int aux_world[][MAX_COLS],
				   const int rule[RULE_SIZE], int delay_in_seconds)
{
	system("clear"); // Clear Screen in Unix

	print_world(world, rows_count, cols_count);

	for (int i = 0; i < n; i++)
	{
		delays(delay_in_seconds);
		system("clear");
		update_world(world, rows_count, cols_count, aux_world, rule);
		print_world(world, rows_count, cols_count);
	}
}
