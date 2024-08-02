/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebuber <bebuber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:58:47 by bebuber           #+#    #+#             */
/*   Updated: 2024/08/02 18:28:54 by bebuber          ###   ########.fr       */
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
	int				nb_meals;
	unsigned long	last_meal;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	int				meals;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	int				nb_philo;
	int				nb_forks;
	unsigned long	tm_to_die;
	int				tm_to_eat;
	int				tm_to_sleep;
	int				nb_meals;
	int				full;
	int				death;
	unsigned long	start;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	print;
}	t_data;

void			error(char *str, t_data *data);
int				if_number(const char str);
void			*day(void *arg);
void			ft_clean(t_data *data);
void			error(char *str, t_data *data);
unsigned long	get_time(void);
int				try_print(t_data *data, t_philo *philo, char *str, \
unsigned long start);
void			ft_sleep(unsigned long start, unsigned long time);
int				init_data(t_data *data, int argc, char **argv);
int				init_threads(t_data *data);
int				check_philos_live(t_data *data, t_philo *philo);
int				check_death(t_data *data, t_philo *philo);
int				check_the_death(t_data *data);
void			monitor_philos(t_data *data);
int				check_philos_full(t_data *data);

#endif