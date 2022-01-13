#include "philo.h"

long    get_time(void)
{
	struct timeval  tp;
	long            milliseconds;

	gettimeofday(&tp, NULL);
	milliseconds = tp.tv_sec * 1000;
	milliseconds += tp.tv_usec / 1000;
	return (milliseconds);
}
