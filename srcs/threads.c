/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senglish <senglish@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 11:53:53 by senglish          #+#    #+#             */
/*   Updated: 2022/01/14 11:53:53 by senglish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

void 	*die(t_all *new, long ct, int count)
{
	pthread_mutex_lock((*new).eatrow);
	(*new).state = died;
	printf("%ld philo #%d died %ld %d\n", ct, (int)new[count].a,
		   (new + count)->deadline, count);
	pthread_mutex_unlock((*new).eatrow);
	return (new);
}

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
				return(die(new, ct, count));
		}
	}
	return (new);
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
	while (1)
    {
		if ((*new).state != died)
			think(new, &start);
		if ((*new).state != died)
			take_forks(new, &start);
		if ((*new).state != died)
			eat(new, &start);
		if ((*new).state != died && new->arr[4])
			count = must_eat(new, count);
		if ((*new).state != died)
			rest(new, &start);
		else
			break ;
    }
	return (new);
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
