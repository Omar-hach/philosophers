/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   daily_task.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohachami <ohachami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 19:33:07 by ohachami          #+#    #+#             */
/*   Updated: 2023/09/02 19:33:15 by ohachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	already_dead(t_resource *rsrc)
{
	pthread_mutex_lock(&(rsrc->tgi->print_mutex));
	rsrc->tgi->is_dead = 1;
	pthread_mutex_unlock(&(rsrc->tgi->print_mutex));
	printf("%ld  %d died\n", tick_tack(rsrc->tgi->int_time),
		rsrc->philo_id);
	if (rsrc->tgi->philo_num == 1)
		pthread_mutex_unlock(&(rsrc->tgi->fork_mutex[0]));
	return (1);
}

int	maybe_dead(t_resource *rsrc, t_general_info *tgi)
{
	long	time;
	int		i;

	i = -1;
	while (1)
	{
		i = -1;
		while (++i < tgi->philo_num)
		{
			if (tgi->glut == tgi->philo_num)
				return (1);
			pthread_mutex_lock(&(rsrc[i].tgi->time_mutex));
			time = tick_tack(tgi->int_time) - rsrc[i].full;
			pthread_mutex_unlock(&(rsrc[i].tgi->time_mutex));
			if (time >= tgi->time_die)
			{
				return (already_dead(&rsrc[i]));
			}
		}
	}
	return (0);
}

void	food_supply_over(t_resource	*rsrc)
{
	pthread_mutex_lock(&(rsrc->tgi->glut_mutex));
	rsrc->tgi->glut++;
	pthread_mutex_unlock(&(rsrc->tgi->glut_mutex));
	while (rsrc->tgi->glut != rsrc->tgi->philo_num)
		rsrc->full = tick_tack(rsrc->tgi->int_time);
}

void	*daily_task(void *p)
{
	t_resource	*rsrc;

	rsrc = (t_resource *)p;
	if ((rsrc->philo_id % 2))
	{
		thinking(rsrc);
		ft_usleep(rsrc->tgi->time_eat, rsrc->tgi);
	}
	while (rsrc->course_had < rsrc->tgi->course_number
		|| rsrc->tgi->course_number < 0)
	{
		if (!taking_fork(rsrc))
			break ;
		if (!eating(rsrc))
			break ;
		if (!sleeping(rsrc))
			break ;
		if (!thinking(rsrc))
			break ;
	}
	if (rsrc->course_had == rsrc->tgi->course_number)
		food_supply_over(rsrc);
	return (NULL);
}
