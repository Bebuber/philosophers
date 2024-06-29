/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebuber <bebuber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:02:13 by bebuber           #+#    #+#             */
/*   Updated: 2024/06/28 19:33:45 by bebuber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	check_args(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
	{
		write(2, "Error: wrong number of arguments\n", 33);
		exit(1);
	}
	while (i < argc)
	{
		if (atoi(argv[i]) < 0)
		{
			printf("Error: wrong argument\n");
			exit(1);
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	check_args(argc, argv);
	return (0);
}
