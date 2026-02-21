/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbeaumo <inbeaumo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 13:16:11 by inbeaumo          #+#    #+#             */
/*   Updated: 2026/02/03 18:08:43 by inbeaumo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	eating_management(t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
	{
		pthread_mutex_lock(&philo->fork_mutex);
		printf_mutexed(philo->monitor, "has taken a fork", get_timestamp_ms()
			- philo->curr_time, philo->philo_id);
		// printf("JE SUIS %d\n", philo->philo_id);
		// printf("MON NEXT EST %d\n", philo->next->philo_id);
		pthread_mutex_lock(&philo->next->fork_mutex);
		printf_mutexed(philo->monitor, "has taken a fork", get_timestamp_ms()
			- philo->curr_time, philo->philo_id);
	}
	else
	{
		pthread_mutex_lock(&philo->next->fork_mutex);
		printf_mutexed(philo->monitor, "has taken a fork", get_timestamp_ms()
			- philo->curr_time, philo->philo_id);
		pthread_mutex_lock(&philo->fork_mutex);
		printf_mutexed(philo->monitor, "has taken a fork", get_timestamp_ms()
			- philo->curr_time, philo->philo_id);
	}
	printf_mutexed(philo->monitor, "is eating", get_timestamp_ms()
		- philo->curr_time, philo->philo_id);
	pthread_mutex_lock(&philo->last_meal_mtx);
	philo->last_meal = get_timestamp_ms();
	pthread_mutex_unlock(&philo->last_meal_mtx);
	eat_count_mtx(philo);
	ft_usleep(philo, philo->time_to_eat);
	pthread_mutex_unlock(&philo->fork_mutex);
	pthread_mutex_unlock(&philo->next->fork_mutex);
}

void	*philo_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->philo_id & 1)
		ft_usleep(philo, philo->time_to_think);
	while (1)
	{
		pthread_mutex_lock(&philo->monitor->is_dead_mtx);
		if (philo->monitor->is_dead == 1)
		{
			pthread_mutex_unlock(&philo->monitor->is_dead_mtx);
			return (0);
		}
		pthread_mutex_unlock(&philo->monitor->is_dead_mtx);
		eating_management(philo);
		pthread_mutex_lock(&philo->eat_count_mutex);
		if (philo->eat_count == philo->monitor->total_eat_count)
		{	
			pthread_mutex_unlock(&philo->eat_count_mutex);
			return (0);
		}
		pthread_mutex_unlock(&philo->eat_count_mutex);
		printf_mutexed(philo->monitor, "is sleeping", get_timestamp_ms()
			- philo->curr_time, philo->philo_id);
		ft_usleep(philo, philo->time_to_sleep);
		printf_mutexed(philo->monitor, "is thinking", get_timestamp_ms()
			- philo->curr_time, philo->philo_id);
		ft_usleep(philo, philo->time_to_think);
	}
	return (0);
}
