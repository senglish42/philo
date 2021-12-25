#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>
# include <sys/types.h>
# include <signal.h>

int abc;

typedef struct s_struct
{
	int			argc;
	char		**argv;
	int 		flag;
	int			arr[5];
}	t_struct;

typedef struct s_philo
{
	int				num;
	int				deadline;
	int				eatline;
	int				sleepline;
	int				eatrow;
	struct s_philo	*next;
}	t_philo;

typedef struct s_all
{
    int             a;
	t_struct		gen;
	t_philo			*philo;
	long int		num_of_philo;
	pthread_mutex_t	life;
	pthread_mutex_t	death;
}	t_all;

//	utils.c	//
size_t		ft_strlen(const char *str);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
char 		*ft_strchr(const char *s, int c);
void 		*ft_memchr(const void *s, int c, size_t n);
long int	ft_atoi(const char *str);

//	ft_split.c	//
char	**ft_split(char const *s, char c);
int		ft_count(char const *s, char c);
char	**ft_fillarray(char **res, char const *s, char c);
int		ft_strcount(char const *s, char c);
char	**ft_freenavalniy(char **res, int elem);

//	main.c	//
void	ft_rotate(t_philo **philo);
void	free_data(t_struct *gen);
int		main(int argc, char **argv);
int		count_dblstr(t_struct *gen, int argc, char **argv);
void	*routine();

//	threads.c	//
int look_for_threads(t_all	*all, int argc, char **argv);
int init_treads(t_all	*all);

//	error.c	//
int error(t_all *all, char *str, int num);

//	lists.c	//
void	ft_lstadd_back(t_philo **lst, t_philo *new);
void	phils_to_list(t_philo **philo, t_philo *new);
t_philo	*ft_lstlast(t_philo *philo);
t_philo	*ft_lstnew(t_all *all, int num);
void	ft_lstclear(t_philo **philo);

#endif
