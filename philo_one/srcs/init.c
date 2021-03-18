/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 02:06:23 by mroux             #+#    #+#             */
/*   Updated: 2021/03/18 09:38:37 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo			*init_philos(int argc, char *argv[], pthread_mutex_t *forks)
{
	int				i;
	t_philo			*philos;
	int				number_of_philos;

	number_of_philos = extract_number_of_philosophers(argc, argv);
	i = 0;
	philos = (t_philo *) malloc(sizeof(t_philo) * number_of_philos);
	while (i < number_of_philos)
	{
		philos[i].args.philo_number = i + 1;
		philos[i].args.meals = 0;
		philos[i].args.time_to_sleep = extract_time_to_sleep(argc, argv);
		philos[i].args.time_to_eat = extract_time_to_eat(argc, argv);
		philos[i].args.time_to_die = extract_time_to_die(argc, argv);
		philos[i].args.forks[0] = &forks[i % number_of_philos];
		philos[i].args.forks[1] = &forks[(i + 1) % number_of_philos];
		philos[i].args.status = 1;
		i++;
	}
	return (philos);
}

// pthread_mutex_t	*init_forks(int argc, char *argv[])
// {
// 	pthread_mutex_t	*forks;
// 	int				i;

// 	(void)argc;
// 	(void)argv;
// 	i = 0;
// 	forks = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t) * 4);
// 	while (i < 4)
// 		pthread_mutex_init(&forks[i++], NULL);
// 	return (forks);
// }

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
