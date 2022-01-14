/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senglish <senglish@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 11:53:36 by senglish          #+#    #+#             */
/*   Updated: 2022/01/14 11:53:36 by senglish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int join(t_struct	*gen)
{
	if (pthread_join(gen->death, NULL) != 0)
		return (error(gen, "Error: cannot join thread\n", 4));
	return (0);
}