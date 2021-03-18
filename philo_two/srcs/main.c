/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 21:55:44 by mroux             #+#    #+#             */
/*   Updated: 2021/03/18 10:14:15 by mroux            ###   ########.fr       */
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
}

void			print_end(int max_meal, unsigned long end_time)
{
	printf("All Philosphers ate %d meals at %lu.\n",  max_meal, end_time);
}

void			start_checker(t_philo *philos, int max_meals, int number_of_philosophers)
{
	int				i;
	t_args			args;
	struct timeval	now;
	unsigned long 	time;
	int				status_meal;

	while (1)
	{
		i = 0;
		while (i < number_of_philosophers)
		{
			args = philos[i].args;
			gettimeofday(&now, NULL);
			if ((time = (timeval_to_ms(&now) - timeval_to_ms(&args.last_lunch))) >= args.time_to_die)
			{
				print_death(args.philo_number, timeval_to_ms(&now)- args.started_at);
				return ;
			}
			if (max_meals != 0)
			{
				if (args.meals >= max_meals)
					status_meal++;
				else
					status_meal = 0;
				if (status_meal == number_of_philosophers)
				{
					print_end(max_meals, timeval_to_ms(&now)- args.started_at);
					return ;
				}
			}
			i++;
		}
	}
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
	start_checker(philos, extract_number_of_meals(argc, argv),
				extract_number_of_philosophers(argc, argv));
	kill_philos(philos, forks);
	return (0);
}
