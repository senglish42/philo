#include "philo.h"

void*	routine(void *all)
{
	t_all *new;

	new = (t_all *)all;
	printf("hi from the philo #%d\n", new->a);
	while (new->flag == 0)
	{
		pthread_mutex_lock(&new->forks[new->a]);
		printf("Philo #%d has taken a fork\n", new->a);
		printf("Philo #%d is eating\n", new->a);
		abc++;
		new->flag = 1;
		pthread_mutex_unlock(&new->forks[new->a]);
	}
//	if (new->flag == 1)
//	{
//		printf("Ooops, i am eating again %d\n", new->a);
//		return(all);
//	}
	return (all);
}

int init_threads(t_all	*all, t_struct	*gen)
{
//	pthread_t	th[all->num_of_philo];
	int count;

	all->state = malloc(sizeof(int *) * gen->arr[0]);
	count = -1;
	while (++count < gen->arr[0])
		all->state[all->a] = thinking;
	gen->forks = malloc(sizeof(pthread_mutex_t) * gen->arr[0]);
	if (!all->forks)
		return (error(gen, "Error: cannot allocate memory\n", 6));
	count = -1;
	while (++count < gen->arr[0])
	{
		if (pthread_mutex_init(&gen->forks[count], NULL))
			return (error(gen, "Error: cannot initialize mutex\n", 5));
	}
//	if (pthread_mutex_init(&all->forks[all->a], NULL))
//		return (error(all, "Error: cannot initialize mutex\n", 5));
	count = -1;
	while (++count < gen->arr[0])
	{
		all[count].flag = 0;
		all[count].a = count;
		all[count].last_meal = 0;
		all[count].ate_cnt = 0;
		all[count].deadline = gen->arr[1];
		all[count].eatline = gen->arr[2];
		all[count].sleepline = gen->arr[3];
		all[count].eatrow = gen->arr[4];
		all[count].forks = gen->forks;
		if (pthread_create(&all[count].th, NULL, routine, &all[count]))
			return (error(gen, "Error: cannot create thread\n", 3));
	}
	count = -1;
	while (++count < gen->arr[0])
	{
		if (pthread_join(all[count].th, NULL) != 0)
			return (error(gen, "Error: cannot join thread\n", 4));
	}
	count = -1;
	while (++count < gen->arr[0])
		pthread_mutex_destroy(&gen->forks[count]);
	free(all->forks);
	return (0);
}
