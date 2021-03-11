/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 21:55:44 by mroux             #+#    #+#             */
/*   Updated: 2021/03/11 02:07:55 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void			*philo_thread(void *arg)
{
	t_args			*p_args;
	struct timeval	tp;
	gettimeofday(&tp, NULL);

	p_args = (t_args *)arg;
	while (1)
	{
		take_fork(p_args);
		eat(p_args);
		do_sleep(p_args);
		think(p_args);
	}
}

int				start_philos(t_philo *philos)
{
	int		i;

	i = 0;
	while (i < 4)
	{
		pthread_create(&(philos[i].thread_id), NULL, &philo_thread, &philos[i].args);
		i++;
	}
	return (0);

}

int				start_checker(t_philo *philos)
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

int				wait_philos(t_philo *philos)
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

int				main(int argc, char *argv[])
{

	int			i;
	t_philo		*philos;
	pthread_mutex_t	*forks;

	i = 0;
	if ((forks = init_forks(argc, argv)) == NULL)
		return (0);
	if ((philos = init_philos(argc, argv, forks)) == NULL)
		return (0);
	start_philos(philos);
	start_checker(philos);
	wait_philos(philos);
	return (0);
}
