#include "philo.h"

void if_flag(s_struct *gen)
{
	int	a;

	a = 0;
	while (gen->argv[a])
	{
		printf("here %d\n", a);
		free(gen->argv[a++]);
	}
}

int	count_dblstr(s_struct *gen, int argc, char **argv)
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

int main(int argc, char **argv)
{
	s_struct gen;
	int	a;
	long int b;

	gen.flag = 0;
	abc = 0;
	a = count_dblstr(&gen, argc, argv);
	if ((argc == 2 && a != 5) || (argc != 6 && !a))
	{
		printf("Error: invalid amount of argc\n");
		return (1);
	}
	b = ft_atoi(gen.argv[0]);
	if (b <= 0 || b > 200)
	{
		printf("Error: not valid amount of threads\n");
		return (2);
	}
	pthread_t	th[b];
	pthread_mutex_t mutex;

	pthread_mutex_init(&mutex, NULL);
	a = -1;
	while (++a < b)
	{
		if (pthread_create(&th[a], NULL, routine, &mutex) != 0)
			return 1;
		usleep(500);
	}
	a = -1;
	while (++a < b)
	{
		if (pthread_join(th[a], NULL) != 0)
			return 2;
	}
	pthread_mutex_destroy(&mutex);
	printf("*** hi %d\n", abc);
	if (gen.flag)
		if_flag(&gen);
	return (0);
}
