/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 21:55:44 by mroux             #+#    #+#             */
/*   Updated: 2021/03/18 14:50:37 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void			*checker(void *arg)
{
	t_checker_args	*checker_args;
	t_args			*args;
	struct timeval	now;
	unsigned long 	time;

	while (1)
	{
		args = checker_args->args;
		gettimeofday(&now, NULL);
		if ((time = (timeval_to_ms(&now) - timeval_to_ms(&args->last_lunch))) >= args->time_to_die)
		{
			print_death(args->philo_number, timeval_to_ms(&now)- args->started_at);
			return ;
		}
		if (checker_args->max_meals != 0 && args->meals >= checker_args->max_meals)
		{
			print_end(checker_args->max_meals, timeval_to_ms(&now) - args->started_at);
			return ;
		}
	}
}

void			*philo_process(void *arg)
{
	t_args			*p_args;
	struct timeval	tp;
	pthread_t		id;

	gettimeofday(&tp, NULL);
	p_args = (t_args *)arg;

	pthread_create(&id, NULL, &philo_, &philos[i].args);
		// pthread_detach(philos[i].thread_id);

	start_checker(philos, extract_number_of_meals(argc, argv),
				extract_number_of_philosophers(argc, argv));


	while (check_status(p_args))
	{
		if (check_status(p_args))
			take_forks(p_args);
		if (check_status(p_args))
			eat(p_args);
		if (check_status(p_args))
			do_sleep(p_args);
		if (check_status(p_args))
			think(p_args);
	}
	return (p_args->meals);
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
		// pthread_create(&(philos[i].thread_id), NULL, &philo_, &philos[i].args);
		// pthread_detach(philos[i].thread_id);
		i++;
	}
	return (0);

}

void			print_death(int philo_number, unsigned long death_time)
{
	printf("Philo %d died at %lu\n",  philo_number, death_time);
}

void			print_end(int max_meal, unsigned long end_time)
{
	printf("All Philosphers ate %d meals at %lu.\n",  max_meal, end_time);
}

void			kill_philos(t_philo *philos, sem_t *forks)
{
	int		i;

	i = 0;
	while (i < 4)
		philos[i++].args.status =  0;
	sem_close(forks);
	sem_unlink("philo_forks");
}

void			wait_philos(t_philo *philos)
{
	(void) philos;
}

int				main(int argc, char *argv[])
{
	int				i;
	t_philo			*philos;
	sem_t			*forks;

	i = 0;
	if (check_vars(argc, argv) == 0)
	{
		printf("Parse error");
		return (0);
	}
	if ((forks = init_forks(argc, argv)) == NULL)
		return (0);
	if ((philos = init_philos(argc, argv, forks)) == NULL)
		return (0);
	start_philos(philos);
	wait_philos(philos);
	kill_philos(philos, forks);
	return (0);
}
