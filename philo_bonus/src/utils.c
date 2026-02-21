/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbeaumo <inbeaumo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 13:16:21 by inbeaumo          #+#    #+#             */
/*   Updated: 2026/02/03 19:02:50 by inbeaumo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	eat_count_mtx(t_philo *philo)
{
	int	is_dead;
	
	//pthread_mutex_lock(&philo->monitor->is_dead_mtx);
	sem_wait(philo->monitor->is_dead_sem);
	is_dead = philo->monitor->is_dead;
	sem_post(philo->monitor->is_dead_sem);
	//pthread_mutex_unlock(&philo->monitor->is_dead_mtx);
	if (is_dead != 0)	
		return ;
	//pthread_mutex_lock(&philo->eat_count_mutex);
	sem_wait(philo->eat_count_sem);
	philo->eat_count++;
	sem_post(philo->eat_count_sem);
	//pthread_mutex_unlock(&philo->eat_count_mutex);
}

void	printf_mutexed(t_monitor *monitor, char *str, long time, int philo_id)
{
	int	is_dead;
	
	// pthread_mutex_lock(&monitor->is_dead_mtx);
	// is_dead = monitor->is_dead;
	// pthread_mutex_unlock(&monitor->is_dead_mtx);
	// if (is_dead != 0)	
	// 	return ;
	
	//pthread_mutex_lock(&monitor->is_dead_mtx);
	sem_wait(monitor->is_dead_sem);
	is_dead = monitor->is_dead;
	if (is_dead != 0)
	{
		sem_post(monitor->is_dead_sem);
		//pthread_mutex_unlock(&monitor->is_dead_mtx);
		return ;
	}
	printf("%ld %d %s\n", time, philo_id, str);
	sem_post(monitor->is_dead_sem);
	//pthread_mutex_unlock(&monitor->is_dead_mtx);
}

void	printf_end_mutex(t_monitor *monitor, char *str, long time, int philo_id)
{
	//pthread_mutex_lock(&monitor->printf_mutex);
	sem_wait(monitor->printf_sem);
	printf("%ld %d %s\n", time, philo_id, str);
	sem_post(monitor->printf_sem);
	//pthread_mutex_unlock(&monitor->printf_mutex);
}

void	ft_usleep(t_philo *philo, int time_to_x)
{
	long	start;
	int	is_dead;

	start = get_timestamp_ms();
	//pthread_mutex_lock(&philo->monitor->is_dead_mtx);
	if (!philo->monitor->is_dead_sem)
	{
		printf("%p\n", philo->monitor->is_dead_sem);
		exit(1) ;
	}
	sem_wait(philo->monitor->is_dead_sem);
	is_dead = philo->monitor->is_dead;
	sem_post(philo->monitor->is_dead_sem);
	//pthread_mutex_unlock(&philo->monitor->is_dead_mtx);
	if (is_dead != 0)	
		return ;
	while (get_timestamp_ms() - start < time_to_x)
		usleep(100);
}
