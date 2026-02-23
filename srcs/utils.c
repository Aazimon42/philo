/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 13:12:28 by edi-maio          #+#    #+#             */
/*   Updated: 2026/01/21 10:36:00 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long	ft_atol(const char *str)
{
	long	nbr;
	int		i;
	int		negative;

	nbr = 0;
	i = 0;
	negative = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			negative = 1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + (str[i] - '0');
		i++;
	}
	if (!negative)
		return (nbr);
	return (-nbr);
}

int	ft_atoi(const char *str)
{
	int	nbr;
	int	i;
	int	negative;

	nbr = 0;
	i = 0;
	negative = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			negative = 1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + (str[i] - '0');
		i++;
	}
	if (!negative)
		return (nbr);
	return (-nbr);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*arr;

	if (size == 0)
	{
		arr = malloc(0);
		if (!arr)
			return (0);
	}
	else if (nmemb * size / size != nmemb)
		return (0);
	else
	{
		arr = malloc(nmemb * size);
		if (arr == 0)
			return (0);
		ft_bzero(arr, size * nmemb);
	}
	return (arr);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*p;

	p = s;
	while (n > 0)
	{
		*p = '\0';
		p++;
		n--;
	}
}
