/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 21:55:44 by mroux             #+#    #+#             */
/*   Updated: 2021/04/11 14:34:30 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		check_meal(t_global *gl, int *status_meal, int i,
	struct timeval *now)
{
	if (gl->number_of_meals != 0)
	{
		if (gl->philos[i].meals >= gl->number_of_meals)
			(*status_meal)++;
		else
			*status_meal = 0;
		if (*status_meal == gl->number_of_philos)
		{
			print_end(gl->number_of_meals,
				timeval_to_ms(now) - gl->philos[i].started_at, gl);
			return (1);
		}
	}
	return (0);
}

void	set_time(t_global *gl, long long *time, int i,
			struct timeval *now)
{
	gettimeofday(now, NULL);
	*time = timeval_to_ms(now) -
		timeval_to_ms(&gl->philos[i].last_lunch);
}

void	start_checker(t_global *gl)
{
	int				i;
	struct timeval	now;
	long long		time;
	int				status_meal;
	long long		ref;

	ref = gl->time_to_die;
	while (1)
	{
		i = 0;
		while (i < gl->number_of_philos)
		{
			set_time(gl, &time, i, &now);
			if (time >= ref)
			{
				print_death(gl->philos[i].philo_number,
							timeval_to_ms(&now) - gl->philos[i].started_at, gl);
				return ;
			}
			if (check_meal(gl, &status_meal, i, &now))
				return ;
			i++;
		}
	}
}
