/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebuber <bebuber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:02:13 by bebuber           #+#    #+#             */
/*   Updated: 2024/07/04 14:59:55 by bebuber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error(char *str)
{
	printf("%s", str);
	exit(1);
}

void	check_args(int argc, char **argv, t_data *data)
{
	int	i;

	i = 1;
	if (argc != 5 && argc != 6)
		error("Error: wrong number of arguments\n");
	while (i < argc)
	{
		if (atoi(argv[i]) < 0)
			error("Error: invalid argument\n");
		i++;
	}
	data->nb_philo = atoi(argv[1]);
	data->nb_forks = data->nb_philo;
	data->tm_to_die = atoi(argv[2]);
	data->tm_to_eat = atoi(argv[3]);
	data->tm_to_sleep = atoi(argv[4]);
	if (argc == 6)
		data->nb_meals = atoi(argv[5]);
	else
		data->nb_meals = -1;
}

void	*m_alloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		error("Error: malloc failed\n");
	return (ptr);
}

void	try_print(pthread_mutex_t print, int id, char *str)
{
	struct timeval	time;
	
	pthread_mutex_lock(&print);
	printf("%d %s\n", id, str);
	pthread_mutex_unlock(&print);
}

void	let_philos_sleap(t_data *data, t_philo *philo, int time)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (philo->id % 2 == 0)
			usleep(time);
		i++;
	}
}

void	let_philo_eat(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->forks[philo->right_fork]);
	try_print(data->print, philo->id, "has taken a fork");
	pthread_mutex_lock(&data->forks[philo->left_fork]);
	try_print(data->print, philo->id, "has taken a fork");
	try_print(data->print, philo->id, "is eating");
	usleep(data->tm_to_eat * 1000);
	
}

void	*routine(void *arg)
{
	t_philo			*philo;
	t_data			*data;
	int				i;

	philo = (t_philo *)arg;
	data = philo->data;
	data->start = gettimeofday();
	pthread_mutex_init(&data->print, NULL);
	let_philos_sleap(data, philo, data->tm_to_eat / 2);
	let_philo_eat(data, philo);

		usleep(data->tm_to_eat * 1000);
		pthread_mutex_unlock(&data->forks[philo->right_fork]);
		pthread_mutex_unlock(&data->forks[philo->left_fork]);
		printf("%d is sleeping\n", philo->id);
		usleep(data->tm_to_sleep * 1000);
		printf("%d is thinking\n", philo->id);

}

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philo;
	int		i;

	i = 0;
	check_args(argc, argv, &data);
	philo = (t_philo *)m_alloc(sizeof(t_philo) * data.nb_philo);
	data.philo = philo;
	data.forks = (pthread_mutex_t *) \
	m_alloc(sizeof(pthread_mutex_t) * data.nb_forks);
	while (i < data.nb_forks)
		pthread_mutex_init(&data.forks[i++], NULL);
	gettimeofday(data.start, NULL);
	i = 0;
	while (i < data.nb_philo)
	{
		philo[i].id = i + 1;
		philo[i].right_fork = i;
		philo[i].left_fork = (i + 1) % data.nb_forks;
		philo[i].data = &data;
		pthread_create(&philo[i].thread, NULL, &routine, &philo[i++]);
	}
	i = 0;
	while (i < data.nb_philo)
		pthread_join(philo[i++].thread, NULL);
	return (0);
}
