#include "philo.h"

void free_data(t_struct *gen)
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

int parse_cmdline(t_struct *gen, int argc, char **argv)
{
	int			a;
	int			b;

	gen->errno = 0;
	gen->flag = 0;
	gen->eatcnt = 0;
	a = count_dblstr(gen, argc, argv);
	if ((argc == 2 && (a != 4 && a != 5)) || ((argc != 5 && argc != 6) && !a))
		return (error(gen, "Error: invalid amount of argc\n", 1));
	b = -1;
	while (++b < 5)
	{
		if (gen->flag && gen->flag == b)
		{
			free_data(gen);
			break ;
		}
		gen->arr[b] = ft_atoi(gen->argv[b]);
		if (gen->arr[b] < 0 || gen->arr[0] > 200)
			return (error(gen, "Error: not valid amount of threads\n", 2));
	}
	return (0);
}

int main(int argc, char **argv)
{
	t_all		*philo;
	t_struct	gen;

	if (parse_cmdline(&gen, argc, argv))
		return (gen.errno);
	philo = malloc(sizeof(t_all) * gen.arr[0]);
	if (!philo)
		return (error(&gen, "Error: memory cannot be allocated\n", 7));
	init_threads(philo, &gen);
	return (0);
}
