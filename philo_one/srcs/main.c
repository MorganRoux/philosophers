/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 21:55:44 by mroux             #+#    #+#             */
/*   Updated: 2021/03/11 00:11:35 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void		*philo_thread(void *arg)
{
	t_args	*p_args;

	p_args = (t_args *)arg;
	printf("hello %d", p_args->number);
	pthread_exit(0);
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

int			launch_philo(t_philo *philos)
{
	int		i;

	i = 0;
	while (i < 4)
	{
		philos[i].args.number = i;
		pthread_create(&(philos[i].th), NULL, &philo_thread, &philos[i].args);
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
	launch_philo(philos);
	i = 0;
	while (i < 4)
	{
		pthread_join(philos[i].th, &philos[i].ret);
		i++;
	}
	return (0);
}
