/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebuber <bebuber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 12:07:22 by bebuber           #+#    #+#             */
/*   Updated: 2024/08/06 18:21:28 by bebuber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	if_number(const char str)
{
	if (str >= '0' && str <= '9')
		return (1);
	return (0);
}

void	unlock_forks(t_data *data, t_philo *philo)
{
	pthread_mutex_unlock(&data->forks[philo->right_fork]);
	pthread_mutex_unlock(&data->forks[philo->left_fork]);
}

void	monitor_philos(t_data *data)
{
	int	i;

	i = 0;
	while (1)
	{
		if (i == data->nb_philo)
			i = 0;
		if (check_philos_live(data, &data->philo[i]))
			return ;
		if (check_philos_full(data))
			return ;
		i++;
	}
	return ;
}

void	if_negative(const char *str, int *i, int *ngt)
{
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			(*ngt) = -1;
		(*i)++;
	}
}

int	ft_atoi(const char *str)
{
	int	i;
	int	ngt;
	int	numb;

	i = 0;
	ngt = 1;
	numb = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if_negative(str, &i, &ngt);
	while (str[i])
	{
		if (if_number(str[i]) == 1)
		{
			numb = numb * 10;
			numb = numb + (str[i] - '0');
			i++;
		}
		else
			return (-1);
	}
	return (numb * ngt);
}
