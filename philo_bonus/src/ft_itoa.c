#include "../philo.h"

int itoa_size(int nb)
{
    int i;

    i = 0;
    if (nb < 0)
        nb *= -1;
    while (nb)
    {
        nb /= 10;
        i++;
    }
    return (i);
}

char    *ft_itoa(int nb)
{
    char    *dest;
    int i;
    int count;

    i = 0;
    count = itoa_size(nb);
    if (nb < 0 || count == 0)
        count++;
    dest = malloc(sizeof(char) * (count + 1));
    if (!dest)
        return (0);
    if (nb < 0)
    {
        nb *= -1;
        dest[0] = '-';
        i++;
    }
    dest[count] = 0;
    while (count > i)
    {
        count--;
        dest[count] = (nb % 10) + '0';
        nb /= 10;
    }
    return (dest);
}