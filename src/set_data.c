/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschelti <sschelti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 14:48:59 by sschelti          #+#    #+#             */
/*   Updated: 2023/05/09 16:59:21 by sschelti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	set_data(t_data *data, int argc, char **argv)
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
	data->number_of_philosophers = ft_uatoi(argv[1]);
	if (data->number_of_philosophers > 20
		|| data->number_of_philosophers < 1)
	{
		printf("Number of philosophers must be between 1 and 20\n");
		return (1);
	}
	data->time_to_die = ft_uatoi(argv[2]) * 1000;
	data->time_to_eat = ft_uatoi(argv[3]) * 1000;
	data->time_to_sleep = ft_uatoi(argv[4]) * 1000;
	if (argv[5])
		data->number_of_times_each_philosopher_must_eat = ft_uatoi(argv[5]);
	else
		data->number_of_times_each_philosopher_must_eat = 0;
	return (0);
}

int	set_philo(t_data *data)
{
	int	i;

	i = 0;
	data->philo_structs = malloc(data->number_of_philosophers * sizeof(t_philo));
	data->philo_threads = malloc(data->number_of_philosophers * sizeof(pthread_t));
	data->forks = malloc(data->number_of_philosophers * sizeof(pthread_mutex_t));
	if (!data->philo_structs || !data->philo_threads || !data->forks)
		return (1);
	while (i != data->number_of_philosophers)
	{
		data->philo_structs[i].philo_id = i + 1;
		data->philo_structs[i].data = data;
		data->philo_structs[i].fork_l = &data->forks[i];
		pthread_mutex_init(&data->forks[i], NULL);
		data->philo_structs[i].fork_r = &data->forks[(i + 1) % data->number_of_philosophers];
		data->philo_structs[i].start_of_program = data->start_of_program;
		data->philo_structs[i].num_of_times_eaten = 0;
		i++;
	}
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
