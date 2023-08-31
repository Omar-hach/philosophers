/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohachami <ohachami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 22:42:28 by ohachami          #+#    #+#             */
/*   Updated: 2023/08/20 22:42:43 by ohachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	taking_fork(t_resource *rsrc)
{
	if (rsrc->philo_id < rsrc->tgi->philo_num)
	{
		pthread_mutex_lock(&(rsrc->tgi->fork_mutex[rsrc->philo_id]));
		pthread_mutex_lock(&(rsrc->tgi->print_mutex));
		if (rsrc->tgi->is_dead)
		{
			pthread_mutex_unlock(&(rsrc->tgi->fork_mutex[rsrc->philo_id]));
			pthread_mutex_unlock(&(rsrc->tgi->print_mutex));
			return (0);
		}
		printf("%d  %d has taken a fork\n", tick_tack(rsrc->tgi->int_time), rsrc->philo_id);
		pthread_mutex_unlock(&(rsrc->tgi->print_mutex));
	}
	else
	{
		pthread_mutex_lock(&(rsrc->tgi->fork_mutex[0]));

		pthread_mutex_lock(&(rsrc->tgi->print_mutex));
		if (rsrc->tgi->is_dead)
		{
			pthread_mutex_unlock(&(rsrc->tgi->fork_mutex[0]));
			pthread_mutex_unlock(&(rsrc->tgi->print_mutex));
			return (0);
		}
		printf("%d  %d has taken a fork\n", tick_tack(rsrc->tgi->int_time), rsrc->philo_id);
		pthread_mutex_unlock(&(rsrc->tgi->print_mutex));
	}
	pthread_mutex_lock(&(rsrc->tgi->fork_mutex[rsrc->philo_id - 1]));
	pthread_mutex_lock(&(rsrc->tgi->print_mutex));
	if (rsrc->tgi->is_dead)
	{
		pthread_mutex_unlock(&(rsrc->tgi->fork_mutex[rsrc->philo_id - 1]));
		if (rsrc->philo_id < rsrc->tgi->philo_num)
			pthread_mutex_unlock(&(rsrc->tgi->fork_mutex[rsrc->philo_id]));
		else
			pthread_mutex_unlock(&(rsrc->tgi->fork_mutex[0]));
		pthread_mutex_unlock(&(rsrc->tgi->print_mutex));
		return (0);
	}
	printf("%d  %d has taken a fork\n", tick_tack(rsrc->tgi->int_time), rsrc->philo_id);
	printf("%d  %d is eating\n", tick_tack(rsrc->tgi->int_time), rsrc->philo_id);
	pthread_mutex_unlock(&(rsrc->tgi->print_mutex));

	return (1);
}

int	eating(t_resource *rsrc)
{
	pthread_mutex_lock(&(rsrc->tgi->eat_mutex));
	if(rsrc->tgi->course_number > -1)
		rsrc->course_had++;
	pthread_mutex_unlock(&(rsrc->tgi->eat_mutex));

	ft_usleep(rsrc->tgi->time_eat * 1000);

	pthread_mutex_lock(&(rsrc->tgi->time_mutex));
	rsrc->full = tick_tack(rsrc->tgi->int_time);
	pthread_mutex_unlock(&(rsrc->tgi->time_mutex));

	pthread_mutex_unlock(&(rsrc->tgi->fork_mutex[rsrc->philo_id - 1]));
	if (rsrc->philo_id < rsrc->tgi->philo_num)
		pthread_mutex_unlock(&(rsrc->tgi->fork_mutex[rsrc->philo_id]));
	else
		pthread_mutex_unlock(&(rsrc->tgi->fork_mutex[0]));
	return (1);
}

int	sleeping(t_resource *rsrc)
{
	pthread_mutex_lock(&(rsrc->tgi->print_mutex));
	if (rsrc->tgi->is_dead)
	{
		pthread_mutex_unlock(&(rsrc->tgi->print_mutex));
		return (0);
	}
	printf("%d  %d is sleeping\n", tick_tack(rsrc->tgi->int_time), rsrc->philo_id);
	pthread_mutex_unlock(&(rsrc->tgi->print_mutex));
	ft_usleep(rsrc->tgi->time_to_sleep * 1000);
	return (1);
}

int	thinking(t_resource *rsrc)
{
	pthread_mutex_lock(&(rsrc->tgi->print_mutex));
	if (rsrc->tgi->is_dead)
	{
		pthread_mutex_unlock(&(rsrc->tgi->print_mutex));
		return (0);
	}
	printf("%d  %d is thinking\n", tick_tack(rsrc->tgi->int_time), rsrc->philo_id);
	pthread_mutex_unlock(&(rsrc->tgi->print_mutex));
	//printf("[%d]cource = %d =%d\n",rsrc->tgi->philo_num, rsrc->course_had < rsrc->tgi->course_number, rsrc->tgi->course_number < 0);
	return (1);
}

int	is_dead(t_resource *rsrc, t_general_info *tgi)
{
	int	time;
	int i;

	i = -1;
	while(1)
	{
		i = -1;
		while(++i < tgi->philo_num)
		{
			while (tgi->glut == tgi->philo_num)
				return (1);
			pthread_mutex_lock(&(rsrc[i].tgi->time_mutex));
			time = tick_tack(tgi->int_time) - rsrc[i].full;
			pthread_mutex_unlock(&(rsrc[i].tgi->time_mutex));
			if (time >= tgi->time_die)
			{
				//printf("survive=%d full=%d int_time=%d\n",rsrc[i].survive, rsrc[i].full, rsrc[i].tgi->int_time);
				pthread_mutex_lock(&(rsrc[i].tgi->print_mutex));
				rsrc->tgi->is_dead = 1;
				pthread_mutex_unlock(&(rsrc[i].tgi->print_mutex));
				printf("%d  %d died\n", tick_tack(rsrc[i].tgi->int_time), rsrc[i].philo_id);
				if (rsrc[i].tgi->philo_num == 1)
					pthread_mutex_unlock(&(rsrc[i].tgi->fork_mutex[0]));
				return (1);
			}
		}
	}
	return (0);
}
