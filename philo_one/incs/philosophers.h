/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 23:33:24 by mroux             #+#    #+#             */
/*   Updated: 2021/03/24 22:53:42 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>



typedef struct		s_philo
{
	pthread_t		thread_id;
	int				philo_number;
	struct timeval	last_lunch;
	int				meals;
	unsigned long	started_at;
	pthread_mutex_t	*forks[2];
	int				status;
	void			*ret;
}					t_philo;

typedef struct		s_global
{
	t_philo			*philos;
	unsigned long 	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	int				number_of_philos;
	int				number_of_meals;
	pthread_mutex_t	mutex_print;
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
pthread_mutex_t		*init_forks(int argc, char *argv[]);
t_philo				*init_philos(t_global *gl, pthread_mutex_t *forks);

/*
*	Actions
*/

void				take_forks(t_philo *philo, t_global *gl, int fork);
void				eat(t_philo *philo, t_global *gl);
void				do_sleep(t_philo *philo, t_global *gl);
void				think(t_philo *philo, t_global *gl);

/*
*	Utils
*/

void				ft_usleep(unsigned long n);
int					ft_atoul(char const *str);
void				print_death(int philo_number, unsigned long death_time, t_global *gl);
void				print_end(int max_meal, unsigned long end_time, t_global *gl);

/*
*	Prints
*/

void 				ft_putstr_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
/*
*	Time
*/

unsigned long		timeval_to_ms(struct timeval *tp);
unsigned long		get_diff_in_ms(struct timeval *tp1, struct timeval *tp2);
unsigned long		get_relative_time_in_ms(unsigned long ref);

/*
*	Parsing
*/

int					check_vars(int argc, char *argv[]);
int					extract_number_of_philosophers(int argc, char *argv[]);
unsigned long		extract_time_to_die(int argc, char *argv[]);
unsigned long		extract_time_to_eat(int argc, char *argv[]);
unsigned long		extract_time_to_sleep(int argc, char *argv[]);
unsigned long		extract_number_of_meals(int argc, char *argv[]);

#endif
