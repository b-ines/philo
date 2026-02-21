/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbeaumo <inbeaumo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 13:16:29 by inbeaumo          #+#    #+#             */
/*   Updated: 2026/02/03 16:51:27 by inbeaumo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <fcntl.h>

typedef struct s_philo	t_philo;

typedef struct s_monitor
{
	t_philo			*first_philo; // is_dead_sem last_meal_sem printf_sem total_eat_count_sem
	sem_t			*printf_sem;
	//pthread_mutex_t	printf_mutex;
	int				is_dead;
	sem_t			*is_dead_sem;
	sem_t			*last_meal_sem;
	//pthread_mutex_t	is_dead_mtx;
	//pthread_mutex_t	last_meal_mtx;
	pthread_t		monitor_tid;
	int				total_eat_count;
	sem_t			*total_eat_count_sem;
	sem_t			*fork_sem;
	//pthread_mutex_t	total_eat_count_mtx;

}	t_monitor;

struct s_philo
{
	int					index;
	int					philo_id;
	int					philo_count;
	pthread_t			tid;
	//pthread_mutex_t		fork_mutex;
	long				start_time;
	long				time_to_die;
	long				time_to_sleep;
	int					eat_count;
	sem_t				*eat_count_sem;
	//pthread_mutex_t		eat_count_mutex;
	long				time_to_eat;
	long				time_to_think;
	long				curr_time;
	long				last_meal;
	sem_t				*last_meal_sem;
	//pthread_mutex_t		last_meal_mtx;
	struct s_philo		*next;
	struct s_philo		*prev;
	struct s_philo		*philo_head;
	struct s_monitor	*monitor;
} ;

//threads.c
void	*monitor_routine(void *data);
void	eating_management(t_philo *philo);
void	*philo_routine(void *data);

//lists.c
t_philo	*create_node(char **argv, int i);
void	ft_addback(t_philo **head, char **argv, int i);
long	get_timestamp_ms(void);
t_philo	*create_node(char **argv, int i);
void	print_node(t_philo *current);
void	ft_free_list(t_philo **philo);

//utils.c
void	printf_mutexed(t_monitor *monitor, char *str, long time, int philo_id);
void	printf_end_mutex(t_monitor *monitor, char *str, long time,
			int philo_id);
void	ft_usleep(t_philo *philo, int time_to_x);
void	eat_count_mtx(t_philo *philo);

//init.c
void	philo_init(t_philo *current, t_monitor *monitor, t_philo **philo_head);
t_philo	*get_last_philo(t_philo **head);
void	threads_init(t_philo **philo_head, char **argv);

//ft_atoi.c
int		ft_atoi(const char *str);
int		ft_strlen(char *str);
char	*ft_strcat(char *dest, char *src);

//ft_itoa.c
char    *ft_itoa(int nb);

//ft_strjoin.c
char    *ft_strjoin(char *s1, char *s2);

#endif