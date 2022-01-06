#include "philo.h"

void*	routine(void *all)
{
	t_all *new;

	new = all;
//	int a;
//	a = -1;
	printf("hi from the philo #%d\n", new->a);
//	if (new->flag == 1)
//	{
//		printf("Ooops, i am eating again %d\n", new->philo->num);
//		return(all);
//	}
	while (new->flag == 0)
	{
//		pthread_mutex_lock(&new->forks[new->a]);
		printf("Philo #%d has taken a fork\n", new->a);
		printf("Philo #%d is eating\n", new->a);
		abc++;
		new->flag = 1;
//		pthread_mutex_unlock(&new->forks[new->a]);
		printf("oja\n");
	}
	//ft_rotate(&new->philo);
	return (all);
}

int init_threads(t_all	*all, t_struct	*gen)
{
//	pthread_t	th[all->num_of_philo];

	all->state = malloc(sizeof(int *) * all->num_of_philo);
	all->a = -1;
	while (++all->a < all->num_of_philo)
		all->state[all->a] = thinking;
	all->forks = malloc(sizeof(pthread_mutex_t) * all->num_of_philo);
	if (!all->forks)
		return (error(gen, "Error: cannot allocate memory\n", 6));
	all->a = -1;
	while (++all->a < all->num_of_philo)
	{
		if (pthread_mutex_init(&all->forks[all->a], NULL))
			return (error(gen, "Error: cannot initialize mutex\n", 5));
	}
//	if (pthread_mutex_init(&all->forks[all->a], NULL))
//		return (error(all, "Error: cannot initialize mutex\n", 5));
	all->a = -1;
	all->flag = 0;
	while (++all->a < all->num_of_philo)
	{
		all->last_meal = 0;
		all->ate_cnt = 0;
		if (pthread_create(&all[all->a].th, NULL, routine, &all[all->a]))
			return (error(gen, "Error: cannot create thread\n", 3));
		printf("oka %d\n", all->a);
//		if (all->philo->next)
//			all->philo = all->philo->next;
	}
	all->a = -1;
	while (++all->a < all->num_of_philo)
	{
		if (pthread_join(all[all->a].th, NULL) != 0)
			return (error(gen, "Error: cannot join thread\n", 4));
	}
	all->a = -1;
	while (++all->a < all->num_of_philo)
		pthread_mutex_destroy(&all->forks[all->a]);
	free(all->forks);
	return (0);
}
