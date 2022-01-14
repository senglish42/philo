/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senglish <senglish@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 11:53:49 by senglish          #+#    #+#             */
/*   Updated: 2022/01/14 19:35:15 by senglish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

void	think(t_all *new, struct timeval *start)
{
	(*new).state = thinking;
	printf("%.f philo #%d is thinking\n", cur_time(start) * 1e-3, new->a);
}

void	take_forks(t_all *new, struct timeval *start)
{
	pthread_mutex_lock(&new->forks[(*new).a - 1 % new->arr[0]]);
	printf("%.f philo #%d has taken a fork\n", cur_time(start) * 1e-3, new->a);
	if ((*new).num_of_philo > 1)
		pthread_mutex_lock(&new->forks[(*new).a % new->arr[0]]);
	else
		while (1)
			usleep(100);
	printf("%.f philo #%d has taken a fork\n", cur_time(start) * 1e-3, new->a);
}

void	eat(t_all *new, struct timeval *start)
{
	float	ct;

	(*new).state = eating;
	(*new).deadline = (*new).deadline + new->arr[1];
	ct = cur_time(start) * 1e-3;
	printf("%.f philo #%d is eating\n", cur_time(start) * 1e-3, new->a);
	while (cur_time(start) * 1e-3 - ct < new->eatline)
		usleep(100);
	pthread_mutex_unlock(&new->forks[(new->a - 1) % new->arr[0]]);
	pthread_mutex_unlock(&new->forks[new->a % new->arr[0]]);
}

int	must_eat(t_all *new, int count)
{
	if (++count == new->arr[4])
	{
		pthread_mutex_lock((*new).eatrow);
		*new->eatcnt = *new->eatcnt + 1;
		pthread_mutex_unlock((*new).eatrow);
	}
	return (count);
}

void	rest(t_all *new, struct timeval *start)
{
	float			ct;

	(*new).state = sleeping;
	ct = cur_time(start) * 1e-3;
	printf("%.f philo #%d is sleeping\n", ct, new->a);
	while (cur_time(start) * 1e-3 - ct < new->sleepline)
		usleep(100);
}
