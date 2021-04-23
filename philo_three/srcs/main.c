/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 21:55:44 by mroux             #+#    #+#             */
/*   Updated: 2021/04/23 14:43:34 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		launch(t_global *gl, int i,
				struct timeval *now, t_thread_args *args)
{
	gl->philos[i].started_at = timeval_to_ms(now);
	gl->philos[i].last_lunch = *now;
	args[i].gl = gl;
	args[i].philo = &gl->philos[i];
	if ((gl->philos[i].pid = fork()) < 0)
		return (-1);
	else if (gl->philos[i].pid == 0)
		philo_process(&args[i]);
	usleep(5);
	return (0);
}

int		start_philos(t_global *gl)
{
	int				i;
	struct timeval	now;
	t_thread_args	*args;

	i = 0;
	gettimeofday(&now, NULL);
	if (!(args = (t_thread_args *)
		malloc(gl->number_of_philos * sizeof(t_thread_args))))
		return (-1);
	while (i < gl->number_of_philos)
	{
		if (i % 2 == 0 && launch(gl, i, &now, args) == -1)
			return (-1);
		i++;
	}
	i = 0;
	ft_usleep(1000);
	while (i < gl->number_of_philos)
	{
		if (i % 2 == 1 && launch(gl, i, &now, args) == -1)
			return (-1);
		i++;
	}
	free(args);
	return (0);
}

void	kill_philos(t_global *gl)
{
	int i;

	i = 0;
	while (i < gl->number_of_philos)
		kill(gl->philos[i++].pid, SIGKILL);
	sem_unlink("philo_forks");
	sem_unlink("philo_print");
	free(gl->philos);
}

void	wait_philos(t_global *gl)
{
	int		i;
	int		ret;
	int		*philo_finished;

	philo_finished = init_finished(gl->number_of_philos);
	while (1)
	{
		i = 0;
		while (i < gl->number_of_philos)
		{
			if (waitpid(gl->philos[i].pid, &ret, WNOHANG) != 0)
			{
				if (test_exit(ret, philo_finished, i) == -1)
					return ;
			}
			ft_usleep(50);
			i++;
		}
		if (test_finished(philo_finished, gl->number_of_philos))
			break ;
	}
	free(philo_finished);
	printf("All philos ate %d meals.\n", gl->number_of_meals);
	sem_wait(gl->sem_print);
}

int		main(int argc, char *argv[])
{
	t_global	gl;
	int			i;

	i = 0;
	if (check_vars(argc, argv) == 0)
	{
		printf("Parse error");
		return (0);
	}
	if (init(&gl, argc, argv) == -1)
		return (0);
	start_philos(&gl);
	wait_philos(&gl);
	kill_philos(&gl);
	sem_unlink("philo_forks");
	sem_unlink("philo_print");
	return (0);
}
