#include "philo.h"

long    cur_time(struct timeval *start)
{
    struct timeval	finish;
    long 			cur;

    gettimeofday(&finish, NULL);
	cur = (finish.tv_sec * 1e6 + finish.tv_usec) - (start->tv_sec * 1e6 + start->tv_usec);
	return (cur);
}

void*	trick_or_treat(void *all)
{
	t_all			*new;
	struct timeval	start;
//	pthread_mutex_t	*death;
	int 			count;
	long			ct;
	int 			a;

	new = (t_all *)all;
	gettimeofday(&start, NULL);
	a = 0;
	while (!new->detach)
	{
		count = -1;
		while (++count < new->num_of_philo)
		{
			if (new[count].state[new[count].a - 1] != thinking)
				continue;
			ct = cur_time(&start) * 1e-3;
			if (ct && ct == new[count].deadline)
			{
				printf("%.3ld philo #%d died %ld\n", ct, (int)new[count].a,
					   (new + count)->deadline);
				exit(0);
			}
		}
	}
	return (all);
}

void*	routine(void *all)
{
    t_all			*new;
    struct timeval	start;
	int 			a;
//    long			ct;
    int 			count;

	count = 0;
    new = (t_all *) all;
    gettimeofday(&start, NULL);
    if (new->a % 2 == 0)
        usleep(10000);
//	if (!new->arr[4])
//		*new->eatcnt = 1;
	a = 0;
	while ((*new).state[new->a - 1] == thinking/* && *new->eatcnt !=
 * new->arr[4]*/)
    {
    	pthread_mutex_lock(&new->forks[(*new).a - 1 % new->arr[0]]);
        printf("%.3f philo #%d has taken the right fork\n", cur_time(&start) *
        1e-3, new->a);
        pthread_mutex_lock(&new->forks[(*new).a % new->arr[0]]);
        printf("%.3f philo #%d has taken the left fork\n", cur_time(&start)
        * 1e-3, new->a);
        (*new).deadline = (*new).deadline + new->arr[1];
	//	(*new).deadline = (*new).deadline + (*new).eatline;
		(*new).state[(*new).a - 1] = eating;
		printf("%.3f philo #%d is eating\n", cur_time(&start) * 1e-3, new->a);
        usleep(new->eatline * 1000);
        pthread_mutex_unlock(&new->forks[(new->a - 1) % new->arr[0]]);
        printf("%.3f philo #%d put the right fork\n", cur_time(&start) * 1e-3,
			   new->a);
        pthread_mutex_unlock(&new->forks[new->a % new->arr[0]]);
        printf("%.3f philo #%d put the left fork\n", cur_time(&start) *
        1e-3, new->a);
		(*new).state[new->a - 1] = sleeping;
	//	(*new).deadline = (*new).deadline + (*new).sleepline;
        printf("%.3f philo #%d is sleeping\n", cur_time(&start) * 1e-3,
			   new->a);
        usleep(new->sleepline * 1000);
		if (new->arr[4])
		{
			if (++count == new->arr[4])
			{
				pthread_mutex_lock((*new).eatrow);
				*new->eatcnt = *new->eatcnt + 1;
				printf("%d new->eatcnt %ld\n", *new->eatcnt, (*new).deadline);
				pthread_mutex_unlock((*new).eatrow);
				if (*new->eatcnt == new->arr[0])
					exit (0);
			}
		}
		(*new).state[new->a - 1] = thinking;
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
	if (gen->arr[4] && pthread_mutex_init(&gen->eatrow, NULL))
		return (error(gen, "Error: cannot initialize mutex\n", 5));
	count = -1;
	gen->eatcnt = 0;
	while (++count < gen->arr[0])
	{
		all[count].detach = 0;
		all[count].flag = &gen->flag;
		all[count].a = count + 1;
		all[count].last_meal = 0;
		all[count].ate_cnt = 0;
		all[count].arr = gen->arr;
		all[count].num_of_philo = (short)gen->arr[0];
		all[count].deadline = gen->arr[1];
		all[count].eatline = gen->arr[2];
		all[count].sleepline = gen->arr[3];
		//all[count].eatrow = gen->arr[4];
		all[count].forks = gen->forks;
		all[count].state = gen->state;
		all[count].eatrow = &gen->eatrow;
//		all[count].death = gen->death;
		all[count].eatcnt = &gen->eatcnt;
		if (pthread_create(&all[count].th, NULL, routine, &all[count]))
			return (error(gen, "Error: cannot create thread\n", 3));
	}
	if (pthread_create(&gen->death, NULL, trick_or_treat, all))
		return (error(gen, "Error: cannot create thread\n", 3));
	if (all->detach)
		return (0);
//	{
//		count = -1;
//		while (++count < gen->arr[0])
//		{
//			/*if (*/pthread_detach(gen->death);/* != 0)*/
//				return (error(gen, "Error: cannot join thread\n", 4));
//		}
//	}
//	else if (pthread_join(gen->death, NULL) != 0)
//		return (error(gen, "Error: cannot join thread\n", 8));
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
