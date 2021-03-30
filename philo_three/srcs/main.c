/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 21:55:44 by mroux             #+#    #+#             */
/*   Updated: 2021/03/30 23:44:11 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int start_philos(t_global *gl)
{
	int i;
	struct timeval now;
	t_thread_args *args;

	i = 0;
	gettimeofday(&now, NULL);
	if (!(args = (t_thread_args *)malloc(gl->number_of_philos * sizeof(t_thread_args))))
		return (-1);
	while (i < gl->number_of_philos)
	{
		if (i % 2 == 0)
		{
			gl->philos[i].started_at = timeval_to_ms(&now);
			gl->philos[i].last_lunch = now;
			args[i].gl = gl;
			args[i].philo = &gl->philos[i];
			if ((gl->philos[i].pid = fork()) < 0)
				return (-1);
			else if (gl->philos[i].pid == 0)
				philo_process(&args[i]);
			usleep(5);
		}
		i++;
	}
	i = 0;
	while (i < gl->number_of_philos)
	{
		if (i % 2 == 1)
		{
			gl->philos[i].started_at = timeval_to_ms(&now);
			gl->philos[i].last_lunch = now;
			args[i].gl = gl;
			args[i].philo = &gl->philos[i];
			if ((gl->philos[i].pid = fork()) < 0)
				return (-1);
			else if (gl->philos[i].pid == 0)
				philo_process(&args[i]);
			usleep(5);
		}
		i++;
	}
	return (0);
}

void kill_philos(t_global *gl)
{
	int i;

	i = 0;
	while (i < gl->number_of_philos)
	{
		gl->philos[i++].status = 0;
		//pthread_join(gl->philos[i].thread_id, NULL);
	}
	sem_unlink("philo_forks");
	sem_unlink("philo_print");
}

void	wait_philos(t_global*gl)
{
	int		i;
	int		status;
	int		ret;

	status = 1;
	while (status)
	{
		i = 0;
		while (i < gl->number_of_philos)
		{
			if (waitpid(gl->philos[i].pid, &ret, WNOHANG) != 0)
			{
				if (WEXITSTATUS(ret) == 2)
					return ;
			}
			ft_usleep(50);
			i++;
		}
	}

}

int main(int argc, char *argv[])
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
	return (0);
}
