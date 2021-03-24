/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 20:36:45 by mroux             #+#    #+#             */
/*   Updated: 2021/03/24 20:36:57 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void			print_death(int philo_number, unsigned long death_time)
{
	printf("Philo %d died at %lu\n",  philo_number, death_time);
}

void			print_end(int max_meal, unsigned long end_time)
{
	printf("All Philosphers ate %d meals at %lu.\n",  max_meal, end_time);
}
