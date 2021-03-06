/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senglish <senglish@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 11:53:41 by senglish          #+#    #+#             */
/*   Updated: 2022/01/14 21:03:35 by senglish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

void	free_data(t_struct *gen)
{
	int	a;

	a = -1;
	while (++a < gen->flag)
		free(gen->argv[a]);
}

int	count_dblstr(t_struct *gen, int argc, char **argv)
{
	char	**splt;
	int		a;
	int		b;

	a = 0;
	gen->argc = argc;
	gen->argv = argv;
	if (gen->argc == 2 && ft_strchr(gen->argv[1], 32))
	{
		splt = ft_split(gen->argv[1], 32);
		while (splt[a])
			a++;
		if (a == 4 || a == 5)
		{
			b = -1;
			while (a > ++b)
				gen->argv[b] = splt[b];
			gen->argv[b] = NULL;
			gen->flag = a;
		}
		free(splt);
	}
	else
		gen->argv = argv + 1;
	return (a);
}

int	memory_allocate(t_all	**all, t_struct	*gen)
{
	t_all		*philo;

	philo = malloc(sizeof(t_all) * gen->arr[0]);
	if (!philo)
		return (error(gen, "Error: memory cannot be allocated\n", 3));
	gen->state = malloc(sizeof(int *) * gen->arr[0]);
	if (!gen->state)
		return (error(gen, "Error: memory cannot be allocated\n", 4));
	gen->forks = malloc(sizeof(pthread_mutex_t) * gen->arr[0]);
	if (!gen->forks)
		return (error(gen, "Error: memory cannot be allocated\n", 5));
	*all = philo;
	return (0);
}

int	parse_cmdline(t_struct *gen, int argc, char **argv)
{
	int			a;
	int			b;

	gen->errno = 0;
	gen->flag = 0;
	gen->eatcnt = 0;
	gen->dead = 0;
	a = count_dblstr(gen, argc, argv);
	if ((argc == 2 && (a != 4 && a != 5)) || ((argc != 5 && argc != 6) && !a))
		return (error(gen, "Error: invalid amount of argc\n", 1));
	b = -1;
	while (gen->argv[++b])
	{
		gen->arr[b] = ft_atoi(gen->argv[b]);
		if (gen->arr[b] < 0 || gen->arr[0] > 200)
			return (error(gen, "Error: not valid amount of threads\n", 2));
		if (gen->flag && gen->flag - 1 == b)
			free_data(gen);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_all		*philo;
	t_struct	gen;

	philo = NULL;
	if (parse_cmdline(&gen, argc, argv))
		return (gen.errno);
	if (memory_allocate(&philo, &gen))
		return (gen.errno);
	if (init_mutex(&gen))
		return (gen.errno);
	if (create_threads(philo, &gen))
		return (gen.errno);
	if (join(philo, &gen))
		return (gen.errno);
	if (destroy_mutex(philo, &gen))
		return (gen.errno);
	free(philo);
	free(gen.state);
	free(gen.forks);
	return (0);
}
