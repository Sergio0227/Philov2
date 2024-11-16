/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <sandre-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 20:06:57 by sandre-a          #+#    #+#             */
/*   Updated: 2024/11/16 13:51:16 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "../includes/color.h"
# include "../includes/gc.h"
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <sys/time.h>

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKES_LEFT_FORK,
	TAKES_RIGHT_FORK,
	DIED
}			t_philo_status;

typedef struct s_simulation	t_simulation;

typedef struct s_fork
{
	pthread_mutex_t			fork;
	int						fork_id;
}							t_fork;

typedef struct s_philo
{
	int						philo_id;
	long					meal_count;
	bool					is_philo_full;
	long					last_meal_time;
	t_fork					*left_fork;
	t_fork					*right_fork;
	pthread_t				thread_id;
	pthread_mutex_t			philo_mtx;
	t_simulation			*data;				//!POINTER TO THE MAIN STRUCT
}							t_philo;

//^ table_mtx is used to synchronize and prevent race conditions, ensuring
//^ consistent updates to shared vars like end_simulation and threads_ready.

struct						s_simulation
{
	long					nbr_of_philo;		//~1st argument
	long					time_to_die;		//!2st argument
	long					time_to_eat;		//*3st argument
	long					time_to_sleep;		//^4st argument
	long					nbr_max_meals;		//?last argument (optional)
	long					sim_start_time;
	bool					end_simulation;
	bool					all_threads_running;
	pthread_t				monitor_thread;
	pthread_mutex_t			write_mtx;
	pthread_mutex_t			table_mtx;
	t_fork					*forks;
	t_philo					*philos;
	t_gc					*gc;
};

long	ft_atol(const char *nptr);
void	start_simulation(t_simulation *data);
void	print_intro(void);
void	set_bool(pthread_mutex_t *mutex, bool *dest, bool value);
bool	get_bool(pthread_mutex_t *mutex, bool *value);
void	set_long(pthread_mutex_t *mutex, long *dest, long value);
long	get_long(pthread_mutex_t *mutex, long *value);
void	inc_long(pthread_mutex_t *mutex, long *dest);
long	gettime(int format);
int		ft_usleep(size_t milliseconds);
void	wait_all_threads(t_simulation *data);
void	write_status(t_philo_status status, t_philo *philo);
bool	simulation_ended(t_simulation *data);


//! DEBUGGING
void	print_philos_and_forks(t_simulation *data);
void	write_status_debug(t_philo_status status, t_philo *philo);

#endif