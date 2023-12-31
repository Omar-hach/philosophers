/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohachami <ohachami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:24:46 by ohachami          #+#    #+#             */
/*   Updated: 2023/06/19 18:24:49 by ohachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_general_info
{
	int				philo_num;
	int				time_die;
	int				time_eat;
	int				time_to_sleep;
	int				course_number;
	long			int_time;
	int				is_dead;
	int				glut;
	pthread_mutex_t	*fork_mutex;
	pthread_mutex_t	glut_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	time_mutex;
	pthread_mutex_t	eat_mutex;
}t_general_info;

typedef struct s_resource
{
	int				philo_id;
	int				survive;
	int				full;
	int				course_had;
	pthread_t		thread;
	t_general_info	*tgi;
}t_resource;

int		ft_atoi(char *str);
void	*ft_calloc(size_t count, size_t size);
int		taking_fork(t_resource *rsrc);
int		eating(t_resource *rsrc);
int		sleeping(t_resource *rsrc);
int		thinking(t_resource *rsrc);
int		maybe_dead(t_resource *rsrc, t_general_info *tgi);
long	tick_tack(long time);
long	ft_usleep(long time, t_general_info *tgi);
int		free_all(t_resource *rsrc, t_general_info *tgi);
void	*daily_task(void *p);

#endif
