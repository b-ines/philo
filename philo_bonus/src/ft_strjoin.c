#include "../philo.h"

char    *ft_strjoin(char *s1, char *s2)
{
	char    *str;
	int     i;
	int     j;

	if (!s1 || !s2)
		return (0);
	i = 0;
	j = 0;
	str = malloc((ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (0);
	while (s1[i])
	{	
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{	
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = 0;
	free(s2);
	return (str);
}
