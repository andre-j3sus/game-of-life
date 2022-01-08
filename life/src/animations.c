#include <stdlib.h>
#include <time.h>
#include "animations.h"

/*
 * Function: delays
 * ----------------------------
 * Delays the current thread.
 * 
 * delay_in_seconds: delay time
 */
void delays(double delay_in_seconds)
{
	int millis = 1000 * delay_in_seconds;

	clock_t initial = clock();
	clock_t final = initial + millis;

	while (clock() < final)
		;
}

void animate_world(int n, int world[][MAX_COLS + 2],
				   int rows_count, int cols_count,
				   int aux_world[][MAX_COLS + 2],
				   const int rule[3], double delay_in_seconds)
{
	system("CLS"); // CLear Screen em Windows

	shows_world(world, rows_count, cols_count);

	for (int i = 0; i < n; i++)
	{
		delays(delay_in_seconds);
		system("CLS");
		update_world(world, rows_count, cols_count, aux_world, rule);
		shows_world(world, rows_count, cols_count);
	}
}
