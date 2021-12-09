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

typedef struct t_struct
{
	int		argc;
	char	**argv;
	int 	flag;
}	s_struct;

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
int		main(int argc, char **argv);
int		count_dblstr(s_struct *gen, int argc, char **argv);
void	*routine();

#endif
