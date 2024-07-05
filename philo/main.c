/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebuber <bebuber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:02:13 by bebuber           #+#    #+#             */
/*   Updated: 2024/07/05 15:15:24 by bebuber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (argc != 5 && argc != 6)
		error("Error: wrong number of arguments\n", NULL);
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (!if_number(argv[i][j]))
				error("Error: invalid argument\n", NULL);
			j++;
		}
		i++;
	}
	return (0);
}

int	special_case(t_data *data)
{
	unsigned long	time;
	unsigned long	start;

	start = get_time();
	time = get_time() - start;
	printf("%lu 1 has taken a fork\n", time);
	ft_sleep(get_time(), data->tm_to_die);
	time = get_time() - start;
	printf("%lu 1 died\n", time);
	ft_exit(data);
	return (0);
}

void	ft_exit(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_forks)
		pthread_mutex_destroy(&data->forks[i++]);
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->death_mutex);
	if (data->philo)
		free(data->philo);
	if (data->forks)
		free(data->forks);
}

void	error(char *str, t_data *data)
{
	printf("%s", str);
	if (data)
		ft_exit(data);
	// system("leaks philo");
	exit (1);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (check_args(argc, argv))
		return (1);
	if (init_data(&data, argc, argv))
		return (1);
	if (data.nb_philo == 1)
		return (special_case(&data));
	if (init_threads(&data))
		return (1);
	ft_exit(&data);
	// system("leaks philo");
	return (0);
}
