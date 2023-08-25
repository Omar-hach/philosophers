/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohachami <ohachami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:29:24 by ohachami          #+#    #+#             */
/*   Updated: 2023/06/19 18:29:26 by ohachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_arg(int argc, char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (++i < argc)
	{
		j = -1;
		if (argv[i][0] == '+')
			++j;
		while (argv[i][++j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (1);
		}
	}
	return (0);
}

void	*daily_task(void *p)
{
	t_resource	*rsrc;
	int			rythme;

	rsrc = (t_resource *)p;
	rythme = rsrc->tgi->time_eat + rsrc->tgi->time_to_sleep;
	if (!(rsrc->philo_id % 2))
	{
		thinking(rsrc);
		usleep(rsrc->tgi->time_eat * 1000);
	}
	if (rsrc->tgi->philo_num % 2 && rsrc->tgi->philo_num == rsrc->philo_id)
	{
		thinking(rsrc);
		usleep(rsrc->tgi->time_eat * 2000);
	}
	while (rsrc->course_had < rsrc->tgi->course_number || rsrc->tgi->course_number < 0)
	{
		if (!taking_fork(rsrc))
			break ;
		if (!eating(rsrc))
			break ;
		if (!is_dead(rsrc))
			break ;
		if (!sleeping(rsrc))
			break ;
		if (!thinking(rsrc))
			break ;
	}
	//printf("philo is number %d is dead\n", rsrc->philo_id);
	//usleep(10);
	return (NULL);
}

t_general_info	*general_info_init(int argc, char **argv, t_general_info *tgi)
{
	struct timeval	lol;

	tgi = (t_general_info *)ft_calloc(1, sizeof(t_general_info));
	if (!tgi)
		return (NULL);
	tgi->philo_num = ft_atoi(argv[1]);
	tgi->time_die = ft_atoi(argv[2]);
	tgi->time_eat = ft_atoi(argv[3]);
	tgi->time_to_sleep = ft_atoi(argv[4]);
	tgi->course_number = -1;
	if (argc == 6)
		tgi->course_number = ft_atoi(argv[5]);
	gettimeofday(&lol, NULL);
	tgi->int_time = lol.tv_usec / 1000 + lol.tv_sec * (uint64_t)1000;
	tgi->forke = (int *)ft_calloc(1, sizeof(int));
	tgi->fork_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * tgi->philo_num);
	return (tgi);
}

int	main(int argc, char **argv)
{
	t_general_info	*tgi;
	t_resource		*rsrc;
	int				i;

	tgi = NULL;
	i = -1;
	if (argc > 6 || argc < 5)
		return (1);
	if (check_arg(argc, argv))
	{
		write(1, "Error\n", 7);
		return (1);
	}
	tgi = general_info_init(argc, argv, tgi);
	if (!tgi)
		return (1);
	rsrc = (t_resource *)ft_calloc(tgi->philo_num, sizeof(t_resource));
	if (!rsrc)
	{
		free(tgi->forke);
		free(tgi);
		return (1);
	}
	pthread_mutex_init(&(tgi->time_mutex), NULL);
	pthread_mutex_init(&(tgi->dead_mutex), NULL);
	pthread_mutex_init(&(tgi->eat_mutex), NULL);
	pthread_mutex_init(&(tgi->print_mutex), NULL);
	while (++i < tgi->philo_num)
	{
		rsrc[i].philo_id = i + 1;
		rsrc[i].tgi = tgi;
		rsrc[i].full = 0;
		pthread_mutex_init(&(tgi->fork_mutex[i]), NULL);
		if (pthread_create(&(rsrc[i].thread), NULL, &daily_task, rsrc + i))
			return (1);
	}
	i = -1;
	while (++i < tgi->philo_num)
	{
		if (pthread_join(rsrc[i].thread, NULL))
			return (1);
		usleep(10);
	}
	free(tgi->fork_mutex);
	free(tgi->forke);
	free(tgi);
	free(rsrc);
}
