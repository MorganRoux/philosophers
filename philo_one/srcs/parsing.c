/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 18:53:15 by mroux             #+#    #+#             */
/*   Updated: 2021/03/14 19:29:38 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int				is_digit(char *str)
{
	if (str == NULL || *str == 0)
		return (0);
	while (*str != 0)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

int				check_vars(int argc, char *argv[])
{
	int		i;

	i = 1;
	if (argc  != 5 && argc != 6)
		return (0);

	while (i < argc)
	{
		printf("%s", argv[i]);
		if (!is_digit(argv[i]))
			return (0);
		i++;
	}
	return (1);
}

int				extract_number_of_philosophers(int argc, char *argv[])
{
	int		n;

	(void)argc;
	n = ft_atoul(argv[1]);
	return (n);
}

unsigned long	extract_time_to_die(int argc, char *argv[])
{
	int		n;

	(void)argc;
	n = ft_atoul(argv[2]);
	return (n);

}

unsigned long	extract_time_to_eat(int argc, char *argv[])
{
	int		n;

	(void)argc;
	n = ft_atoul(argv[3]);
	return (n);

}

unsigned long	extract_time_to_sleep(int argc, char *argv[])
{
	int		n;

	(void)argc;
	n = ft_atoul(argv[4]);
	return (n);
}

unsigned long	extract_number_of_meals(int argc, char *argv[])
{
	int		n;

	(void)argc;
	n = ft_atoul(argv[5]);
	return (n);
}
