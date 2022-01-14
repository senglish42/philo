/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senglish <senglish@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 11:53:19 by senglish          #+#    #+#             */
/*   Updated: 2022/01/14 19:33:07 by senglish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	error(t_struct	*gen, char *str, int num)
{
	gen->errno = num;
	if (gen->flag)
		free_data(gen);
	printf("%s", str);
	return (gen->errno);
}
