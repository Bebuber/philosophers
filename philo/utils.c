/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebuber <bebuber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:28:31 by bebuber           #+#    #+#             */
/*   Updated: 2024/07/05 18:11:49 by bebuber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	try_print(t_data data, int id, char *str, unsigned long start)
{
	unsigned long	time;

	time = start - data.start;
	pthread_mutex_lock(&data.print);
	printf("%lu %d %s\n", time, id, str);
	pthread_mutex_unlock(&data.print);
}

void	ft_sleep(unsigned long start, unsigned long time)
{
	while (get_time() - start < time)
		usleep (time / 10);
}
