#include "philo.h"

long    cur_time(struct timeval *start)
{
    struct timeval	finish;
    long 			cur;

    gettimeofday(&finish, NULL);
	cur = (finish.tv_sec * 1e6 + finish.tv_usec) - (start->tv_sec * 1e6 + start->tv_usec);
	return (cur);
}

void*	routine(void *all)
{
    t_all *new;
    struct timeval start;

    gettimeofday(&start, NULL);
    new = (t_all *) all;
    printf("hi from the philo #%d\n", new->a);
    if (new->a % 2 == 0)
        usleep(100);
    while (new->state[new->a - 1] == thinking) {
        pthread_mutex_lock(&new->forks[(new->a - 1) % new->num_of_philo]);
        printf("%.3f philo #%d has taken the left fork\n", cur_time(&start) * 1e-3, new->a);
        pthread_mutex_lock(&new->forks[new->a % new->num_of_philo]);
        printf("%.3f philo #%d has taken the right fork\n", cur_time(&start) * 1e-3, new->a);
        usleep(new->eatline);
        new->state[new->a - 1] = eating;
        printf("%.3f philo #%d is eating\n", cur_time(&start) * 1e-3, new->a);
        pthread_mutex_unlock(&new->forks[new->a % new->num_of_philo]);
        printf("%.3f philo #%d put the right fork\n", cur_time(&start) * 1e-3, new->a);
        pthread_mutex_unlock(&new->forks[(new->a - 1) % new->num_of_philo]);
        printf("%.3f philo #%d put the left fork\n", cur_time(&start) * 1e-3, new->a);
        new->state[new->a - 1] = sleeping;
        printf("%.3f philo #%d is sleeping\n", cur_time(&start) * 1e-3, new->a);
        usleep(new->sleepline);
        new->state[new->a - 1] = thinking;
        printf("%.3f philo #%d is thinking\n", cur_time(&start) * 1e-3, new->a);
    }
    return (all);
}

int init_threads(t_all	*all, t_struct	*gen)
{
	int count;

	gen->state = malloc(sizeof(int *) * gen->arr[0]);
	count = -1;
	while (++count < gen->arr[0])
		gen->state[count] = thinking;
	gen->forks = malloc(sizeof(pthread_mutex_t) * gen->arr[0]);
	if (!gen->forks)
		return (error(gen, "Error: memory cannot be allocated\n", 6));
	count = -1;
	while (++count < gen->arr[0])
	{
		if (pthread_mutex_init(&gen->forks[count], NULL))
			return (error(gen, "Error: cannot initialize mutex\n", 5));
	}
	count = -1;
	while (++count < gen->arr[0])
	{
		all[count].flag = 0;
		all[count].a = count + 1;
		all[count].last_meal = 0;
		all[count].ate_cnt = 0;
		all[count].num_of_philo = gen->arr[0];
		all[count].deadline = gen->arr[1];
		all[count].eatline = gen->arr[2];
		all[count].sleepline = gen->arr[3];
		all[count].eatrow = gen->arr[4];
		all[count].forks = gen->forks;
		all[count].state = gen->state;
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
