#include "philo.h"

void	phils_to_list(t_philo **philo, t_philo *new)
{
	t_philo	*phils;

	if (*philo == NULL)
		*philo = new;
	else
	{
		phils = ft_lstlast(*philo);
		phils->next = new;
		new->next = NULL;
	}
}

t_philo	*ft_lstlast(t_philo *philo)
{
	while (philo->next)
		philo = philo->next;
	return (philo);
}

t_philo	*ft_lstnew(t_all *all, int num)
{
	t_philo *philo;

	philo = (t_philo *) malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->num = num;
	philo->deadline = (int)all->gen.argv[1];
	philo->eatline = (int)all->gen.argv[2];
	philo->deadline = (int)all->gen.argv[3];
	return (philo);
}
