/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 18:44:25 by mroux             #+#    #+#             */
/*   Updated: 2021/03/30 23:46:56 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_usleep(long long n)
{
	struct timeval	start;
	struct timeval	step;

	gettimeofday(&start, NULL);
	while (1)
	{
		usleep(50);
		gettimeofday(&step, NULL);
		if ((long long)(((long long)(step.tv_sec - start.tv_sec)) * 1000000 +
			((long long)(step.tv_usec - start.tv_usec))) > n)
			break ;
	}
}

void			print_death(int philo_number, long long death_time, t_global *gl)
{
	sem_wait(gl->sem_print);
	printf("Philo %d died at %lld\n",  philo_number, death_time);
}

void			print_end(int max_meal, long long end_time, t_global *gl)
{
	sem_wait(gl->sem_print);
	printf("All Philosphers ate %d meals at %lld.\n",  max_meal, end_time);
}

