/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_get_and_set.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 12:48:05 by sandre-a          #+#    #+#             */
/*   Updated: 2024/11/17 15:42:37 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	set_bool(pthread_mutex_t *mutex, bool *dest, bool value)
{
	pthread_mutex_lock(mutex);
	*dest = value;
	pthread_mutex_unlock(mutex);
}

bool	get_bool(pthread_mutex_t *mutex, bool *value)
{
	bool	return_value;

	pthread_mutex_lock(mutex);
	return_value = *value;
	pthread_mutex_unlock(mutex);
	return (return_value);
}

void	set_long(pthread_mutex_t *mutex, long *dest, long value)
{
	pthread_mutex_lock(mutex);
	*dest = value;
	pthread_mutex_unlock(mutex);
}

void	inc_dec_long(pthread_mutex_t *mutex, long *dest, char choice)
{
	pthread_mutex_lock(mutex);
	if (choice == '+')
		(*dest)++;
	else
		(*dest)--;
	pthread_mutex_unlock(mutex);
}

long	get_long(pthread_mutex_t *mutex, long *value)
{
	long	return_value;

	pthread_mutex_lock(mutex);
	return_value = *value;
	pthread_mutex_unlock(mutex);
	return (return_value);
}
