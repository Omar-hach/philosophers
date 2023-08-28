/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohachami <ohachami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 04:23:37 by ohachami          #+#    #+#             */
/*   Updated: 2023/06/24 04:23:41 by ohachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(char *str)
{
	int	sign;
	int	number;

	number = 0;
	sign = 1;
	while ((*str == ' ' || *str == '\f')
		|| (*str == '\n' || *str == '\r') || (*str == '\v' || *str == '\t'))
		str++;
	if (*str == '+' || *str == '-' )
	{
		sign = ((-1) * (*str == '-') + (*str == '+'));
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		number = number * 10 + *str - '0';
		str++;
	}
	return (number * sign);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;

	p = malloc(size * count);
	if (!p)
		return (NULL);
	memset(p, 0, size * count);
	return (p);
}

int	tick_tack(int time)
{
	struct timeval	lol;

	gettimeofday(&lol, NULL);
	//printf("int time==%d lol==%ld=%d\n", time, lol.tv_sec, lol.tv_usec /1000);
	return (lol.tv_sec * 1000 + lol.tv_usec / 1000 - time);
}