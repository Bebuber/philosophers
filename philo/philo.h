/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebuber <bebuber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:58:47 by bebuber           #+#    #+#             */
/*   Updated: 2024/07/04 14:51:00 by bebuber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	int				right_fork;
	int				left_fork;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	int				nb_philo;
	int				nb_forks;
	int				tm_to_die;
	int				tm_to_eat;
	int				tm_to_sleep;
	int				nb_meals;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	struct timeval	start;
	struct timeval	end;
}	t_data;

void	check_args(int argc, char **argv, t_data *data);
void	*m_alloc(size_t size);
void	error(char *str);
void	*routine(void *arg);

#endif