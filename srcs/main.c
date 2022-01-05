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

void	ft_rotate(t_philo **philo)
{
    t_philo	*philo1;
    t_philo	*philo2;

    if (!*philo || !(*philo)->next)
        return ;
    philo1 = *philo;
    philo2 = philo1->next;
    philo1->next = NULL;
    ft_lstadd_back(&philo2, philo1);
    *philo = philo2;
}

void*	routine(void *all)
{
	t_all *new;

    new = all;
    int a;
	a = -1;
    while (++a < 2)
	{
        pthread_mutex_lock(&new->forks[new->a]);
        printf("Philo #%d has taken a fork\n", new->a);
        printf("Philo #%d is eating %d\n", new->a, a);
		abc++;
		pthread_mutex_unlock(&new->forks[new->a]);
    }
    //ft_rotate(&new->philo);
    return (all);
}

int main(int argc, char **argv)
{
	t_all	all;
	int 	rv;

	all.philo = NULL;
	rv = look_for_threads(&all, argc, argv);
	if (rv)
		return (rv);
	printf("*** hi %d\n", abc);
	if (all.gen.flag)
		free_data(&all.gen);
	return (0);
}
