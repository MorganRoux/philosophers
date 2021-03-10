/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 21:55:44 by mroux             #+#    #+#             */
/*   Updated: 2021/03/11 00:35:00 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void		*philo_thread(void *arg)
{
	t_args	*p_args;

	p_args = (t_args *)arg;
	usleep(250000 * p_args->philo_number);
	while (1)
	{
		usleep(1000000);
		write(STDOUT_FILENO,"hello\n",6);
	}
}

t_philo		*init(int argc, char *argv[])
{
	t_philo	*philos;
	int		i;

	i = 0;
	(void) argc;
	(void) argv;
	philos = (t_philo *) malloc(sizeof(t_philo) * 4);
	return (philos);
}

int			start_philos(t_philo *philos)
{
	int		i;

	i = 0;
	while (i < 4)
	{
		philos[i].args.philo_number = i;
		pthread_create(&(philos[i].thread_id), NULL, &philo_thread, &philos[i].args);
		i++;
	}
	return (0);

}

int			start_checker(t_philo *philos)
{
	int		i;

	i = 0;
	while (i < 4)
	{
		usleep(1000000);
		pthread_detach(philos[i].thread_id);
		i++;
	}
	return (0);
}

int			wait_philos(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		pthread_join(philos[i].thread_id, &philos[i].ret);
		i++;
	}
	return (0);
}

int			main(int argc, char *argv[])
{

	int			i;
	t_philo		*philos;

	i = 0;
	if ((philos = init(argc, argv)) == NULL)
		return (0);
	start_philos(philos);
	start_checker(philos);
	wait_philos(philos);
	return (0);
}
