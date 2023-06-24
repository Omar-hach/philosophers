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

int	main(int argc,char **argv)
{
	pthread_t thread;

	if (argc > 5 || argc < 4)
		return (1);
	if (check_arg(argc, argv))
	{
		write(1, "Error\n", 7);
		return (1);
	}
	pthread_create(&thread, NULL, function, NULL);
	pthread_join(&thread, NULL);
	
}
