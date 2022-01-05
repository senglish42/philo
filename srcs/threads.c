#include "philo.h"

int look_for_threads(t_all	*all, int argc, char **argv)
{
    int	a;
    int b;

    all->gen.flag = 0;
    a = count_dblstr(&all->gen, argc, argv);
    if ((argc == 2 && (a != 4 && a != 5)) || ((argc != 5 && argc != 6) && !a))
        return (error(all, "Error: invalid amount of argc\n", 1));
    b = -1;
    while (++b < 5)
    {
        if ((a && b == a) || b == argc - 1)
            all->gen.arr[b] = 0;
        else
        {
            all->gen.arr[b] = ft_atoi(all->gen.argv[b]);
            if (all->gen.arr[b] <= 0 || all->gen.arr[0] > 200)
                return (error(all, "Error: not valid amount of threads\n", 2));
        }
    }
    all->num_of_philo = all->gen.arr[0];
    t_philo *philo[all->num_of_philo];

    a = -1;
    while (++a < all->num_of_philo)
    {
        philo[a] = ft_lstnew(all, a);
        if (!philo[a])
            return (error(all, "Error: impossible to create a new list\n", 3));
        philo[a]->next = NULL;
        phils_to_list(&all->philo, philo[a]);
    }
    return (init_treads(all));
}

int init_treads(t_all	*all)
{
	pthread_t	th[all->num_of_philo];

	all->a = -1;
	all->forks = malloc(sizeof(pthread_mutex_t) * all->num_of_philo);
	if (!all->forks)
		return (error(all, "Error: cannot allocate memory\n", 6));
	while (++all->a < all->num_of_philo)
	{
		if (pthread_mutex_init(&all->forks[all->a], NULL))
			return (error(all, "Error: cannot initialize mutex\n", 5));
	}
	if (pthread_mutex_init(&all->forks[all->a], NULL))
		return (error(all, "Error: cannot initialize mutex\n", 5));
	all->a = -1;
	while (++all->a < all->num_of_philo)
	{
		if (pthread_create(&th[all->a], NULL, routine, (void *)all) != 0)
			return (error(all, "Error: cannot create thread\n", 3));
	}
	all->a = -1;
	while (++all->a < all->num_of_philo)
	{
		if (pthread_join(th[all->a], NULL) != 0)
			return (error(all, "Error: cannot join thread\n", 4));
	}
	all->a = -1;
	while (++all->a < all->num_of_philo)
		pthread_mutex_destroy(&all->forks[all->a]);
	free(all->forks);
	return (0);
}
