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

int check_arg(int argc,char **argv)
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
			if(argv[i][j] < '0' || argv[i][j] > '9') // argv[i][j] > 0
				return (1);
		}
	}
	return (0);
}

void *function()
{
	struct timeval lol;
	
	gettimeofday(&lol, NULL);
	printf("[%ld]I am philo number",lol.tv_sec); 
	return (NULL);
}

int	main(int argc,char **argv)
{
	int philo_num;
	int i;
	pthread_t *thread;

	if (argc > 5 || argc < 4)
		return (1);
	if (check_arg(argc, argv))
	{
		write(1, "Error\n", 7);
		return (1);
	}
	philo_num = ft_atoi(argv[1]);
	i = -1;
	thread = (pthread_t *)malloc(sizeof(pthread_t) * philo_num);
	while(++i < philo_num)
	{
		if(pthread_create(thread + i, NULL, &function, NULL))
			return (1);
		usleep(10);
		printf(" %d\n", i);
	}
	i = -1;
	while(++i < philo_num)
	{
		if(pthread_join(*(thread + i), NULL))
			return (1);
		usleep(10);
		printf("philo is number %d is dead\n", i);
	}
	free(thread);
}
