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

int	first_fork(t_resource *rsrc)
{
	if (rsrc->philo_id < rsrc->tgi->philo_num)
		pthread_mutex_lock(&(rsrc->tgi->fork_mutex[rsrc->philo_id]));
	else
		pthread_mutex_lock(&(rsrc->tgi->fork_mutex[0]));
	pthread_mutex_lock(&(rsrc->tgi->print_mutex));
	if (rsrc->tgi->is_dead)
	{
		if (rsrc->philo_id < rsrc->tgi->philo_num)
			pthread_mutex_unlock(&(rsrc->tgi->fork_mutex[rsrc->philo_id]));
		else
			pthread_mutex_unlock(&(rsrc->tgi->fork_mutex[0]));
		pthread_mutex_unlock(&(rsrc->tgi->print_mutex));
		return (0);
	}
	printf("%ld  %d has taken a fork\n", tick_tack(rsrc->tgi->int_time),
		rsrc->philo_id);
	pthread_mutex_unlock(&(rsrc->tgi->print_mutex));
	return (1);
}

int	taking_fork(t_resource *rsrc)
{
	if (!first_fork(rsrc))
		return (0);
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
	printf("%ld  %d has taken a fork\n", tick_tack(rsrc->tgi->int_time),
		rsrc->philo_id);
	printf("%ld  %d is eating\n", tick_tack(rsrc->tgi->int_time),
		rsrc->philo_id);
	pthread_mutex_unlock(&(rsrc->tgi->print_mutex));
	return (1);
}

int	eating(t_resource *rsrc)
{
	pthread_mutex_lock(&(rsrc->tgi->eat_mutex));
	if (rsrc->tgi->course_number > -1)
		rsrc->course_had++;
	pthread_mutex_unlock(&(rsrc->tgi->eat_mutex));
	ft_usleep(rsrc->tgi->time_eat, rsrc->tgi);
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
	printf("%ld  %d is sleeping\n", tick_tack(rsrc->tgi->int_time),
		rsrc->philo_id);
	pthread_mutex_unlock(&(rsrc->tgi->print_mutex));
	ft_usleep(rsrc->tgi->time_to_sleep, rsrc->tgi);
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
	printf("%ld  %d is thinking\n", tick_tack(rsrc->tgi->int_time),
		rsrc->philo_id);
	pthread_mutex_unlock(&(rsrc->tgi->print_mutex));
	return (1);
}
