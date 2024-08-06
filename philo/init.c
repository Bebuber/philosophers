/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebuber <bebuber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:25:18 by bebuber           #+#    #+#             */
/*   Updated: 2024/08/06 18:13:00 by bebuber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*m_alloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		error("Error: malloc failed\n", NULL);
	return (ptr);
}

void	init_philo(t_data *data, int i, t_philo *philo)
{
	philo->id = i + 1;
	philo->right_fork = i;
	philo->left_fork = (i + 1) % data->nb_forks;
	philo->nb_meals = data->nb_meals;
	philo->meals = 0;
	philo->data = data;
	philo->last_meal = 0;
	philo->time_to_die = data->tm_to_die;
	philo->time_to_eat = data->tm_to_eat;
	philo->time_to_sleep = data->tm_to_sleep;
	philo->nb_philos = data->nb_philo;
}

int	init_data(t_data *data, int argc, char **argv)
{
	int	i;

	i = 0;
	data->nb_philo = ft_atoi(argv[1]);
	data->nb_forks = data->nb_philo;
	data->tm_to_die = ft_atoi(argv[2]);
	data->tm_to_eat = ft_atoi(argv[3]);
	data->tm_to_sleep = ft_atoi(argv[4]);
	data->death = 0;
	if (argc == 6)
		data->nb_meals = ft_atoi(argv[5]);
	else
		data->nb_meals = -1;
	data->philo = (t_philo *)m_alloc(sizeof(t_philo) * data->nb_philo);
	data->forks = (pthread_mutex_t *) \
	m_alloc(sizeof(pthread_mutex_t) * data->nb_forks);
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->death_mutex, NULL);
	pthread_mutex_init(&data->meal_mutex, NULL);
	while (i < data->nb_forks)
		pthread_mutex_init(&data->forks[i++], NULL);
	i = -1;
	while (++i < data->nb_philo)
		init_philo(data, i, &data->philo[i]);
	return (0);
}

int	start_with_thinking(t_data *data, t_philo *philo)
{
	unsigned long	start_time;

	start_time = get_time();
	if (try_print(data, philo, "is thinking", start_time))
		return (1);
	if (ft_sleep(start_time, philo->time_to_eat / 2, data))
		return (1);
	return (0);
}
