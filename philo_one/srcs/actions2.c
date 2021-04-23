/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 00:57:18 by mroux             #+#    #+#             */
/*   Updated: 2021/04/23 16:26:54 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void		log_lunch(t_philo *philo)
{
	struct timeval save;

	save = philo->last_lunch;
	gettimeofday(&philo->last_lunch, NULL);
}

void		*philo_thread(void *arg)
{
	t_thread_args	*p_args;
	struct timeval	tp;

	p_args = (t_thread_args *)arg;
	gettimeofday(&tp, NULL);
	while (p_args->philo->status)
	{
		if (p_args->philo->status)
			take_forks(p_args->philo, p_args->gl, 0);
		if (p_args->philo->status)
			take_forks(p_args->philo, p_args->gl, 1);
		if (p_args->philo->status)
			eat(p_args->philo, p_args->gl);
		if (p_args->philo->status)
			do_sleep(p_args->philo, p_args->gl);
		if (p_args->philo->status)
			think(p_args->philo, p_args->gl);
	}
	return (NULL);
}
