/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebuber <bebuber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:58:47 by bebuber           #+#    #+#             */
/*   Updated: 2024/07/05 16:59:31 by bebuber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	int				right_fork;
	int				left_fork;
	int				dead;
	unsigned long	last_meal;
	unsigned long	time_to_die;
	int				meals;
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
	int				death;
	unsigned long	start;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	print;
}	t_data;

void			error(char *str, t_data *data);
int				if_number(const char str);
void			*routine(void *arg);
void			ft_exit(t_data *data);
void			error(char *str, t_data *data);
unsigned long	get_time(void);
void			try_print(t_data data, int id, char *str, unsigned long start);
void			ft_sleep(unsigned long start, unsigned long time);
int				init_data(t_data *data, int argc, char **argv);
int				init_threads(t_data *data);
#endif