/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoul.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 12:07:41 by mroux             #+#    #+#             */
/*   Updated: 2021/04/10 20:54:00 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int				is_base(char *base, char c)
{
	int i;

	i = 0;
	while (base[i] != '\0')
	{
		if (c == base[i])
			return (1);
		i++;
	}
	return (0);
}

int				ft_atoul(char const *str)
{
	long long	total;
	long long	signe;
	long long	i;
	long long	mult;

	mult = 1;
	i = 0;
	total = 0;
	signe = 1;
	while (*str == '\f' || *str == '\n'
			|| *str == '\t' || *str == '\v'
			|| *str == '\r' || *str == ' ')
		str++;
	if (*str == '+' || *str == '-')
		signe = (*str++ == '-') ? signe * (-1) : signe;
	while (str[i] != '\0' && is_base("0123456789", str[i]))
		i++;
	while (0 < i)
	{
		total += mult * (long long)(str[i - 1] - '0');
		mult = mult * 10;
		i--;
	}
	return (total * signe);
}
