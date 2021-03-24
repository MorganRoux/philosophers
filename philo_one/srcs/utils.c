/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 18:44:25 by mroux             #+#    #+#             */
/*   Updated: 2021/03/24 21:23:48 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_usleep(unsigned long n)
{
	struct timeval	start;
	struct timeval	step;

	gettimeofday(&start, NULL);
	while (1)
	{
		usleep(50);
		gettimeofday(&step, NULL);
		if ((size_t)(((size_t)(step.tv_sec - start.tv_sec)) * 1000000 +
			((size_t)(step.tv_usec - start.tv_usec))) > n)
			break ;
	}
}

void			print_death(int philo_number, unsigned long death_time, t_global *gl)
{
	pthread_mutex_lock(&gl->mutex_print);
	printf("Philo %d died at %lu\n",  philo_number, death_time);
}

void			print_end(int max_meal, unsigned long end_time, t_global *gl)
{
	pthread_mutex_lock(&gl->mutex_print);
	printf("All Philosphers ate %d meals at %lu.\n",  max_meal, end_time);
}

