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
		//pthread_mutex_init(&current->eat_count_mutex, 0);
		sem_unlink(ft_strjoin("/eat_count_p", ft_itoa(current->philo_count)));
		current->eat_count_sem = sem_open(ft_strjoin("/eat_count_p", ft_itoa(current->philo_count)), O_CREAT, 0644, 1);
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
	// pthread_mutex_destroy(&monitor->printf_mutex);
	// pthread_mutex_destroy(&monitor->is_dead_mtx);
	// pthread_mutex_destroy(&(*philo_head)->fork_mutex); 
	// pthread_mutex_destroy(&(*philo_head)->eat_count_mutex); -----
	// pthread_mutex_destroy(&(*philo_head)->last_meal_mtx);
	// pthread_mutex_destroy(&monitor->last_meal_mtx);
	//sem_close(); peut etre dans le ft_free_all
	// is_dead_sem last_meal_sem printf_sem total_eat_count_sem
	sem_close(monitor->last_meal_sem);
	sem_close(monitor->is_dead_sem);
	sem_close(monitor->printf_sem);
	sem_close(monitor->total_eat_count_sem);
	sem_close(monitor->fork_sem);
	ft_free_list(philo_head);
	sem_unlink("/eat_count_p");
	sem_unlink("/is_dead_m");
	sem_unlink("/last_meal_m");
	sem_unlink("/printf_m");
	sem_unlink("/total_eat_count_m");
	sem_unlink("/last_meal_p");
	sem_unlink("/fork_sem_m");
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
	// pthread_mutex_init(&monitor->printf_mutex, 0);
	// pthread_mutex_init(&monitor->last_meal_mtx, 0);
	// pthread_mutex_init(&monitor->is_dead_mtx, 0);
	// pthread_mutex_init(&monitor->total_eat_count_mtx, 0);
	// is_dead_sem last_meal_sem printf_sem total_eat_count_sem
	sem_unlink("/is_dead_m");
	monitor->is_dead_sem = sem_open("/is_dead_m", O_CREAT, 0644, 1);
	sem_unlink("/fork_m");
	monitor->fork_sem = sem_open("/fork_sem_m", O_CREAT, 0644, ft_atoi(argv[1]));
	sem_unlink("/last_meal_m");
	monitor->last_meal_sem = sem_open("/last_meal_m", O_CREAT, 0644, 1);
	sem_unlink("/printf_m");
	monitor->printf_sem = sem_open("/printf_m", O_CREAT, 0644, 1);
	sem_unlink("/total_eat_count_m");
	monitor->total_eat_count_sem = sem_open("/total_eat_count_m", O_CREAT, 0644, 1);
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
