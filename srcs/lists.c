#include "philo.h"

//void	ft_lstadd_back(t_philo **lst, t_philo *new)
//{
//    t_philo	*temp;
//
//    if (!new)
//        return ;
//    temp = ft_lstlast(*lst);
//    temp->next = new;
//}
//
//void	phils_to_list(t_philo **philo, t_philo *new)
//{
//	t_philo	*phils;
//
//	//phils = NULL;
//	printf("ok\n");
//	if (*philo == NULL) {
//		printf("first\n");
//		*philo = new;
//	}
//	else
//	{
//		printf("hi\n");
//		phils = ft_lstlast(*philo);
//		phils->next = new;
//		new->next = NULL;
//	}
//	printf("done\n");
//}
//
//void	ft_lstclear(t_philo **philo)
//{
//	t_philo	*temp;
//
//	if (!(*philo))
//		return ;
//	while (*philo)
//	{
//		temp = (*philo)->next;
//		free(*philo);
//		*philo = NULL;
//		*philo = temp;
//	}
//	*philo = NULL;
//}
//
//t_philo	*ft_lstlast(t_philo *philo)
//{
//	while (philo->next)
//		philo = philo->next;
//	return (philo);
//}
//
//t_philo	*ft_lstnew(t_all *all, int num)
//{
//	t_philo *philo;
//
//	if (!all)
//		return (NULL);
//	philo = (t_philo *)malloc(sizeof(t_philo));
//	if (!philo)
//		return (NULL);
//	philo->num = num;
//	philo->deadline = all->gen.arr[1];
//	philo->eatline = all->gen.arr[2];
//	philo->sleepline = all->gen.arr[3];
//	philo->eatrow = all->gen.arr[4];
//	return (philo);
//}
