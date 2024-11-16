/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <sandre-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:08:35 by sandre-a          #+#    #+#             */
/*   Updated: 2024/11/16 14:51:50 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long	ft_atol(const char *nptr)
{
	long	sign;
	long	result;

	result = 0;
	sign = 1;
	while (*nptr == 32 || (*nptr >= 7 && *nptr <= 13))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	if (!(*nptr >= '0' && *nptr <= '9'))
		return (LONG_MIN);
	while (*nptr >= '0' && *nptr <= '9')
	{
		result *= 10;
		result += *nptr - '0';
		nptr++;
	}
	if (*nptr != 0)
		return (LONG_MIN);
	result *= sign;
	return (result);
}

void	write_status(t_philo_status status, t_philo *philo)
{
	long	time;

	pthread_mutex_lock(&philo->data->write_mtx);
	time = gettime(1) - philo->data->sim_start_time -1;
	if (status == TAKES_LEFT_FORK)
		printf("%ld %d has taken a fork\n", time, philo->philo_id);
	else if (status == TAKES_RIGHT_FORK)
		printf("%ld %d has taken a fork\n", time, philo->philo_id);
	else if (status == EATING)
		printf("%ld %d is eating\n", time, philo->philo_id);
	else if (status == SLEEPING)
		printf("%ld %d is sleeping\n", time, philo->philo_id);
	else if (status == THINKING)
		printf("%ld %d is thinking\n", time, philo->philo_id);
	else if (status == DIED)
		printf("%ld %d died\n", time, philo->philo_id);
	pthread_mutex_unlock(&philo->data->write_mtx);
}

//! DEBUGGING//////////////////////////////////////////////////////////////////
void	print_philos_and_forks(t_simulation *data)
{
	int	i;

	i = -1;
	while (++i < data->nbr_of_philo)
	{
		printf("Philosopher %d has fork %d and fork %d\n",
			data->philos[i].philo_id, data->philos[i].left_fork->fork_id,
			data->philos[i].right_fork->fork_id);
	}
}

void	write_status_debug(t_philo_status status, t_philo *philo)
{
	long	time;

	pthread_mutex_lock(&philo->data->write_mtx);
	time = gettime(1) - philo->data->sim_start_time -1;
	if (status == TAKES_LEFT_FORK)
		printf("%ld %d has taken a fork ------ Fork: %d\n", time,
			philo->philo_id, philo->left_fork->fork_id);
	else if (status == TAKES_RIGHT_FORK)
		printf("%ld %d has taken a fork ------ Fork: %d\n", time,
			philo->philo_id, philo->right_fork->fork_id);
	else if (status == EATING)
		printf("%ld %d is eating ------ Meal Number: %ld\n", time,
			philo->philo_id, philo->meal_count);
	else if (status == SLEEPING)
		printf("%ld %d is sleeping\n", time, philo->philo_id);
	else if (status == THINKING)
		printf("%ld %d is thinking\n", time, philo->philo_id);
	else if (status == DIED)
		printf("%ld %d died\n", time, philo->philo_id);
	pthread_mutex_unlock(&philo->data->write_mtx);
}
//! //////////////////////////////////////////////////////////////////////////
