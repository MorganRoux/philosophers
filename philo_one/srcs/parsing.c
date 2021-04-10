/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 18:53:15 by mroux             #+#    #+#             */
/*   Updated: 2021/04/10 20:17:07 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int			extract_number_of_philosophers(int argc, char *argv[])
{
	int		n;

	(void)argc;
	n = ft_atoul(argv[1]);
	return (n);
}

long long	extract_time_to_die(int argc, char *argv[])
{
	int		n;

	(void)argc;
	n = ft_atoul(argv[2]);
	return (n);
}

long long	extract_time_to_eat(int argc, char *argv[])
{
	int		n;

	(void)argc;
	n = ft_atoul(argv[3]);
	return (n);
}

long long	extract_time_to_sleep(int argc, char *argv[])
{
	int		n;

	(void)argc;
	n = ft_atoul(argv[4]);
	return (n);
}

long long	extract_number_of_meals(int argc, char *argv[])
{
	int		n;

	if (argc == 6)
		n = ft_atoul(argv[5]);
	else
		n = 0;
	return (n);
}
