/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senglish <senglish@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 11:53:36 by senglish          #+#    #+#             */
/*   Updated: 2022/01/14 20:33:23 by senglish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	join(t_all *all, t_struct *gen)
{
	int	count;

	if (pthread_join(gen->death, NULL) != 0)
		return (error(gen, "Error: cannot join thread\n", 10));
	count = -1;
	while (++count < gen->arr[0])
	{
		if (pthread_join(all[count].th, NULL) != 0)
			return (error(gen, "Error: cannot join thread\n", 11));
	}
	return (0);
}
