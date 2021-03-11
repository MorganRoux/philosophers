/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 21:55:44 by mroux             #+#    #+#             */
/*   Updated: 2021/03/11 01:58:41 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void			*philo_thread(void *arg)
{
	t_args			*p_args;
	struct timeval	tp;
	gettimeofday(&tp, NULL);

	p_args = (t_args *)arg;
	// printf("--%ld %d %ld %d\n", tp.tv_sec, tp.tv_usec, p_args->started_at->tv_sec, p_args->started_at->tv_usec);
	while (1)
	{
		take_fork(p_args);
		eat(p_args);
		// do_sleep(p_args);
		// think(p_args);
	}
}

int				start_philos(t_philo *philos)
{
	int		i;

	i = 0;
	while (i < 4)
	{
		// printf("??? %ld %d\n", philos[i].args.started_at->tv_sec, philos[i].args.started_at->tv_usec);
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
		philos[i].args.forks[0] = &forks[(i * 2) % 4];
		philos[i].args.forks[0] = &forks[(i * 2 + 1) % 4];
		i++;
	}
	// printf("=====%ld %d %ld %d\n", tp.tv_sec, tp.tv_usec, philos[1].args.started_at->tv_sec, philos[1].args.started_at->tv_usec);
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
