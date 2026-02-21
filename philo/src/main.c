/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbeaumo <inbeaumo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 13:15:05 by inbeaumo          #+#    #+#             */
/*   Updated: 2026/02/03 17:01:13 by inbeaumo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	main(int argc, char **argv)
{
	int		i;
	t_philo	*philo_head;

	i = 0;
	philo_head = 0;
	if (argc < 5 || argc > 6)
	{	
		printf("Correct format : <nb of philo> <time_to_die> ");
		printf("<time_to_eat> <time_to_sleep>\n");
		printf("Optionnal : <number_of_time_to_eat> as lasst argument>\n");
		return (1);
	}
	if (ft_atoi(argv[1]) == 1)
	{
		printf("0 1 has taken a fork\n");
		usleep(ft_atoi(argv[2]) * 1000);
		printf("%d 1 died\n", ft_atoi(argv[2]));
		return (0);
	}
	if (ft_atoi(argv[1]) <= 0 || ft_atoi(argv[2]) <= 0 || ft_atoi(argv[3]) <= 0 || ft_atoi(argv[4]) <= 0)
		return (1);
	while (argv[1] && i < ft_atoi(argv[1]))
		ft_addback(&philo_head, argv, i++);
	get_last_philo(&philo_head)->next = philo_head;
	threads_init(&philo_head, argv);
	return (0);
}
