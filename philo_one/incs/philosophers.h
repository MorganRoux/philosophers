/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 23:33:24 by mroux             #+#    #+#             */
/*   Updated: 2021/03/14 18:46:47 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct		s_args
{
	int				philo_number;
	struct timeval	last_lunch;
	unsigned long 	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	unsigned long	started_at;
	pthread_mutex_t	*forks[2];
	int				status;
}					t_args;

typedef struct		s_philo
{
	pthread_t		thread_id;
	void			*ret;
	t_args			args;
}					t_philo;

unsigned long		timeval_to_ms(struct timeval *tp);
unsigned long		get_diff_in_ms(struct timeval *tp1, struct timeval *tp2);
unsigned long		get_relative_time_in_ms(unsigned long ref);

pthread_mutex_t		*init_forks(int argc, char *argv[]);
t_philo				*init_philos(int argc, char *argv[], pthread_mutex_t *forks);

void				take_forks(t_args *p_args);
void				eat(t_args *p_args);
void				do_sleep(t_args *p_args);
void				think(t_args *p_args);

void				ft_usleep(unsigned long n);
#endif
