#include "philo.h"

int error(t_all *all, char *str, int num)
{
	if (all->philo)
		ft_lstclear(&all->philo);
	if (all->gen.flag)
		free_data(&all->gen);
	printf("%s", str);
	return (num);
}