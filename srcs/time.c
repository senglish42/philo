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

long    cur_time(struct timeval *start)
{
	struct timeval	finish;
	long 			cur;

	gettimeofday(&finish, NULL);
	cur = (finish.tv_sec * 1e6 + finish.tv_usec) - (start->tv_sec * 1e6 + start->tv_usec);
	return (cur);
}