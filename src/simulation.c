/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 12:11:44 by sandre-a          #+#    #+#             */
/*   Updated: 2024/11/17 15:49:12 by sandre-a         ###   ########.fr       */
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
	write_status(TAKES_LEFT_FORK, philo);
	pthread_mutex_lock(&philo->right_fork->fork);
	write_status(TAKES_RIGHT_FORK, philo);
	set_long(&philo->philo_mtx, &philo->last_meal_time, gettime(1));
	inc_dec_long(&philo->philo_mtx, &philo->meal_count, '+');
	write_status(EATING, philo);
	ft_usleep(philo->data->time_to_eat);
	if (philo->data->nbr_max_meals > 0
		&& philo->meal_count == philo->data->nbr_max_meals)
		set_bool(&philo->philo_mtx, &philo->is_philo_full, true);
	pthread_mutex_unlock(&philo->left_fork->fork);
	pthread_mutex_unlock(&philo->right_fork->fork);
}

void	*start_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_all_threads(philo->data);
	inc_dec_long(&philo->data->table_mtx, &philo->data->num_running_threads,
		'+');
	set_long(&philo->philo_mtx, &philo->last_meal_time, gettime(1));
	while (!simulation_ended(philo->data))
	{
		if (philo->is_philo_full || simulation_ended(philo->data))
			break ;
		eat(philo);
		if (!simulation_ended(philo->data))
			write_status(SLEEPING, philo);
		ft_usleep(philo->data->time_to_sleep);
		if (!simulation_ended(philo->data))
			write_status(THINKING, philo);
	}
	inc_dec_long(&philo->data->table_mtx, &philo->data->num_running_threads,
		'-');
	return (NULL);
}

void	*one_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	(void)philo;
	set_long(&philo->philo_mtx, &philo->last_meal_time, gettime(1));
	write_status(TAKES_LEFT_FORK, philo);
	return (NULL);
}

void	*monitor_threads(void *arg)
{
	t_simulation	*data;
	long			time_since_last_meal;
	int				i;

	data = (t_simulation *)arg;
	while (!simulation_ended(data) && get_long(&data->table_mtx,
			&data->num_running_threads))
	{
		i = -1;
		while (++i < data->nbr_of_philo && !simulation_ended(data))
		{
			time_since_last_meal = gettime(1)
				- get_long(&data->philos->philo_mtx,
					&data->philos[i].last_meal_time);
			if (time_since_last_meal >= data->time_to_die
				&& !get_bool(&data->philos[i].philo_mtx,
					&data->philos->is_philo_full))
			{
				if (!simulation_ended(data))
					write_status(DIED, &data->philos[i]);
				set_bool(&data->table_mtx, &data->end_simulation, true);
			}
		}
	}
	return (NULL);
}

void	start_simulation(t_simulation *d)
{
	int	i;

	if (d->nbr_of_philo == 1)
		pthread_create(&d->philos[0].thread_id, NULL, one_philo, &d->philos[0]);
	else
	{
		i = -1;
		while (++i < d->nbr_of_philo)
			pthread_create(&d->philos[i].thread_id, NULL, start_routine,
				&d->philos[i]);
	}
	set_long(&d->table_mtx, &d->sim_start_time, gettime(1));
	ft_usleep(1);
	pthread_create(&d->monitor_thread, NULL, monitor_threads, d);
	set_bool(&d->table_mtx, &d->all_threads_running, true);
	i = -1;
	while (++i < d->nbr_of_philo)
	{
		pthread_join(d->philos[i].thread_id, NULL);
		pthread_mutex_destroy(&d->forks[i].fork);
		pthread_mutex_destroy(&d->philos[i].philo_mtx);
	}
	pthread_join(d->monitor_thread, NULL);
	pthread_mutex_destroy(&d->table_mtx);
	pthread_mutex_destroy(&d->write_mtx);
}
