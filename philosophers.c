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

int	free_all(t_resource *rsrc, t_general_info *tgi)
{
	int	i;

	i = -1;
	while (++i < tgi->philo_num && rsrc)
	{
		pthread_mutex_destroy(&(tgi->fork_mutex[i]));
		if (pthread_join(rsrc[i].thread, NULL))
			return (1);
		usleep(10);
	}
	free(tgi->fork_mutex);
	pthread_mutex_destroy(&tgi->glut_mutex);
	pthread_mutex_destroy(&tgi->time_mutex);
	pthread_mutex_destroy(&tgi->dead_mutex);
	pthread_mutex_destroy(&tgi->eat_mutex);
	pthread_mutex_destroy(&tgi->print_mutex);
	free(tgi);
	if (rsrc)
		free(rsrc);
	return (0);
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
	tgi->int_time = lol.tv_usec / 1000 + lol.tv_sec * 1000;
	tgi->fork_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* tgi->philo_num);
	if (!tgi->fork_mutex)
	{
		free(tgi);
		return (NULL);
	}
	return (tgi);
}

t_general_info	*init_check(int argc, char **argv, t_general_info *tgi)
{
	if (argc > 6 || argc < 5)
		return (NULL);
	if (check_arg(argc, argv))
	{
		write(1, "Error\n", 7);
		return (NULL);
	}
	tgi = general_info_init(argc, argv, tgi);
	pthread_mutex_init(&(tgi->time_mutex), NULL);
	pthread_mutex_init(&(tgi->dead_mutex), NULL);
	pthread_mutex_init(&(tgi->glut_mutex), NULL);
	pthread_mutex_init(&(tgi->eat_mutex), NULL);
	pthread_mutex_init(&(tgi->print_mutex), NULL);
	if (!tgi)
		return (NULL);
	return (tgi);
}

int	main(int argc, char **argv)
{
	t_general_info	*tgi;
	t_resource		*rsrc;
	int				i;

	tgi = NULL;
	tgi = init_check(argc, argv, tgi);
	if (!tgi)
		return (1);
	rsrc = (t_resource *)ft_calloc(tgi->philo_num, sizeof(t_resource));
	if (!rsrc)
		return (free_all(NULL, tgi) + 1);
	i = -1;
	while (++i < tgi->philo_num)
	{
		rsrc[i].philo_id = i + 1;
		rsrc[i].tgi = tgi;
		rsrc[i].full = 0;
		pthread_mutex_init(&(tgi->fork_mutex[i]), NULL);
		if (pthread_create(&(rsrc[i].thread), NULL, &daily_task, rsrc + i))
			return (1);
		usleep(10);
	}
	maybe_dead(rsrc, tgi);
	return (free_all(rsrc, tgi));
}
