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
	struct timeval	now;

	gettimeofday(&now, NULL);
	//printf("int time==%d lol==%ld=%d\n", time, lol.tv_sec, lol.tv_usec /1000);
	return (now.tv_sec * 1000 + now.tv_usec / 1000 - time);
}

int ft_usleep(int time)
{
	struct timeval	start_time;
	struct timeval	end_time;
    int				actual_time;

    gettimeofday(&start_time, NULL);
    usleep(time);
    gettimeofday(&end_time, NULL);

    actual_time = (end_time.tv_sec - start_time.tv_sec) * 1000 +
                          (end_time.tv_usec - start_time.tv_usec) / 1000;

    if (actual_time < time)
        usleep(time - actual_time);
	return(0);
}