/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschelti <sschelti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 14:48:59 by sschelti          #+#    #+#             */
/*   Updated: 2023/05/20 16:46:08 by sschelti         ###   ########.fr       */
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
	if (!argv[1][0] || !argv[2][0] || !argv[3][0] || !argv[4][0] 
		|| (argv[5] && !argv[5][0]))
		return (1);
	data->finished = 0;
	data->num_of_philo = ft_uatoi(argv[1]);
	data->time_to_die = ft_uatoi(argv[2]);
	data->time_to_eat = ft_uatoi(argv[3]);
	data->time_to_sleep = ft_uatoi(argv[4]);
	if (argv[5])
		data->max_eat = ft_uatoi(argv[5]);
	else
		data->max_eat = -1;
	if (gettimeofday(&data->start_of_program, NULL) == -1)
		return (1);
	return (0);
}

int	set_philo(t_data *data)
{
	int	i;

	i = -1;
	data->philo_str = malloc(data->num_of_philo * sizeof(t_philo));
	data->philo_threads = malloc(data->num_of_philo * sizeof(pthread_t));
	data->forks = malloc(data->num_of_philo * sizeof(t_fork));
	data->print_mutex = malloc(sizeof(pthread_mutex_t));
	if (!data->philo_str || !data->philo_threads
		|| !data->forks || !data->print_mutex)
		return (1);
	if (pthread_mutex_init(data->print_mutex, NULL) != 0)
		return (1);
	while (++i != data->num_of_philo)
	{
		if (set_individual_philo(data, i) == 1)
			return (1);
	}
	return (0);
}

int	set_individual_philo(t_data *data, int i)
{
	data->philo_str[i].philo_id = i + 1;
	data->philo_str[i].data = data;
	data->philo_str[i].fork_l = &data->forks[i];
	data->philo_str[i].fork_r = &data->forks[(i + 1) % data->num_of_philo];
	if (pthread_mutex_init(&data->forks[i].mutex, NULL) != 0)
		return (1);
	data->forks[i].locked = 0;
	data->philo_str[i].start_of_program = data->start_of_program;
	data->philo_str[i].last_time_eaten = 0;
	data->philo_str[i].eat_n = 0;
	data->philo_str[i].finished = 0;
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
