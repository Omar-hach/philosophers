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

int	taking_folk(t_resource *rsrc)
{
	pthread_mutex_lock(&(rsrc->the_mutex));
	rsrc->tgi->forke[rsrc->philo_id - 1] = rsrc->philo_id;
	if (rsrc->philo_id < rsrc->tgi->philo_num)
		rsrc->tgi->forke[rsrc->philo_id] = rsrc->philo_id;
	else
		rsrc->tgi->forke[0] = rsrc->philo_id;
	pthread_mutex_unlock(&(rsrc->the_mutex));
	printf("%d  %d has taken a fork\n", tick_tack(rsrc->tgi->int_time), rsrc->philo_id);
	return (1);
}

int	eating(t_resource *rsrc)
{
	struct timeval	lol;

	gettimeofday(&lol, NULL);
	printf("%d  %d is eating\n", tick_tack(rsrc->tgi->int_time), rsrc->philo_id);
	usleep(rsrc->tgi->time_eat * 1000);
	pthread_mutex_lock(&(rsrc->the_mutex));
	rsrc->full = lol.tv_sec * 1000 + lol.tv_usec / 1000 ;
	pthread_mutex_unlock(&(rsrc->the_mutex));
	return (1);
}

int	sleeping(t_resource *rsrc)
{
	printf("%d  %d is sleeping\n", tick_tack(rsrc->tgi->int_time), rsrc->philo_id);
	usleep(rsrc->tgi->time_to_sleep * 1000);
	return (1);
}

int	thinking(t_resource *rsrc)
{
	printf("%d  %d is thinking\n", tick_tack(rsrc->tgi->int_time), rsrc->philo_id);
	return (1);
}

int	is_dead(t_resource *rsrc)
{
	pthread_mutex_lock(&(rsrc->the_mutex));
	rsrc->survive = tick_tack(rsrc->full);
	pthread_mutex_unlock(&(rsrc->the_mutex));
	//printf("int time==%d lol==%d\n",rsrc->full, rsrc->survive);
	if (rsrc->survive >= rsrc->tgi->time_die)
	{
		printf("%d  %d died\n", tick_tack(rsrc->tgi->int_time), rsrc->philo_id);
		return (1);
	}
	else
		return (0);
}