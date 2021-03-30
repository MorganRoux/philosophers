/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 02:06:23 by mroux             #+#    #+#             */
/*   Updated: 2021/03/30 23:46:56 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo			*init_philos(t_global *gl, sem_t *forks)
{
	int				i;
	t_philo			*philos;

	i = 0;
	philos = (t_philo *) malloc(sizeof(t_philo) * gl->number_of_philos);
	while (i < gl->number_of_philos)
	{
		philos[i].philo_number = i + 1;
		philos[i].meals = 0;
		philos[i].forks = forks;
		philos[i].status = 1;
		i++;
	}
	return (philos);
}

sem_t			*init_forks(t_global *gl)
{
	sem_t	*forks;

	if ((forks = sem_open("philo_forks", O_CREAT, S_IRWXU, gl->number_of_philos)) == SEM_FAILED)
		return (NULL);
	return (forks);
}

int				init_gl(t_global *gl, int argc, char *argv[])
{
	if ((gl->sem_print = sem_open("philo_print", O_CREAT, S_IRWXU, 1)) == SEM_FAILED)
		return (-1);
	gl->number_of_philos = extract_number_of_philosophers(argc, argv);
	gl->time_to_sleep = extract_time_to_sleep(argc, argv);
	gl->time_to_eat = extract_time_to_eat(argc, argv);
	gl->time_to_die = extract_time_to_die(argc, argv);
	gl->number_of_meals = extract_number_of_meals(argc, argv);
	return (0);
}

int				init(t_global *gl, int argc, char *argv[])
{
	sem_t	*forks;

	sem_unlink("philo_forks");
	sem_unlink("philo_print");
	if (init_gl(gl, argc, argv) == -1)
		return (-1);
	if ((forks = init_forks(gl)) == NULL)
		return (-1);
	if ((gl->philos = init_philos(gl, forks)) == NULL)
		return (-1);
	return (0);
}
