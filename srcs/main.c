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
		if (a == 5)
		{
			b = -1;
			while (a > ++b)
				gen->argv[b] = splt[b];
			gen->argv[b] = NULL;
		}
		gen->flag = 1;
		free(splt);
	}
	else
		gen->argv = argv + 1;
	return (a);
}

void*	routine(void *mutex)
{
	int a;
	a = -1;
	while (++a < 20000000)
	{
		pthread_mutex_lock(mutex);
		abc++;
		pthread_mutex_unlock(mutex);
	}
	return (NULL);
}

int look_for_threads(t_all	*all, int argc, char **argv)
{
	int	a;

	all->gen.flag = 0;
	abc = 0;
	a = count_dblstr(&all->gen, argc, argv);
	if ((argc == 2 && a != 5) || (argc != 6 && !a))
		return (error(all, "Error: invalid amount of argc\n", 1));
	all->num_of_philo = ft_atoi(all->gen.argv[0]);
	if (all->num_of_philo <= 0 || all->num_of_philo > 200)
		return (error(all, "Error: not valid amount of threads\n", 2));
	all->philo = (t_philo *)malloc(sizeof(t_philo) * all->num_of_philo);
	all->philo = NULL;
	phils_to_list(all->philo, all->philo->next);
	return (init_treads(all));
}

int main(int argc, char **argv)
{
	t_all	all;
	int 	rv;

	rv = look_for_threads(&all, argc, argv);
	if (rv)
		return (rv);

	printf("*** hi %d\n", abc);
	if (all.gen.flag)
		free_data(&all.gen);
	return (0);
}
