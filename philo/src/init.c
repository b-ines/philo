/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbeaumo <inbeaumo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 13:15:22 by inbeaumo          #+#    #+#             */
/*   Updated: 2026/02/03 16:59:22 by inbeaumo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	philo_init(t_philo *current, t_monitor *monitor, t_philo **philo_head)
{
	while (current)
	{
		current->monitor = monitor;
		pthread_mutex_init(&current->eat_count_mutex, 0);
		pthread_create(&current->tid, 0, &philo_routine, current);
		current->philo_head = *philo_head;
		if (current->philo_id == current->philo_count)
			return ;
		if (current->next)
			current = current->next;
	}
}

t_philo	*get_last_philo(t_philo **head)
{
	t_philo	*temp;

	if (!head || !*head || !(*head)->next)
		return (0);
	temp = *head;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

void	ft_free_all(t_monitor *monitor, t_philo **philo_head)
{
	pthread_mutex_destroy(&monitor->printf_mutex);
	pthread_mutex_destroy(&monitor->is_dead_mtx);
	pthread_mutex_destroy(&(*philo_head)->fork_mutex);
	pthread_mutex_destroy(&(*philo_head)->eat_count_mutex);
	pthread_mutex_destroy(&(*philo_head)->last_meal_mtx);
	pthread_mutex_destroy(&monitor->last_meal_mtx);
	ft_free_list(philo_head);
	free(monitor);
}

void	threads_init(t_philo **philo_head, char **argv)
{
	t_monitor	*monitor;
	t_philo		*current;

	current = *philo_head;
	monitor = (t_monitor *)malloc(sizeof(t_monitor));
	monitor->is_dead = 0;
	monitor->total_eat_count = 0;
	if (argv[5])
		monitor->total_eat_count = ft_atoi(argv[5]);
	pthread_mutex_init(&monitor->printf_mutex, 0);
	pthread_mutex_init(&monitor->last_meal_mtx, 0);
	pthread_mutex_init(&monitor->is_dead_mtx, 0);
	pthread_mutex_init(&monitor->total_eat_count_mtx, 0);
	philo_init(current, monitor, philo_head);
	monitor->first_philo = *philo_head;
	pthread_create(&monitor->monitor_tid, 0, &monitor_routine, monitor);
	current = *philo_head;
	while (current)
	{
		pthread_join(current->tid, 0);
		if (current->philo_id == current->philo_count)
			break ;
		current = current->next;
	}
	pthread_join(monitor->monitor_tid, 0);
	ft_free_all(monitor, philo_head);
}
