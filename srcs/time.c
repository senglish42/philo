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

//int delay(long sleep)
//{
//	long start_time;
//	long cur_time;
//
//	start_time = get_time();
//	while (1)
//	{
//		cur_time = get_time() - start_time;
//		if (cur_time == sleep)
//			break ;
//	}
//	return (0);
//}
