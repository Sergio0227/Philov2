/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <sandre-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:17:27 by sandre-a          #+#    #+#             */
/*   Updated: 2024/11/16 14:51:18 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*
! 0 -> SECONDS
? 1 -> MILLISECONDS (1 millisecond = 1/1000 of a second)
~ 2 -> MICROSECONDS (1 microsecond = 1/1,000,000 of a second)
*/

long	gettime(int format)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	if (!format)
		return ((long)(tv.tv_sec));
	else if (format == 1)
		return ((long)(tv.tv_sec * 1000 + tv.tv_usec / 1000));
	else if (format == 2)
		return ((long)(tv.tv_sec * 1000000 + tv.tv_usec));
	return (-1);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = gettime(1);
	while ((gettime(1) - start) < milliseconds)
		usleep(500);
	return (0);
}
void	wait_all_threads(t_simulation *data)
{
	while (!get_bool(&data->table_mtx, &data->all_threads_running))
		;
}