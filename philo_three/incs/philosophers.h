/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 23:33:24 by mroux             #+#    #+#             */
/*   Updated: 2021/04/10 18:07:23 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>


typedef struct		s_philo
{
	pthread_t		thread_id;
	pid_t			pid;
	int				philo_number;
	struct timeval	last_lunch;
	int				meals;
	long long		started_at;
	sem_t			*forks;
	int				status;
	void			*ret;
}					t_philo;

typedef struct		s_global
{
	t_philo			*philos;
	long long 		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				number_of_philos;
	int				number_of_meals;
	sem_t			*sem_print;
}					t_global;

typedef struct 		s_thread_args
{
	t_global		*gl;
	t_philo			*philo;
}					t_thread_args;

/*
*	Init
*/

int					init(t_global *gl, int argc, char *argv[]);
sem_t				*init_forks(t_global *gl);
t_philo				*init_philos(t_global *gl, sem_t *forks);

/*
*	Actions
*/

void				*philo_process(void *arg);
void				take_forks(t_philo *philo, t_global *gl, int fork);
void				eat(t_philo *philo, t_global *gl);
void				do_sleep(t_philo *philo, t_global *gl);
void				think(t_philo *philo, t_global *gl);

/*
*	Utils
*/

void				ft_usleep(long long n);
int					ft_atoul(char const *str);
void				print_death(int philo_number, long long death_time, t_global *gl);
void				print_end(int max_meal, long long end_time, t_global *gl);

/*
*	Prints
*/

void 				ft_putstr_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
/*
*	Time
*/

long long		timeval_to_ms(struct timeval *tp);
long long		get_diff_in_ms(struct timeval *tp1, struct timeval *tp2);
long long		get_relative_time_in_ms(long long ref);

/*
*	Parsing
*/

int					check_vars(int argc, char *argv[]);
int					extract_number_of_philosophers(int argc, char *argv[]);
long long		extract_time_to_die(int argc, char *argv[]);
long long		extract_time_to_eat(int argc, char *argv[]);
long long		extract_time_to_sleep(int argc, char *argv[]);
long long		extract_number_of_meals(int argc, char *argv[]);

#endif
