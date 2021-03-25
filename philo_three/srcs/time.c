/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 00:48:07 by mroux             #+#    #+#             */
/*   Updated: 2021/03/24 22:12:05 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned long	timeval_to_ms(struct timeval *tp)
{
	return (tp->tv_sec * 1000 + tp->tv_usec / 1000);
}
unsigned long	get_diff_in_ms(struct timeval *tp1, struct timeval *tp2)
{
	return (timeval_to_ms(tp2) - timeval_to_ms(tp1));
}

unsigned long	get_relative_time_in_ms(unsigned long ref)
{
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	return (timeval_to_ms(&tp) - ref);
}
