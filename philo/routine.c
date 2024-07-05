/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebuber <bebuber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 15:28:32 by bebuber           #+#    #+#             */
/*   Updated: 2024/07/05 12:56:10 by bebuber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_sleap(t_data data, t_philo *philo)
{
	unsigned long	start_time;

	start_time = get_time();
	try_print(data, philo->id, "is sleeping", start_time);
	ft_sleep(start_time, data.tm_to_sleep);
}

void	let_philo_eat(t_data data, t_philo *philo)
{
	unsigned long	start_eat;

	pthread_mutex_lock(&data.forks[philo->right_fork]);
	try_print(data, philo->id, "has taken a fork", get_time());
	pthread_mutex_lock(&data.forks[philo->left_fork]);
	try_print(data, philo->id, "has taken a fork", get_time());
	start_eat = get_time();
	try_print(data, philo->id, "is eating", start_eat);
	philo->meals++;
	ft_sleep(start_eat, data.tm_to_eat);
	pthread_mutex_unlock(&data.forks[philo->right_fork]);
	pthread_mutex_unlock(&data.forks[philo->left_fork]);
}

void	let_philos_sleap(t_data data, int time)
{
	int	i;

	i = 0;
	while (i < data.nb_philo)
	{
		if (data.philo[i].id % 2 == 0)
		{
			// printf("%d\n", data.philo[i].id);
			ft_sleep(get_time(), time);
		}
		i++;
	}
}

void	*routine(void *arg)
{
	t_philo			*philo;
	t_data			*data;

	philo = (t_philo *)arg;
	data = philo->data;
	let_philos_sleap(*data, data->tm_to_eat / 2);
	while (1)
	{
		let_philo_eat(*data, philo);
		get_sleap(*data, philo);
		try_print(*data, philo->id, "is thinking", get_time());
		if (data->nb_meals != -1 && philo->meals == data->nb_meals)
			break ;
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
