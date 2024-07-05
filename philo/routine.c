/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebuber <bebuber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 15:28:32 by bebuber           #+#    #+#             */
/*   Updated: 2024/07/05 18:10:43 by bebuber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philos_sleap(t_data data, t_philo *philo)
{
	unsigned long	start_time;

	start_time = get_time();
	try_print(data, philo->id, "is sleeping", start_time);
	ft_sleep(start_time, data.tm_to_sleep);
}

void	philos_eat(t_data data, t_philo *philo)
{
	unsigned long	start_eat;

	pthread_mutex_lock(&data.forks[philo->right_fork]);
	try_print(data, philo->id, "has taken a fork", get_time());
	pthread_mutex_lock(&data.forks[philo->left_fork]);
	try_print(data, philo->id, "has taken a fork", get_time());
	start_eat = get_time();
	try_print(data, philo->id, "is eating", start_eat);
	philo->last_meal = start_eat;
	philo->meals++;
	ft_sleep(start_eat, data.tm_to_eat);
	pthread_mutex_unlock(&data.forks[philo->right_fork]);
	pthread_mutex_unlock(&data.forks[philo->left_fork]);
}

int	do_philos_die(t_data *data, t_philo *philo)
{
	unsigned long	left_time;
	unsigned long	last_meal;

	last_meal = philo->last_meal;
	if (last_meal)
		left_time = get_time() - last_meal;
	else
		left_time = get_time() - data->start;
	if (left_time >= philo->time_to_die)
	{
		pthread_mutex_lock(&data->death_mutex);
		if (data->death == 0)
			try_print(*data, philo->id, "died", get_time());
		data->death = 1;
		pthread_mutex_unlock(&data->death_mutex);
		return (1);
	}
	return (0);
}

// int	check_death(t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	while (i < data->nb_philo)
// 	{
// 		if (data->philo[i].dead == 1)
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

void	*routine(void *arg)
{
	t_philo			*philo;
	t_data			*data;

	philo = (t_philo *)arg;
	data = philo->data;
	if (philo->id % 2 == 0)
		ft_sleep(get_time(), data->tm_to_eat / 2);
	while (data->death == 0)
	{
		if (do_philos_die(data, philo))
			break ;
		philos_eat(*data, philo);
		// if (check_death(data))
		// 	break ;
		philos_sleap(*data, philo);
		// if (check_death(data))
		// 	break ;
		if (data->nb_meals != -1 && philo->meals == data->nb_meals)
			break ;
		if (get_time() - philo->last_meal < philo->time_to_die)
			try_print(*data, philo->id, "is thinking", get_time());
	}
	return (NULL);
}

int	init_threads(t_data *data)
{
	int	i;

	i = 0;
	data->start = get_time();
	while (i < data->nb_philo)
	{
		pthread_create(&data->philo[i].thread, NULL, &routine, &data->philo[i]);
		ft_sleep(get_time(), 1);
		i++;
	}
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(data->philo[i].thread, NULL);
		i++;
	}
	return (0);
}
