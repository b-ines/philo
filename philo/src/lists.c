/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbeaumo <inbeaumo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 13:15:48 by inbeaumo          #+#    #+#             */
/*   Updated: 2026/02/03 16:59:01 by inbeaumo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_addback(t_philo **head, char **argv, int i)
{
	t_philo	*new_node;
	t_philo	*last;

	new_node = create_node(argv, i);
	new_node->philo_head = *head;
	if (!(*head))
	{
		*head = new_node;
		return ;
	}
	last = *head;
	while (last->next)
		last = last->next;
	last->next = new_node;
	new_node->prev = last;
}

long	get_timestamp_ms(void)
{
	struct timeval	tv;
	struct timezone	tz;

	gettimeofday(&tv, &tz);
	return (((tv.tv_sec) * 1000) + ((tv.tv_usec) / 1000));
}

t_philo	*create_node(char **argv, int i)
{
	t_philo	*new_node;

	new_node = (t_philo *)malloc(sizeof(t_philo));
	new_node->index = i;
	new_node->philo_id = i + 1;
	new_node->philo_count = ft_atoi(argv[1]);
	new_node->time_to_die = ft_atoi(argv[2]);
	new_node->time_to_eat = ft_atoi(argv[3]);
	new_node->time_to_sleep = ft_atoi(argv[4]);
	new_node->eat_count = 0;
	if ((new_node->time_to_die - new_node->time_to_eat
			- new_node->time_to_sleep) <= 0)
		new_node->time_to_think = 0;
	else
		new_node->time_to_think = (new_node->time_to_die
				- new_node->time_to_eat - new_node->time_to_sleep) / 2;
	pthread_mutex_init(&new_node->fork_mutex, 0);
	pthread_mutex_init(&new_node->last_meal_mtx, 0);
	new_node->curr_time = get_timestamp_ms();
	new_node->last_meal = new_node->curr_time;
	new_node->prev = 0;
	new_node->next = 0;
	return (new_node);
}

void	ft_free_list(t_philo **philo)
{
	t_philo	*temp;
	t_philo	*head;

	if (!philo || !(*philo))
		return ;
	head = *philo;
	while ((*philo)->next != head)
	{
		temp = (*philo)->next;
		free(*philo);
		*philo = temp;
	}
	free(*philo);
	*philo = 0;
}
