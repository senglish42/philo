#include "philo.h"

void free_data(t_struct *gen)
{
	int	a;

	a = 0;
	while (gen->argv[a])
	{
		printf("here %d\n", a);
		free(gen->argv[a++]);
	}
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
			if (a == 4)
			{
				gen->argv[b] = 0;
				gen->argv[b + 1] = NULL;
			}
			else
				gen->argv[b] = NULL;
			gen->flag = 1;
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
		if ((a && b == a) || b == argc - 1)
			gen->arr[b] = 0;
		else
		{
			gen->arr[b] = ft_atoi(gen->argv[b]);
			if (gen->arr[b] < 0 || gen->arr[0] > 200)
				return (error(gen, "Error: not valid amount of threads\n", 2));
		}
	}
	return (0);
}

//int init_struct(t_all **philo, t_struct	*gen)
//{
//	(*philo)->num_of_philo = (short)gen->arr[0];
//	(*philo)->deadline = gen->arr[1];
//	(*philo)->eatline = gen->arr[2];
//	(*philo)->sleepline = gen->arr[3];
//	(*philo)->eatrow = gen->arr[4];
//	return (0);
//}

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
	if (gen.flag)
		free_data(&gen);
	return (0);
}
