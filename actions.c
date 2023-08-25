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
			return (0);
		printf("%d  %d has taken a fork\n", tick_tack(rsrc->tgi->int_time), rsrc->philo_id);
		pthread_mutex_unlock(&(rsrc->tgi->print_mutex));
		/*if(rsrc->tgi->forke[rsrc->philo_id]
			|| rsrc->tgi->forke[rsrc->philo_id - 1])
		{
			pthread_mutex_unlock(&(rsrc->tgi->fork_mutex[rsrc->philo_id - 1]));
			return (1);
		}*/
		// rsrc->tgi->forke[rsrc->philo_id] = rsrc->philo_id;
	}
	else
	{
		pthread_mutex_lock(&(rsrc->tgi->fork_mutex[0]));
		pthread_mutex_lock(&(rsrc->tgi->print_mutex));
		if (rsrc->tgi->is_dead)
			return (0);
		printf("%d  %d has taken a fork\n", tick_tack(rsrc->tgi->int_time), rsrc->philo_id);
		pthread_mutex_unlock(&(rsrc->tgi->print_mutex));
		// if(rsrc->tgi->forke[0] || rsrc->tgi->forke[rsrc->philo_id - 1])
		// {
		// 	pthread_mutex_unlock(&(rsrc->tgi->fork_mutex[0]));
		// 	return (1);
		// }
		// rsrc->tgi->forke[0] = rsrc->philo_id;
	}
	pthread_mutex_lock(&(rsrc->tgi->fork_mutex[rsrc->philo_id - 1]));
	pthread_mutex_lock(&(rsrc->tgi->print_mutex));
	if (rsrc->tgi->is_dead)
		return (0);
	printf("%d  %d has taken a fork\n", tick_tack(rsrc->tgi->int_time), rsrc->philo_id);
	pthread_mutex_unlock(&(rsrc->tgi->print_mutex));
	return (1);
}

int	eating(t_resource *rsrc)
{
	struct timeval	lol;

	gettimeofday(&lol, NULL);
	pthread_mutex_lock(&(rsrc->tgi->print_mutex));
	if (rsrc->tgi->is_dead)
		return (0);
	printf("%d  %d is eating\n", tick_tack(rsrc->tgi->int_time), rsrc->philo_id);
	pthread_mutex_unlock(&(rsrc->tgi->print_mutex));
	pthread_mutex_lock(&(rsrc->tgi->eat_mutex));
	if(rsrc->tgi->course_number > 0)
		rsrc->course_had++;
	pthread_mutex_unlock(&(rsrc->tgi->eat_mutex));
	usleep(rsrc->tgi->time_eat * 1000);
	pthread_mutex_unlock(&(rsrc->tgi->fork_mutex[rsrc->philo_id - 1]));
	if (rsrc->philo_id < rsrc->tgi->philo_num)
		pthread_mutex_unlock(&(rsrc->tgi->fork_mutex[rsrc->philo_id]));
	else
		pthread_mutex_unlock(&(rsrc->tgi->fork_mutex[0]));
	pthread_mutex_lock(&(rsrc->tgi->time_mutex));
	rsrc->full = lol.tv_sec * 1000 + lol.tv_usec / 1000 ;
	pthread_mutex_unlock(&(rsrc->tgi->time_mutex));
	return (1);
}

int	sleeping(t_resource *rsrc)
{
	pthread_mutex_lock(&(rsrc->tgi->print_mutex));
	if (rsrc->tgi->is_dead)
		return (0);
	printf("%d  %d is sleeping\n", tick_tack(rsrc->tgi->int_time), rsrc->philo_id);
	pthread_mutex_unlock(&(rsrc->tgi->print_mutex));
	usleep(rsrc->tgi->time_to_sleep * 1000);
	return (1);
}

int	thinking(t_resource *rsrc)
{
	pthread_mutex_lock(&(rsrc->tgi->print_mutex));
	if (rsrc->tgi->is_dead)
		return (0);
	printf("%d  %d is thinking\n", tick_tack(rsrc->tgi->int_time), rsrc->philo_id);
	pthread_mutex_unlock(&(rsrc->tgi->print_mutex));
	return (1);
}

int	is_dead(t_resource *rsrc)
{
	pthread_mutex_lock(&(rsrc->tgi->dead_mutex));
	rsrc->survive = tick_tack(rsrc->full);
	//printf("int time==%d lol==%d\n",rsrc->full, rsrc->survive);
	if (rsrc->survive >= rsrc->tgi->time_die)
	{
		rsrc->tgi->is_dead = 1;
		printf("%d  %d died\n", tick_tack(rsrc->tgi->int_time), rsrc->philo_id);
		pthread_mutex_unlock(&(rsrc->tgi->dead_mutex));
		return (0);
	}
	pthread_mutex_unlock(&(rsrc->tgi->dead_mutex));
	return (1);
}