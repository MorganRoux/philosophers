/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 18:53:15 by mroux             #+#    #+#             */
/*   Updated: 2021/04/10 20:17:33 by mroux            ###   ########.fr       */
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

	if (argc != 5 && argc != 6)
		return (0);
	i = 1;
	while (i < argc)
	{
		if (!is_digit(argv[i]) || ft_atoul(argv[i]) <= 0)
			return (0);
		i++;
	}
	return (1);
}
