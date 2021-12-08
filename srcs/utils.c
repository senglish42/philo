#include "philo.h"

long int	ft_atoi(const char *str)
{
	int			a;
	long int	b;
	long int	c;

	a = 0;
	b = 1;
	c = 0;
	while ((str[a] >= 9 && str[a] <= 13) || str[a] == 32 || str[a] == 127)
		a++;
	if (*(str + a) == '+')
		a++;
	else if (*(str + a) == '-')
	{
		b = -b;
		a++;
	}
	while (*(str + a) >= 48 && *(str + a) <= 57)
		c = c * 10 + ((*(str + a++) - 48));
	c = b * c;
	return (c);
}

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			a;
	unsigned char	*b;

	a = -1;
	b = (unsigned char *)s;
	while (++a < n)
	{
		if (*(b + a) == (unsigned char)c)
			return (b + a);
	}
	return (0);
}

char	*ft_strchr(const char *s, int c)
{
	return (ft_memchr(s, c, ft_strlen(s) + 1));
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	a;

	a = 0;
	if (!dst && !src)
		return (0);
	while (dstsize > a)
	{
		dst[a] = src[a];
		if (!src[a])
			return (ft_strlen(src));
		a++;
	}
	dst[a - 1] = '\0';
	return (ft_strlen(src));
}

size_t	ft_strlen(const char *str)
{
	size_t	a;

	a = 0;
	while (*(str + a) != '\0')
		a++;
	return (a);
}
