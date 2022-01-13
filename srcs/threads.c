#include "philo.h"

void*	trick_or_treat(void *all)
{
	t_all			*new;
	struct timeval	start;
	int 			count;
	long			ct;

	new = (t_all *)all;
	gettimeofday(&start, NULL);
	while (1)
	{
		count = -1;
		while (++count < new->num_of_philo)
		{
			if (*new->eatcnt == (int)(*new).arr[0])
				return (all);
			if (new[count].state != thinking)
				continue;
			ct = cur_time(&start) * 1e-3;
			if (ct && ct >= new[count].deadline)
			{
				pthread_mutex_lock((*new).eatrow);
				(*new).state = died;
				printf("%ld philo #%d died %ld %d\n", ct, (int)new[count].a,
					   (new + count)->deadline, count);
				pthread_mutex_unlock((*new).eatrow);
				return (all);
			}
		}
	}
	return (all);
}

int	must_eat(t_all *new, int count)
{
	if (++count == new->arr[4])
	{
		pthread_mutex_lock((*new).eatrow);
		*new->eatcnt = *new->eatcnt + 1;
		printf("%d new->eatcnt %ld\n", *new->eatcnt, (*new).deadline);
		pthread_mutex_unlock((*new).eatrow);
	}
	return (count);
}

void	eat(t_all *new, struct timeval *start)
{
	(*new).state = eating;
	(*new).deadline = (*new).deadline + new->arr[1];
	printf("%.f philo #%d is eating\n", cur_time(start) * 1e-3, new->a);
	usleep(new->eatline * 1000);
	pthread_mutex_unlock(&new->forks[(new->a - 1) % new->arr[0]]);
	pthread_mutex_unlock(&new->forks[new->a % new->arr[0]]);
}

void 	take_forks(t_all *new, struct timeval *start)
{
	pthread_mutex_lock(&new->forks[(*new).a - 1 % new->arr[0]]);
	printf("%.f philo #%d has taken a fork\n", cur_time(start) *
											   1e-3, new->a);
	pthread_mutex_lock(&new->forks[(*new).a % new->arr[0]]);
	printf("%.f philo #%d has taken a fork\n", cur_time(start)
											   * 1e-3, new->a);
}

void	think(t_all *new, struct timeval *start)
{
	(*new).state = thinking;
	printf("%.f philo #%d is thinking\n", cur_time(start) * 1e-3, new->a);
}

void*	routine(void *all)
{
    t_all			*new;
    struct timeval	start;
    int 			count;

	count = 0;
    new = (t_all *) all;
    gettimeofday(&start, NULL);
    if (new->a % 2)
		usleep(10000);
	while ((*new).state != died)
    {
		if ((*new).state != died)
			think(new, &start);
		if ((*new).state != died)
			take_forks(new, &start);
		if ((*new).state != died)
			eat(new, &start);
//		(*new).state = thinking;
//		printf("%.f philo #%d is thinking\n", cur_time(&start) * 1e-3, new->a);
//    	pthread_mutex_lock(&new->forks[(*new).a - 1 % new->arr[0]]);
//        printf("%.f philo #%d has taken a fork\n", cur_time(&start) *
//        1e-3, new->a);
//        pthread_mutex_lock(&new->forks[(*new).a % new->arr[0]]);
//        printf("%.f philo #%d has taken a fork\n", cur_time(&start)
//        * 1e-3, new->a);
//		(*new).state = eating;
//		(*new).deadline = (*new).deadline + new->arr[1];
//		printf("%.f philo #%d is eating\n", cur_time(&start) * 1e-3, new->a);
//		usleep(new->sleepline * 1000);
//		pthread_mutex_unlock(&new->forks[(new->a - 1) % new->arr[0]]);
//		pthread_mutex_unlock(&new->forks[new->a % new->arr[0]]);
		if ((*new).state != died && new->arr[4])
			count = must_eat(new, count);
		(*new).state = sleeping;
        printf("%.f philo #%d is sleeping\n", cur_time(&start) * 1e-3,
			   new->a);
		usleep(new->sleepline * 1000);
    }
	return (new);
}

int others(t_struct	*gen)
{
	if (pthread_join(gen->death, NULL) != 0)
		return (error(gen, "Error: cannot join thread\n", 4));
	free(gen->state);
	free(gen->forks);
	return (0);
}

int create_threads(t_all *all, t_struct	*gen)
{
	int count;

	count = -1;
	while (++count < gen->arr[0])
	{
		all[count].a = count + 1;
		all[count].arr = gen->arr;
		all[count].num_of_philo = (short)gen->arr[0];
		all[count].deadline = gen->arr[1];
		all[count].eatline = gen->arr[2];
		all[count].sleepline = gen->arr[3];
		all[count].forks = gen->forks;
		all[count].eatrow = &gen->eatrow;
		all[count].eatcnt = &gen->eatcnt;
		if (pthread_create(&all[count].th, NULL, routine, &all[count]))
			return (error(gen, "Error: cannot create thread\n", 3));
	}
	if (pthread_create(&gen->death, NULL, trick_or_treat, all))
		return (error(gen, "Error: cannot create thread\n", 3));
	return (0);
}

int init_mutex(t_struct	*gen)
{
	int count;

	count = -1;
	while (++count < gen->arr[0])
	{
		if (pthread_mutex_init(&gen->forks[count], NULL))
			return (error(gen, "Error: cannot initialize mutex\n", 5));
	}
	if (gen->arr[4] && pthread_mutex_init(&gen->eatrow, NULL))
		return (error(gen, "Error: cannot initialize mutex\n", 5));
	return (0);
}
