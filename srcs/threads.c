/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senglish <senglish@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 11:53:53 by senglish          #+#    #+#             */
/*   Updated: 2022/01/14 22:21:40 by senglish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

void	*die(t_all *new, long ct, int count)
{
	pthread_mutex_lock((*new).eatrow);
	*new->dead = 1;
	printf("%ld philo #%d died\n", ct, (int)new[count].num);
	pthread_mutex_unlock((*new).eatrow);
	return (new);
}

void	*trick_or_treat(void *all)
{
	t_all			*new;
	struct timeval	start;
	int				count;
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
			if (new[count].state == eating)
				continue ;
			ct = current(&start) * 1e-3;
			if (ct < new[count].deadline)
				usleep(100);
			else
				return (die(new, ct, count));
		}
	}
	return (new);
}

void	*routine(void *all)
{
	t_all			*new;
	struct timeval	start;
	int				count;
	float			ct;

	count = 0;
	new = (t_all *)all;
	gettimeofday(&start, NULL);
	ct = current(&start) * 1e-3;
	if (new->num % 2)
		usleep(10000);
	while (*new->dead != 1 && *new->eatcnt != new->arr[0])
	{
		if (*new->dead != 1)
			think(new, &start);
		if (*new->dead != 1)
			take_forks(new, &start);
		if (*new->dead != 1)
			eat(new, &start);
		if (*new->dead != 1 && new->arr[4])
			count = must_eat(new, count);
		if (*new->dead != 1)
			rest(new, &start);
	}
	return (NULL);
}

int	create_threads(t_all *all, t_struct	*gen)
{
	int	count;

	count = -1;
	while (++count < gen->arr[0])
	{
		all[count].num = count + 1;
		all[count].arr = gen->arr;
		all[count].num_of_philo = (short)gen->arr[0];
		all[count].deadline = gen->arr[1];
		all[count].eatline = gen->arr[2];
		all[count].sleepline = gen->arr[3];
		all[count].forks = gen->forks;
		all[count].eatrow = &gen->eatrow;
		all[count].eatcnt = &gen->eatcnt;
		all[count].dead = &gen->dead;
		if (pthread_create(&all[count].th, NULL, routine, &all[count]))
			return (error(gen, "Error: cannot create thread\n", 8));
	}
	if (pthread_create(&gen->death, NULL, trick_or_treat, all))
		return (error(gen, "Error: cannot create thread\n", 9));
	return (0);
}
