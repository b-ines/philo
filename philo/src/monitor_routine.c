/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbeaumo <inbeaumo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 16:03:50 by inbeaumo          #+#    #+#             */
/*   Updated: 2026/02/03 18:08:48 by inbeaumo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	death_timer(t_philo *current, t_monitor *monitor)
{
	pthread_mutex_lock(&current->last_meal_mtx);
	if (get_timestamp_ms() - current->last_meal > current->time_to_die)
	{
		pthread_mutex_lock(&monitor->is_dead_mtx);
		if (monitor->is_dead != 1)
		{
			monitor->is_dead = 1;
			printf_end_mutex(monitor, "died", get_timestamp_ms()
			- current->curr_time, current->philo_id);
		}
		pthread_mutex_unlock(&monitor->is_dead_mtx);
		pthread_mutex_unlock(&current->last_meal_mtx);
		return (1);
	}
	pthread_mutex_unlock(&current->last_meal_mtx);
	return (0);
}

int	all_philo_ate(t_philo *current, t_monitor *monitor)
{
	t_philo	*temp;
	int		i;

	temp = current->philo_head;
	i = 0;
	if (monitor->total_eat_count == 0)
		return (0);
	while (i < temp->philo_count)
	{
		pthread_mutex_lock(&temp->eat_count_mutex);
		if (temp->eat_count < monitor->total_eat_count)
		{	
			pthread_mutex_unlock(&temp->eat_count_mutex);
			return (0);
		}
		pthread_mutex_unlock(&temp->eat_count_mutex);
		temp = temp->next;
		i++;
	}
	return (1);
}

void	*monitor_routine(void *data)
{
	t_monitor	*monitor;
	t_philo		*current;

	monitor = (t_monitor *)data;
	monitor->monitor_tid = pthread_self();
	while (1)
	{
		current = monitor->first_philo;
		while (current)
		{
			if (death_timer(current, monitor))
				return (0);
			if (all_philo_ate(current, monitor))
				return (0);
			current = current->next;
			usleep(50);
		}
	}
	return (0);
}
