/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 22:51:49 by mroux             #+#    #+#             */
/*   Updated: 2021/04/11 14:36:24 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

char	*ft_strdup(char *src)
{
	char	*dest;
	int		size;
	int		i;

	i = 0;
	size = 1;
	if (src == 0)
		return (0);
	while (src[size - 1] != '\0')
		size++;
	if ((dest = malloc(size)) == 0)
		return (0);
	while (i < size)
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}

void	ft_putstr_fd(char *s, int fd)
{
	while (*s != 0)
		write(fd, s++, 1);
}

void	putnbr(unsigned int n, int fd)
{
	char	*base;

	base = ft_strdup("0123456789");
	if (n == 0)
		return ;
	putnbr(n / 10, fd);
	write(fd, &base[n % 10], 1);
	free(base);
}

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	nbr;

	if (n == 0)
	{
		write(fd, "0", 1);
		return ;
	}
	nbr = (unsigned int)(n < 0) ? -n : n;
	if (n < 0)
		write(fd, "-", 1);
	putnbr(nbr, fd);
	return ;
}
