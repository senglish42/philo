#include "philo.h"

int init_treads(t_all	*all)
{
	pthread_t	th[all->num_of_philo];
	int			a;

	pthread_mutex_init(&all->life, NULL);
	a = -1;
	while (++a < all->num_of_philo)
	{
		if (pthread_create(&th[a], NULL, routine, &all->life) != 0)
			return (error(all, "Error: cannot create thread\n", 3));
		usleep(500);
	}
	a = -1;
	while (++a < all->num_of_philo)
	{
		if (pthread_join(th[a], NULL) != 0)
			return (error(all, "Error: cannot join thread\n", 4));
	}
	pthread_mutex_destroy(&all->life);
	return (0);
}
