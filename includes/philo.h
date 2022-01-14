/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senglish <senglish@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 19:45:47 by senglish          #+#    #+#             */
/*   Updated: 2022/01/14 19:53:04 by senglish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>
# include <sys/types.h>
# include <signal.h>

enum e_states
{
	eating,
	thinking,
	sleeping,
	died
};

typedef struct s_struct
{
	int				argc;
	char			**argv;
	int				flag;
	long			arr[5];
	int				errno;
	int				eatcnt;
	pthread_mutex_t	*forks;
	pthread_t		death;
	pthread_mutex_t	eatrow;
	int				detach;
	int				*state;
}	t_struct;

typedef struct s_all
{
	int				a;
	long			deadline;
	long			eatline;
	long			sleepline;
	long			*arr;
	int				*flag;
	int				ate_cnt;
	long			last_meal;
	short			num_of_philo;
	int				state;
	int				*eatcnt;
	int				detach;
	pthread_t		th;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*eatrow;
}	t_all;

//	error.c	//
int			error(t_struct *gen, char *str, int num);

//	ft_split.c	//
char		**ft_split(char const *s, char c);
int			ft_count(char const *s, char c);
char		**ft_fillarray(char **res, char const *s, char c);
int			ft_strcount(char const *s, char c);
char		**ft_freenavalniy(char **res, int elem);

//	join.c	//
int			join(t_struct *gen);

//	main.c	//
void		free_data(t_struct *gen);
int			count_dblstr(t_struct *gen, int argc, char **argv);
int			parse_cmdline(t_struct	*gen, int argc, char **argv);
int			memory_allocate(t_all	**all, t_struct	*gen);
int			main(int argc, char **argv);

//	mutex.c	//
int			init_mutex(t_struct	*gen);

//	states.c	//
void		think(t_all *new, struct timeval *start);
void		take_forks(t_all *new, struct timeval *start);
void		eat(t_all *new, struct timeval *start);
int			must_eat(t_all *new, int count);
void		rest(t_all *new, struct timeval *start);

//	threads.c	//
void		*routine(void);
int			create_threads(t_all *all, t_struct	*gen);
int			others(t_struct	*gen);

//	time.c	//
long		get_time(void);
long		cur_time(struct timeval *start);

//	utils.c	//
long int	ft_atoi(const char *str);
void		*ft_memchr(const void *s, int c, size_t n);
char		*ft_strchr(const char *s, int c);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t		ft_strlen(const char *str);

#endif
