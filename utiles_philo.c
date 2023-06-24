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

int	ft_atoi(const char *str)
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