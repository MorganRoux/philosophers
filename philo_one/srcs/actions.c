/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 00:57:18 by mroux             #+#    #+#             */
/*   Updated: 2021/03/24 20:06:53 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void		log_lunch(t_philo *philo)
{
	gettimeofday(&philo->last_lunch,  NULL);
}

// void		take_forks(t_args *p_args)
// {
// 	pthread_mutex_lock(p_args->forks[0]);
// 	printf("%lu: %d has taken a fork.\n", get_relative_time_in_ms(p_args->started_at), p_args->philo_number);
// 	pthread_mutex_lock(p_args->forks[1]);
// 	printf("%lu: %d has taken a fork.\n", get_relative_time_in_ms(p_args->started_at), p_args->philo_number);
// }

void		take_forks(t_philo *philo, int fork)
{
	pthread_mutex_lock(philo->forks[fork]);
	printf("%lu: %d has taken a fork.\n", get_relative_time_in_ms(philo->started_at), philo->philo_number);
}

// void		release_forks(t_args *p_args)
// {
// 	pthread_mutex_unlock(p_args->forks[0]);
// 	pthread_mutex_unlock(p_args->forks[1]);
// }

void		release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->forks[0]);
	pthread_mutex_unlock(philo->forks[1]);
}

void		eat(t_philo *philo, unsigned long time_to_eat)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	// printf("%d: last lunch: %lu\n", p_args->philo_number, timeval_to_ms(&now) - timeval_to_ms(&p_args->last_lunch));
	printf("%lu: %d is eating.\n", get_relative_time_in_ms(philo->started_at), philo->philo_number);
	log_lunch(philo);
	ft_usleep(time_to_eat * 1000);
	philo->meals++;
	release_forks(philo);
}

void		do_sleep(t_philo *philo, unsigned long time_to_sleep)
{
	printf("%lu: %d is sleeping.\n", get_relative_time_in_ms(philo->started_at), philo->philo_number);
	ft_usleep(time_to_sleep * 1000);
	// printf("%lu: %d is waking up.\n", get_relative_time_in_ms(p_args->started_at), p_args->philo_number);
}

void		think(t_philo *philo)
{
	printf("%lu: %d is thinking.\n", get_relative_time_in_ms(philo->started_at), philo->philo_number);
}
