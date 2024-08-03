/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebuber <bebuber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 15:28:32 by bebuber           #+#    #+#             */
/*   Updated: 2024/08/03 18:54:18 by bebuber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philos_sleep(t_data *data, t_philo *philo)
{
	unsigned long	start_time;

	start_time = get_time();
	if (try_print(data, philo, "is sleeping", start_time))
		return (1);
	if (ft_sleep(start_time, philo->time_to_sleep, data))
		return (1);
	return (0);
}

int	philos_eat(t_data *data, t_philo *philo)
{
	unsigned long	start_eat;

	pthread_mutex_lock(&data->forks[philo->right_fork]);
	if (try_print(data, philo, "has taken a fork", get_time()))
		return (pthread_mutex_unlock(&data->forks[philo->right_fork]), 1);
	pthread_mutex_lock(&data->forks[philo->left_fork]);
	if (try_print(data, philo, "has taken a fork", get_time()))
		return (unlock_forks(data, philo), 1);
	start_eat = get_time();
	pthread_mutex_lock(&data->meal_mutex);
	philo->last_meal = start_eat;
	pthread_mutex_unlock(&data->meal_mutex);
	if (try_print(data, philo, "is eating", start_eat))
		return (unlock_forks(data, philo), 1);
	pthread_mutex_lock(&data->meal_mutex);
	philo->meals++;
	pthread_mutex_unlock(&data->meal_mutex);
	if (ft_sleep(start_eat, philo->time_to_eat, data))
		return (unlock_forks(data, philo), 1);
	pthread_mutex_unlock(&data->forks[philo->right_fork]);
	pthread_mutex_unlock(&data->forks[philo->left_fork]);
	return (0);
}

int	check_philos_full(t_data *data)
{
	t_philo	*philo;
	int		i;

	philo = data->philo;
	i = 0;
	pthread_mutex_lock(&data->meal_mutex);
	while (i < philo->nb_philos)
	{
		if ((data->nb_meals == -1) || (data->nb_meals != -1 \
		&& philo[i].meals != data->nb_meals))
		{
			pthread_mutex_unlock(&data->meal_mutex);
			return (0);
		}
		i++;
	}
	pthread_mutex_unlock(&data->meal_mutex);
	return (1);
}

void	*day(void *arg)
{
	t_philo			*philo;
	t_data			*data;

	philo = (t_philo *)arg;
	data = philo->data;
	if (philo->id % 2 == 0)
	{
		if (start_with_thinking(data, philo))
			return (NULL);
	}
	while (1)
	{
		if (check_the_death(data))
			return (NULL);
		if (philos_eat(data, philo) || philos_sleep(data, philo))
			return (NULL);
		pthread_mutex_lock(&data->meal_mutex);
		if (philo->nb_meals != -1 && philo->meals == philo->nb_meals)
			return (pthread_mutex_unlock(&data->meal_mutex), NULL);
		pthread_mutex_unlock(&data->meal_mutex);
		if (try_print(data, philo, "is thinking", get_time()))
			return (NULL);
		usleep(100);
	}
	return (NULL);
}

int	init_threads(t_data *data)
{
	int	i;

	i = -1;
	data->start = get_time();
	while (++i < data->nb_philo)
	{
		usleep(100);
		if (pthread_create(&data->philo[i].thread, NULL, &day, &data->philo[i]))
			return (1);
	}
	monitor_philos(data);
	i = -1;
	while (++i < data->nb_philo)
	{
		if (pthread_join(data->philo[i].thread, NULL))
			return (1);
	}
	return (0);
}
