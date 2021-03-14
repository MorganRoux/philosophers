/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 00:57:18 by mroux             #+#    #+#             */
/*   Updated: 2021/03/14 19:31:30 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void		log_lunch(t_args *p_args)
{
	gettimeofday(&p_args->last_lunch,  NULL);
}

void		release_forks(t_args *p_args)
{
	pthread_mutex_unlock(p_args->forks[0]);
	pthread_mutex_unlock(p_args->forks[1]);
}

void		take_forks(t_args *p_args)
{
	pthread_mutex_lock(p_args->forks[0]);
	printf("%lu: %d has taken a fork.\n", get_relative_time_in_ms(p_args->started_at), p_args->philo_number);
	pthread_mutex_lock(p_args->forks[1]);
	printf("%lu: %d has taken a fork.\n", get_relative_time_in_ms(p_args->started_at), p_args->philo_number);
	//h(stdout);
}

void		eat(t_args *p_args)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	// printf("%d: last lunch: %lu\n", p_args->philo_number, timeval_to_ms(&now) - timeval_to_ms(&p_args->last_lunch));
	printf("%lu: %d is eating.\n", get_relative_time_in_ms(p_args->started_at), p_args->philo_number);
	//h(stdout);
	log_lunch(p_args);
	ft_usleep(p_args->time_to_eat * 1000);
	p_args->meals++;
	release_forks(p_args);
}

void		do_sleep(t_args *p_args)
{
	printf("%lu: %d is sleeping.\n", get_relative_time_in_ms(p_args->started_at), p_args->philo_number);
	//h(stdout);
	ft_usleep(p_args->time_to_sleep * 1000);
	// printf("%lu: %d is waking up.\n", get_relative_time_in_ms(p_args->started_at), p_args->philo_number);
}

void		think(t_args *p_args)
{
	printf("%lu: %d is thinking.\n", get_relative_time_in_ms(p_args->started_at), p_args->philo_number);
	//h(stdout);
}
