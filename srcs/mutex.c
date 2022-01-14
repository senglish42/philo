/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senglish <senglish@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 11:53:44 by senglish          #+#    #+#             */
/*   Updated: 2022/01/14 13:11:03 by senglish         ###   ########.fr       */
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
			return (error(gen, "Error: cannot initialize mutex\n", 5));
	}
	if (gen->arr[4] && pthread_mutex_init(&gen->eatrow, NULL))
		return (error(gen, "Error: cannot initialize mutex\n", 5));
	return (0);
}
