#include "philo.h"

int error(t_all *all, char *str, int num)
{
	if (all->gen.flag)
		free_data(&all->gen);
	printf("%s", str);
	return (num);
}