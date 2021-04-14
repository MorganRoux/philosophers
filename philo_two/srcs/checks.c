/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 21:55:44 by mroux             #+#    #+#             */
/*   Updated: 2021/04/14 20:08:45 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		check_meal_finished(int *status_meal, int n)
{
	int	i;
	int	sum;

	i = 0;
	sum = 0;
	while (i < n)
		sum += status_meal[i++];
	return ((sum >= n) ? 1 : 0);
}

int		check_meal(t_global *gl, int *status_meal, int i,
	struct timeval *now)
{
	(void)now;
	if (gl->number_of_meals != 0)
	{
		if (gl->philos[i].meals >= gl->number_of_meals)
			status_meal[i] = 1;
		if (check_meal_finished(status_meal, gl->number_of_philos))
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

int		*init_meal(int n)
{
	int	*p;
	int	i;

	i = 0;
	p = (int *)malloc(n * sizeof(int));
	while (i < n)
		p[i++] = 0;
	return (p);
}

void	start_checker(t_global *gl)
{
	int				i;
	struct timeval	now;
	int				*status_meal;
	long long		ref;

	status_meal = init_meal(gl->number_of_meals);
	ref = gl->time_to_die;
	while (1)
	{
		i = 0;
		while (i < gl->number_of_philos)
		{
			if (get_time(gl, i, &now) >= ref && gl->philos->status == 1)
			{
				sem_wait(gl->philos[i].eating);
				print_death(gl->philos[i].philo_number,
							timeval_to_ms(&now) - gl->philos[i].started_at, gl);
				return ;
			}
			if (check_meal(gl, status_meal, i, &now))
				return ;
			i++;
		}
	}
}
