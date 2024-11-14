/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <sandre-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 12:11:44 by sandre-a          #+#    #+#             */
/*   Updated: 2024/11/14 20:08:18 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	simulation_ended(t_simulation *data)
{
	return (get_bool(&data->table_mtx, &data->end_simulation));
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->fork);
	write_status_debug(TAKES_LEFT_FORK, philo);
	pthread_mutex_lock(&philo->right_fork->fork);
	write_status_debug(TAKES_RIGHT_FORK, philo);
	set_long(&philo->philo_mtx, &philo->last_meal_time, gettime(1));
	inc_long(&philo->philo_mtx, &philo->meal_count);
	write_status_debug(EATING, philo);
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->left_fork->fork);
	pthread_mutex_unlock(&philo->right_fork->fork);
}

void	*start_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_all_threads(philo->data);
	inc_long(&philo->data->table_mtx, &philo->data->nbr_of_running_threads);
	set_long(&philo->philo_mtx, &philo->last_meal_time, gettime(1));
	while (!simulation_ended(philo->data))
	{
		if (philo->is_philo_full)
			return (NULL);
		eat(philo);
		write_status_debug(SLEEPING, philo);
		ft_usleep(philo->data->time_to_sleep);
		write_status_debug(THINKING, philo);
	}
	return (NULL);
}

void	*simulate_one_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	(void)philo;
	set_long(&philo->philo_mtx, &philo->last_meal_time, gettime(1));
	write_status_debug(TAKES_LEFT_FORK, philo);
	ft_usleep(philo->data->time_to_die);
	return (NULL);
}

void	simulate_philos(t_simulation *data)
{
	int	i;

	i = -1;
	while (++i < data->nbr_of_philo)
	{
		pthread_create(&data->philos[i].thread_id, NULL, start_routine,
			&data->philos[i]);
	}
}

void	*monitor_threads(void *arg)
{
	t_simulation	*data;
	long			time_since_last_meal;
	int				i;

	data = (t_simulation *)arg;
	while (!simulation_ended(data))
	{
		i = -1;
		while (++i < data->nbr_of_philo && !simulation_ended(data))
		{
			time_since_last_meal = gettime(1)
				- get_long(&data->philos->philo_mtx,
					&data->philos[i].last_meal_time);
			if (time_since_last_meal > data->time_to_die)
			{
				set_bool(&data->table_mtx, &data->end_simulation, true);
				write_status(DIED, &data->philos[i]);
			}
		}
	}
	return (NULL);
}

void	start_simulation(t_simulation *data)
{
	int i;

	if (data->nbr_of_philo == 1)
		pthread_create(&data->philos[0].thread_id, NULL, simulate_one_philo,
			&data->philos[0]);
	else
		simulate_philos(data);
	set_long(&data->table_mtx, &data->sim_start_time, gettime(1));
	pthread_create(&data->monitor_thread, NULL, monitor_threads, data);
	set_bool(&data->table_mtx, &data->all_threads_running, true);
	i = -1;
	while (++i < data->nbr_of_philo)
		pthread_join(data->philos[i].thread_id, NULL);
	pthread_join(data->monitor_thread, NULL);
}