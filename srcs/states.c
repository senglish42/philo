/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senglish <senglish@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 11:53:49 by senglish          #+#    #+#             */
/*   Updated: 2022/01/14 11:53:49 by senglish         ###   ########.fr       */
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
	printf("%.f philo #%d has taken a fork\n", cur_time(start) *
											   1e-3, new->a);
	pthread_mutex_lock(&new->forks[(*new).a % new->arr[0]]);
	printf("%.f philo #%d has taken a fork\n", cur_time(start)
											   * 1e-3, new->a);
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

int		must_eat(t_all *new, int count)
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

void	rest(t_all *new, struct timeval *start)
{
	(*new).state = sleeping;
	printf("%.f philo #%d is sleeping\n", cur_time(start) * 1e-3,
		   new->a);
	usleep(new->sleepline * 1000);
}
