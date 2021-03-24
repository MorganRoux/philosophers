/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 21:55:44 by mroux             #+#    #+#             */
/*   Updated: 2021/03/24 21:20:08 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void			*philo_thread(void *arg)
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

int				start_philos(t_global *gl)
{
	int		i;
	struct timeval	now;
	t_thread_args	*args;

	i = 0;
	gettimeofday(&now, NULL);
	if (!(args = (t_thread_args*)malloc(gl->number_of_philos * sizeof(t_thread_args))))
		return (-1);
	while (i < (float) gl->number_of_philos / 2.0)
	{
		gl->philos[2 * i].started_at = timeval_to_ms(&now);
		gl->philos[2 * i].last_lunch = now;
		args[2 * i].gl = gl;
		args[2 * i].philo = &gl->philos[2 * i];
		pthread_create(&(gl->philos[2 * i].thread_id), NULL, &philo_thread, &args[2 * i]);
		pthread_detach(gl->philos[2 * i].thread_id);
		i++;
	}
	i = 0;
	while (i < (float) gl->number_of_philos / 2)
	{
		gl->philos[2 * i + 1].started_at = timeval_to_ms(&now);
		gl->philos[2 * i + 1].last_lunch = now;
		args[2 * i + 1].gl = gl;
		args[2 * i + 1].philo = &gl->philos[2 * i + 1];
		pthread_create(&(gl->philos[2 * i + 1].thread_id), NULL, &philo_thread, &args[2 * i + 1]);
		pthread_detach(gl->philos[2 * i + 1].thread_id);
		i++;
	}
	return (0);

}

void			start_checker(t_global *gl)
{
	int				i;
	struct timeval	now;
	unsigned long 	time;
	int				status_meal;

	while (1)
	{
		i = 0;
		while (i < gl->number_of_philos)
		{
			gettimeofday(&now, NULL);
			if ((time = (timeval_to_ms(&now) - timeval_to_ms(&gl->philos[i].last_lunch))) >= gl->time_to_die)
			{
				print_death(gl->philos[i].philo_number, timeval_to_ms(&now)- gl->philos[i].started_at, gl);
				return ;
			}
			if (gl->number_of_meals != 0)
			{
				if (gl->philos[i].meals >= gl->number_of_meals)
					status_meal++;
				else
					status_meal = 0;
				if (status_meal == gl->number_of_philos)
				{
					print_end(gl->number_of_meals, timeval_to_ms(&now)- gl->philos[i].started_at, gl);
					return ;
				}
			}
			i++;
		}
	}
}

void			kill_philos(t_global *gl)
{
	int		i;

	i = 0;
	while (i < gl->number_of_philos)
		gl->philos[i++].status =  0;
}

int				main(int argc, char *argv[])
{
	int				i;
	t_global		gl;

	i = 0;
	if (check_vars(argc, argv) == 0)
	{
		printf("Parse error");
		return (0);
	}
	if (init(&gl, argc, argv) == -1)
		return (0);
	start_philos(&gl);
	start_checker(&gl);
	kill_philos(&gl);
	pthread_mutex_unlock(&gl.mutex_print);
	return (0);
}
