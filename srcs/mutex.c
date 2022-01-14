/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senglish <senglish@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 11:53:44 by senglish          #+#    #+#             */
/*   Updated: 2022/01/14 21:56:17 by senglish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	init_mutex(t_struct	*gen)
{
	int	count;

	count = -1;
	while (++count < gen->arr[0])
	{
		if (pthread_mutex_init(&gen->forks[count], NULL))
			return (error(gen, "Error: cannot initialize mutex\n", 6));
	}
	if (gen->arr[4] && pthread_mutex_init(&gen->eatrow, NULL))
		return (error(gen, "Error: cannot initialize mutex\n", 7));
	return (0);
}

int	destroy_mutex(t_all *all, t_struct *gen)
{
	int	count;

	count = -1;
	if (gen->arr[4] && pthread_mutex_destroy(&gen->eatrow))
		return (error(gen, "Error: cannot destroy mutex\n", 13));
	while (++count < gen->arr[0])
	{
		pthread_mutex_unlock(&all->forks[count]);
		if (pthread_mutex_destroy(&all->forks[count]))
			return (error(gen, "Error: cannot destroy mutex1\n", 12));
	}
	return (0);
}
