/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 00:57:18 by mroux             #+#    #+#             */
/*   Updated: 2021/03/11 01:45:35 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void		take_fork(t_args *p_args)
{
	printf("%lu: %d has taken a fork.\n", get_relative_time_in_ms(p_args->started_at), p_args->philo_number + 1);
	fflush(stdout);
}

void		eat(t_args *p_args)
{
	printf("%lu: %d is eating.\n", get_relative_time_in_ms(p_args->started_at), p_args->philo_number + 1);
	fflush(stdout);
	usleep(p_args->time_to_eat * 1000);

}

void		do_sleep(t_args *p_args)
{
	printf("%lu: %d is sleeping.\n", get_relative_time_in_ms(p_args->started_at), p_args->philo_number + 1);
	fflush(stdout);
	usleep(p_args->time_to_sleep);
}

void		think(t_args *p_args)
{
	printf("%lu: %d is thinking.\n", get_relative_time_in_ms(p_args->started_at), p_args->philo_number + 1);
	fflush(stdout);
}
