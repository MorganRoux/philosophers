/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 23:33:24 by mroux             #+#    #+#             */
/*   Updated: 2021/03/11 00:22:17 by mroux            ###   ########.fr       */
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
	int 			time_to_die;
	int				time_to_eat;
	int				time_to_sleep;

}					t_args;

typedef struct		s_philo
{
	pthread_t		thread_id;
	void			*ret;
	t_args			args;
}					t_philo;

#endif
