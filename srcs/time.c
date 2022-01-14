/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senglish <senglish@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 11:53:59 by senglish          #+#    #+#             */
/*   Updated: 2022/01/14 19:39:50 by senglish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

long	get_time(void)
{
	struct timeval	tp;
	long			milliseconds;

	gettimeofday(&tp, NULL);
	milliseconds = tp.tv_sec * 1000;
	milliseconds += tp.tv_usec / 1000;
	return (milliseconds);
}

long	cur_time(struct timeval *start)
{
	struct timeval	finish;
	long			cur;

	gettimeofday(&finish, NULL);
	cur = (finish.tv_sec * 1e6 + finish.tv_usec)
		- (start->tv_sec * 1e6 + start->tv_usec);
	return (cur);
}
