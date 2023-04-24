/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_struct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschelti <sschelti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 14:48:59 by sschelti          #+#    #+#             */
/*   Updated: 2023/04/24 14:21:21 by sschelti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	set_rules(t_rules *rules, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		printf("incorrect amount of arguments\n");
		return (1);
	}
	if (check_values(argc, argv) == 1)
	{
		printf("values can only be positive decimals\n");
		return (1);
	}
	rules->number_of_philosophers = ft_uatoi(argv[1]);
	if (rules->number_of_philosophers > 20
		|| rules->number_of_philosophers < 1)
	{
		printf("Number of philosophers must be between 1 and 20\n");
		return (1);
	}
	rules->time_to_die = ft_uatoi(argv[2]);
	rules->time_to_eat = ft_uatoi(argv[3]);
	rules->time_to_sleep = ft_uatoi(argv[4]);
	if (argv[5])
		rules->number_of_times_each_philosopher_must_eat = ft_uatoi(argv[5]);
	else
		rules->number_of_times_each_philosopher_must_eat = 0;
	return (0);
}

int	check_values(int argc, char **argv)
{
	int	j;
	int	i;

	j = 1;
	i = 0;
	while (j != argc)
	{
		while (argv[j][i] == 32 || (argv[j][i] >= 9 && argv[j][i] <= 13))
			i++;
		if (argv[j][i] == '+')
			i++;
		while (argv[j][i] >= '0' && argv[j][i] <= '9')
			i++;
		if (i != ft_strlen(argv[j]))
			return (1);
		i = 0;
		j++;
	}
	return (0);
}
