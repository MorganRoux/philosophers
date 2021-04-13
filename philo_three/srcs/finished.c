/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finished.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 21:55:44 by mroux             #+#    #+#             */
/*   Updated: 2021/04/13 22:20:18 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		*init_finished(int n)
{
	int		*ret;
	int		i;

	i = 0;
	ret = malloc(n * sizeof(int));
	while (i < n)
		ret[i++] = 0;
	return (ret);
}

int		test_finished(int *philo_finished, int n)
{
	int		i;
	int		sum;

	i = 0;
	sum = 0;
	while (i < n)
		sum += philo_finished[i++];
	return (sum >= n ? 1 : 0);
}

int		test_exit(int ret, int *philo_finished, int i)
{
	if (WEXITSTATUS(ret) == 2)
	{
		free(philo_finished);
		return (-1);
	}
	if (WEXITSTATUS(ret) == 3)
		philo_finished[i] = 1;
	return (0);
}
