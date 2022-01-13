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

enum possible_states
{
	eating, thinking, sleeping
};

typedef struct s_struct
{
	int				argc;
	char			**argv;
	int 			flag;
	long			arr[5];
	int 			errno;
	int 			eatcnt;
	pthread_mutex_t	*forks;
	pthread_t		death;
	pthread_mutex_t eatrow;
	int 			detach;
	int				*state;
}	t_struct;

typedef struct s_all
{
    int             a;
    long			deadline;
    long			eatline;
    long			sleepline;
	long 			*arr;
    int 			*flag;
    int 			ate_cnt;
    long 			last_meal;
	short			num_of_philo;
	int 			*state;
	int 			*eatcnt;
	int				detach;
	pthread_t 		th;
	pthread_mutex_t	*forks;
	pthread_mutex_t *eatrow;
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
int		fill_gen(t_struct *gen);
int		init_struct(t_all **philo, t_struct	*gen);
int		parse_cmdline(t_struct	*gen, int argc, char **argv);
void	free_data(t_struct *gen);
int		main(int argc, char **argv);
int		count_dblstr(t_struct *gen, int argc, char **argv);

//	threads.c	//
void	*routine();
int		init_threads(t_all	*all, t_struct	*gen);

//	error.c	//
int error(t_struct	*gen, char *str, int num);

//	time.c	//
long    get_time(void);

#endif
