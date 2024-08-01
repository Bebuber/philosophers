/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebuber <bebuber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 15:28:32 by bebuber           #+#    #+#             */
/*   Updated: 2024/08/01 20:18:27 by bebuber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philos_sleep(t_data *data, t_philo *philo)
{
	unsigned long	start_time;

	start_time = get_time();
	if (try_print(data, philo, "is sleeping", start_time))
		return (1);
	while (get_time() - start_time < philo->time_to_sleep)
	{
		if (check_the_death(data))
			return (1);
		ft_sleep(get_time(), 5);
	}
	return (0);
}

int	philos_eat(t_data *data, t_philo *philo)
{
	unsigned long	start_eat;

	pthread_mutex_lock(&data->forks[philo->right_fork]);
	if (try_print(data, philo, "has taken a fork", get_time()))
		return (1);
	pthread_mutex_lock(&data->forks[philo->left_fork]);
	if (try_print(data, philo, "has taken a fork", get_time()))
		return (1);
	start_eat = get_time();
	philo->last_meal = start_eat;
	if (try_print(data, philo, "is eating", start_eat))
		return (1);
	philo->meals++;
	ft_sleep(start_eat, philo->time_to_eat);
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
	while (i < data->nb_philo)
	{
		if ((philo->nb_meals == -1) || (philo[i].nb_meals != -1 \
		&& philo[i].meals != philo[i].nb_meals))
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
		try_print(data, philo, "is thinking", get_time());
		ft_sleep(get_time(), philo->time_to_eat / 2);
	}
	while (1)
	{
		if (check_the_death(data))
			return (NULL);
		if (philos_eat(data, philo))
			return (NULL);
		if (philos_sleep(data, philo))
			return (NULL);
		pthread_mutex_lock(&data->meal_mutex);
		if (philo->nb_meals != -1 && philo->meals == philo->nb_meals)
			return (pthread_mutex_unlock(&data->meal_mutex), NULL);
		pthread_mutex_unlock(&data->meal_mutex);
		if (try_print(data, philo, "is thinking", get_time()))
			return (NULL);
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
		ft_sleep(get_time(), 1);
		if (pthread_create(&data->philo[i].thread, NULL, &day, &data->philo[i]))
			return (1);
	}
	i = 0;
	while (i++)
	{
		if (i == data->nb_philo)
			i = 0;
		if (check_philos_live(data, &data->philo[i]) || check_philos_full(data))
			break ;
	}
	i = -1;
	while (++i < data->nb_philo)
	{
		if (pthread_join(data->philo[i].thread, NULL))
			return (1);
	}
	return (0);
}
