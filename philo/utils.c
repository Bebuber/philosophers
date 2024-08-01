/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebuber <bebuber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:28:31 by bebuber           #+#    #+#             */
/*   Updated: 2024/08/01 20:13:54 by bebuber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_philos_live(t_data *data, t_philo *philo)
{
	unsigned long	left_time;
	unsigned long	last_meal;

	last_meal = philo->last_meal;
	if (last_meal)
		left_time = get_time() - last_meal;
	else
	{
		pthread_mutex_lock(&data->print);
		left_time = get_time() - data->start;
		pthread_mutex_unlock(&data->print);
	}
	if (left_time >= data->tm_to_die)
	{
		pthread_mutex_lock(&data->death_mutex);
		if (data->death == 0)
		{
			pthread_mutex_lock(&data->print);
			printf("%lu %d died\n", get_time() - data->start, philo->id);
			pthread_mutex_unlock(&data->print);
			data->death = 1;
		}
		return (pthread_mutex_unlock(&data->death_mutex), 1);
	}
	return (0);
}

int	check_the_death(t_data *data)
{
	pthread_mutex_lock(&data->death_mutex);
	if (data->death == 1)
	{
		pthread_mutex_unlock(&data->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->death_mutex);
	return (0);
}

int	try_print(t_data *data, t_philo *philo, char *str, unsigned long start)
{
	unsigned long	time;
	int				id;

	if (check_the_death(data))
		return (1);
	pthread_mutex_lock(&data->print);
	id = philo->id;
	time = start - data->start;
	printf("%lu %d %s\n", time, id, str);
	pthread_mutex_unlock(&data->print);
	return (0);
}

unsigned long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_sleep(unsigned long start, unsigned long time)
{
	while (get_time() - start < time)
		usleep (time / 10);
}
