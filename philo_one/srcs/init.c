/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 02:06:23 by mroux             #+#    #+#             */
/*   Updated: 2021/03/11 02:09:43 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo			*init_philos(int argc, char *argv[], pthread_mutex_t *forks)
{
	int	i;
	t_philo			*philos;
	struct timeval	tp;

	(void)argc;
	(void)argv;
	i = 0;
	philos = (t_philo *) malloc(sizeof(t_philo) * 4);
	gettimeofday(&tp, NULL);
	while (i < 4)
	{
		philos[i].args.philo_number = i;
		philos[i].args.started_at = tp.tv_sec * 1000 + tp.tv_usec / 1000;
		philos[i].args.time_to_sleep = 1000;
		philos[i].args.time_to_eat = 1000;
		philos[i].args.time_to_die = 6000;
		philos[i].args.forks[0] = &forks[i % 4];
		philos[i].args.forks[1] = &forks[(i + 1) % 4];
		i++;
	}
	return (philos);
}

pthread_mutex_t	*init_forks(int argc, char *argv[])
{
	pthread_mutex_t	*forks;
	int				i;

	(void)argc;
	(void)argv;
	i = 0;
	forks = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t) * 4);
	while (i < 4)
		pthread_mutex_init(&forks[i++], NULL);
	return (forks);
}
