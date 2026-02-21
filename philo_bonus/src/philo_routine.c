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
	// if (philo->philo_id % 2 == 0)
	// {
		sem_wait(philo->monitor->fork_sem);
		printf_mutexed(philo->monitor, "has taken a fork", get_timestamp_ms()
			- philo->curr_time, philo->philo_id);
		sem_wait(philo->monitor->fork_sem);
		printf_mutexed(philo->monitor, "has taken a fork", get_timestamp_ms()
			- philo->curr_time, philo->philo_id);
	// }
	// else
	// {
	// 	pthread_mutex_lock(&philo->next->fork_mutex);
	// 	printf_mutexed(philo->monitor, "has taken a fork", get_timestamp_ms()
	// 		- philo->curr_time, philo->philo_id);
	// 	pthread_mutex_lock(&philo->fork_mutex);
	// 	printf_mutexed(philo->monitor, "has taken a fork", get_timestamp_ms()
	// 		- philo->curr_time, philo->philo_id);
	// }
	printf_mutexed(philo->monitor, "is eating", get_timestamp_ms()
		- philo->curr_time, philo->philo_id);
	sem_wait(philo->last_meal_sem);
	philo->last_meal = get_timestamp_ms();
	sem_post(philo->last_meal_sem);
	eat_count_mtx(philo);
	ft_usleep(philo, philo->time_to_eat);
	sem_post(philo->monitor->fork_sem);
	sem_post(philo->monitor->fork_sem);
}

void	*philo_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->philo_id & 1)
		ft_usleep(philo, philo->time_to_think);
	while (1)
	{
		sem_wait(philo->monitor->is_dead_sem);
		if (philo->monitor->is_dead == 1)
		{
			sem_post(philo->monitor->is_dead_sem);
			return (0);
		}
		sem_post(philo->monitor->is_dead_sem);
		eating_management(philo);
		sem_wait(philo->eat_count_sem);
		if (philo->eat_count == philo->monitor->total_eat_count)
		{	
			sem_post(philo->eat_count_sem);
			return (0);
		}
		sem_post(philo->eat_count_sem);
		printf_mutexed(philo->monitor, "is sleeping", get_timestamp_ms()
			- philo->curr_time, philo->philo_id);
		ft_usleep(philo, philo->time_to_sleep);
		printf_mutexed(philo->monitor, "is thinking", get_timestamp_ms()
			- philo->curr_time, philo->philo_id);
		ft_usleep(philo, philo->time_to_think);
	}
	return (0);
}
