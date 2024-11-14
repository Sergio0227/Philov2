/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <sandre-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:37:49 by sandre-a          #+#    #+#             */
/*   Updated: 2024/11/14 17:50:50 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*
^number_of_philo: The number of philosophers and also the number of forks.
*time_to_die: if no meal since the begging of their last meal, they die
^time_to_eat: time it takes for a philosopher to eat / time they hold 2 FORKS
*time_to_sleep: The time a philosopher will spend sleeping
^nbr_max_meals(optional): if not specified simulation stops when a philo dies
!all timestamps are in milliseconds / min 60ms to be valid (usleep 60000)
*/

static bool	valid_input(int argc, char **argv)
{
	int		i;
	long	value;

	if (!(argc >= 5 && argc <= 6) || ft_atol(argv[1]) < 1 || (argv[5]
			&& ft_atol(argv[5]) < 0) || ft_atol(argv[1]) > 500)
		return (printf(RED "ERROR: " YELLOW "Wrong input\n" DEF_COL), false);
	i = 1;
	while (argv[++i])
	{
		if (argc == 6 && argv[i + 1] == 0)
			break ;
		value = ft_atol(argv[i]);
		if (value == LONG_MIN)
			printf(RED "ERROR: " YELLOW "Numeric values only\n" DEF_COL);
		else if (value < 0)
			printf(RED "ERROR: " YELLOW "Time cannot be negative\n" DEF_COL);
		else if (value < 60)
			printf(RED "ERROR: " YELLOW "Time must be > than 60ms\n" DEF_COL);
		if (value < 60)
			return (false);
		if (value > INT_MAX)
			return (printf(RED "ERROR: " YELLOW "INT_MAX is limit\n" DEF_COL),
				false);
	}
	return (true);
}

static void grab_forks(t_philo *philo)
{
	int nbr_of_philo;

	nbr_of_philo = philo->data->nbr_of_philo;
	if (philo->philo_id % 2 == 1)
	{
		philo->left_fork = &philo->data->forks[philo->philo_id - 1];
		if (philo->philo_id != nbr_of_philo)
			philo->right_fork = &philo->data->forks[philo->philo_id];
		else
			philo->right_fork = &philo->data->forks[0];
	}
	else
	{
		philo->right_fork = &philo->data->forks[philo->philo_id - 1];
		if (philo->philo_id != nbr_of_philo)
			philo->left_fork = &philo->data->forks[philo->philo_id];
		else
			philo->left_fork = &philo->data->forks[0];
	}
}

static void	init_philos(t_simulation *data)
{
	t_philo	*philo;
	int		i;

	i = -1;
	data->philos = ft_malloc(&data->gc, sizeof(t_philo) * data->nbr_of_philo);
	while (++i < data->nbr_of_philo)
	{
		philo = &data->philos[i];
		philo->philo_id = i + 1;
		philo->data = data;
		philo->is_philo_full = false;
		philo->last_meal_time = 0;
		philo->meal_count = 0;
		grab_forks(philo);
	}
}

static void	init_data(t_simulation *data, char **argv)
{
	int	i;

	data->nbr_of_philo = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	if (argv[5])
		data->nbr_max_meals = ft_atol(argv[5]);
	else
		data->nbr_max_meals = -1;
	data->gc = NULL;
	data->end_simulation = false;
	data->all_threads_running = false;
	data->nbr_of_running_threads = 0;
	data->sim_start_time = 0;
	i = -1;
	data->forks = ft_malloc(&data->gc, sizeof(t_fork) * data->nbr_of_philo);
	while (++i < data->nbr_of_philo)
	{
		data->forks[i].fork_id = i;
		pthread_mutex_init(&data->forks[i].fork, NULL);
	}
	pthread_mutex_init(&data->write_mtx, NULL);
	pthread_mutex_init(&data->table_mtx, NULL);
	init_philos(data);
}

int	main(int argc, char **argv)
{
	t_simulation	data;

	if (!valid_input(argc, argv))
		return (1);
	print_intro();
	init_data(&data, argv);
	if (data.nbr_max_meals)
		start_simulation(&data);
	collect_garbage(&data.gc);
	return (0);
}
