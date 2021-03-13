/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 02:06:23 by mroux             #+#    #+#             */
/*   Updated: 2021/03/13 19:12:58 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo			*init_philos(int argc, char *argv[], pthread_mutex_t *forks)
{
	int				i;
	t_philo			*philos;


	(void)argc;
	(void)argv;
	i = 0;
	philos = (t_philo *) malloc(sizeof(t_philo) * 4);
	while (i < 4)
	{
		philos[i].args.philo_number = i + 1;
		philos[i].args.time_to_sleep = 200;
		philos[i].args.time_to_eat = 200;
		philos[i].args.time_to_die = 411;
		philos[i].args.forks[0] = &forks[i % 4];
		philos[i].args.forks[1] = &forks[(i + 1) % 4];
		philos[i].args.status = 1;
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
