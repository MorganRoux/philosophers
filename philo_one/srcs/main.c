/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 21:55:44 by mroux             #+#    #+#             */
/*   Updated: 2021/03/13 19:17:35 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void			*philo_thread(void *arg)
{
	t_args			*p_args;
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	p_args = (t_args *)arg;
	while (p_args->status)
	{
		if (p_args->status)
			take_forks(p_args);
		if (p_args->status)
			eat(p_args);
		if (p_args->status)
			do_sleep(p_args);
		if (p_args->status)
			think(p_args);
	}
	return (NULL);
}

int				start_philos(t_philo *philos)
{
	int		i;
	struct timeval	now;

	i = 0;
	gettimeofday(&now, NULL);
	while (i < 4)
	{
		philos[i].args.started_at = timeval_to_ms(&now);
		philos[i].args.last_lunch = now;
		pthread_create(&(philos[i].thread_id), NULL, &philo_thread, &philos[i].args);
		pthread_detach(philos[i].thread_id);
		i++;
	}
	return (0);

}

void			print_death(int philo_number, unsigned long death_time)
{
	printf("Philo %d died at %lu\n",  philo_number, death_time);
	//fflush(stdout);
}

void			start_checker(t_philo *philos)
{
	int				i;
	t_args			args;
	struct timeval	now;
	unsigned long 	time;

	while (1)
	{
		i = 0;
		while (i < 4)
		{
			args = philos[i].args;
			gettimeofday(&now, NULL);
			if ((time = (timeval_to_ms(&now) - timeval_to_ms(&args.last_lunch))) >= args.time_to_die)
			{
				// printf("%d->dtime: %lu\n", philos[i].args.philo_number, time);
				print_death(args.philo_number, timeval_to_ms(&now)- args.started_at); // timeval_to_ms(&args.last_lunch) + args.time_to_die - args.started_at);
				return ;
			}
			i++;
		}
	}
}

void			kill_philos(t_philo *philos)
{
	int		i;

	i = 0;
	while (i < 4)
		philos[i++].args.status =  0;
	// printf("end");
	fflush(stdout);
}

int				main(int argc, char *argv[])
{
	int				i;
	t_philo			*philos;
	pthread_mutex_t	*forks;

	i = 0;
	if ((forks = init_forks(argc, argv)) == NULL)
		return (0);
	if ((philos = init_philos(argc, argv, forks)) == NULL)
		return (0);
	start_philos(philos);
	start_checker(philos);
	// printf("hey");
	// fflush(stdout);
	kill_philos(philos);
	return (0);
}
