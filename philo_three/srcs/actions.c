/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 00:57:18 by mroux             #+#    #+#             */
/*   Updated: 2021/04/23 14:06:32 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void		take_forks(t_philo *philo, t_global *gl, int fork)
{
	(void)fork;
	sem_wait(philo->forks);
	sem_wait(gl->sem_print);
	if (philo->status)
		printf("%lld: %d has taken a fork.\n",
			get_relative_time_in_ms(philo->started_at), philo->philo_number);
	sem_post(gl->sem_print);
}

void		release_forks(t_philo *philo)
{
	sem_post(philo->forks);
	sem_post(philo->forks);
}

void		eat(t_philo *philo, t_global *gl)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	if (philo->status)
	{
		sem_wait(gl->sem_print);
		printf("%lld: %d is eating.\n",
			get_relative_time_in_ms(philo->started_at), philo->philo_number);
		sem_post(gl->sem_print);
		log_lunch(philo);
		ft_usleep(gl->time_to_eat * 1000);
		philo->meals++;
		if ((gl->number_of_meals > 0) && (philo->meals >= gl->number_of_meals))
		{
			release_forks(philo);
			philo->status = 3;
			return;
		}
	}
	release_forks(philo);
}

void		do_sleep(t_philo *philo, t_global *gl)
{
	sem_wait(gl->sem_print);
	if (philo->status)
	{
		printf("%lld: %d is sleeping.\n",
			get_relative_time_in_ms(philo->started_at), philo->philo_number);
		sem_post(gl->sem_print);
		ft_usleep(gl->time_to_sleep * 1000);
	}
	else
		sem_post(gl->sem_print);
}

void		think(t_philo *philo, t_global *gl)
{
	sem_wait(gl->sem_print);
	if (philo->status)
		printf("%lld: %d is thinking.\n",
			get_relative_time_in_ms(philo->started_at), philo->philo_number);
	sem_post(gl->sem_print);
}
