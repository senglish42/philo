#include "philo.h"

int error(t_struct	*gen, char *str, int num)
{
	gen->errno = num;
	if (gen->flag)
		free_data(gen);
	printf("%s", str);
	return(gen->errno);
}