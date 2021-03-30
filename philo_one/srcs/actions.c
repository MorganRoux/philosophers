/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 00:57:18 by mroux             #+#    #+#             */
/*   Updated: 2021/03/30 20:11:09 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void		log_lunch(t_philo *philo)
{
	struct timeval save;

	save = philo->last_lunch;
	gettimeofday(&philo->last_lunch,  NULL);
}

void		take_forks(t_philo *philo, t_global *gl, int fork)
{
	pthread_mutex_lock(philo->forks[fork]);
	pthread_mutex_lock(&gl->mutex_print);
	if (philo->status)
		printf("%lld: %d has taken a fork.\n", get_relative_time_in_ms(philo->started_at), philo->philo_number);
	pthread_mutex_unlock(&gl->mutex_print);
}

void		release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->forks[0]);
	pthread_mutex_unlock(philo->forks[1]);
}

void		eat(t_philo *philo, t_global *gl)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	pthread_mutex_lock(&gl->mutex_print);
	if (philo->status)
	{
		printf("%lld: %d is eating.\n", get_relative_time_in_ms(philo->started_at), philo->philo_number);
		pthread_mutex_unlock(&gl->mutex_print);
		log_lunch(philo);
		ft_usleep(gl->time_to_eat * 1000);
		philo->meals++;
	}
	else
		pthread_mutex_unlock(&gl->mutex_print);
	release_forks(philo);
}

void		do_sleep(t_philo *philo, t_global *gl)
{
	pthread_mutex_lock(&gl->mutex_print);
	if (philo->status)
	{
		printf("%lld: %d is sleeping.\n", get_relative_time_in_ms(philo->started_at), philo->philo_number);
		pthread_mutex_unlock(&gl->mutex_print);
		ft_usleep(gl->time_to_sleep * 1000);
	}
	else
		pthread_mutex_unlock(&gl->mutex_print);
}

void		think(t_philo *philo, t_global *gl)
{
	pthread_mutex_lock(&gl->mutex_print);
	if (philo->status)
		printf("%lld: %d is thinking.\n", get_relative_time_in_ms(philo->started_at), philo->philo_number);
	pthread_mutex_unlock(&gl->mutex_print);
}
