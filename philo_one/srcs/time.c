/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 00:48:07 by mroux             #+#    #+#             */
/*   Updated: 2021/04/23 15:57:53 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	timeval_to_ms(struct timeval *tp)
{
	return ((long long)((long long)tp->tv_sec * (long long)1000 +
		(long long)tp->tv_usec / (long long)1000));
}

long long	get_diff_in_ms(struct timeval *tp1, struct timeval *tp2)
{
	return (timeval_to_ms(tp2) - timeval_to_ms(tp1));
}

long long	get_relative_time_in_ms(long long ref)
{
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	return (timeval_to_ms(&tp) - ref);
}

long long	get_time(t_global *gl, int i,
			struct timeval *now)
{
	long long	time;

	gettimeofday(now, NULL);
	time = timeval_to_ms(now) -
		timeval_to_ms(&gl->philos[i].last_lunch);
	return (time);
}
