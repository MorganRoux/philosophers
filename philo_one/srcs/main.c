/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 21:55:44 by mroux             #+#    #+#             */
/*   Updated: 2021/04/23 16:23:46 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philo_thread(void *arg)
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

void	launch(t_global *gl, int i, struct timeval *now, t_thread_args *args)
{
	gl->philos[i].started_at = timeval_to_ms(now);
	gl->philos[i].last_lunch = *now;
	args[i].gl = gl;
	args[i].philo = &gl->philos[i];
	pthread_create(&(gl->philos[i].thread_id), NULL, &philo_thread, &args[i]);
	pthread_detach(gl->philos[i].thread_id);
}

int		start_philos(t_global *gl, t_thread_args *args)
{
	int				i;
	struct timeval	now;

	i = 0;
	gettimeofday(&now, NULL);
	while (i < gl->number_of_philos)
	{
		if (i % 2 == 0)
			launch(gl, i, &now, args);
		i++;
	}
	ft_usleep(5000);
	i = 0;
	while (i < gl->number_of_philos)
	{
		if (i % 2 == 1)
			launch(gl, i, &now, args);
		i++;
	}
	return (0);
}

void	kill_philos(t_global *gl)
{
	int i;

	i = 0;
	while (i < gl->number_of_philos)
	{
		gl->philos[i].status = 0;
		pthread_join(gl->philos[i++].thread_id, NULL);
	}
}

void	clean_gl(t_global *gl)
{
	int	i;

	i = 0;
	while (i < gl->number_of_philos)
	{
		pthread_mutex_destroy(&gl->forks[i]);
		pthread_mutex_destroy(&gl->philos[i]->eating);
		i++;
	}
	pthread_mutex_destroy(&gl->mutex_print);
}

int		main(int argc, char *argv[])
{
	t_global		gl;
	t_thread_args	*args;

	if (check_vars(argc, argv) == 0)
	{
		printf("Parse error");
		return (0);
	}
	if (init(&gl, argc, argv) == -1)
		return (0);
	if (!(args = (t_thread_args *)
			malloc(gl.number_of_philos * sizeof(t_thread_args))))
		return (-1);
	start_philos(&gl, args);
	start_checker(&gl);
	kill_philos(&gl);
	clean_gl(&gl);
	free(args);
	return (0);
}
