/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschelti <sschelti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 14:48:59 by sschelti          #+#    #+#             */
/*   Updated: 2023/06/08 17:13:31 by sschelti         ###   ########.fr       */
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
	data->num_of_philo = ft_uatoi(argv[1]);
	data->time_to_die = ft_uatoi(argv[2]);
	data->time_to_eat = ft_uatoi(argv[3]);
	data->time_to_sleep = ft_uatoi(argv[4]);
	if (argv[5])
		data->max_eat = ft_uatoi(argv[5]);
	else
		data->max_eat = -1;
	data->last_eat = 0;
	data->philos_finished = 0;
	return (0);
}

int	set_philo(t_data *data)
{
	unsigned int	i;

	i = -1;
	data->phi_str = malloc(data->num_of_philo * sizeof(t_philo));
	data->phi_t = malloc(data->num_of_philo * sizeof(pthread_t));
	data->forks = malloc(data->num_of_philo * sizeof(pthread_mutex_t));
	data->print_mutex = malloc(sizeof(pthread_mutex_t));
	data->finished_mutex = malloc(sizeof(pthread_mutex_t));
	data->eat_mutex = malloc(sizeof(pthread_mutex_t));
	if (!data->phi_str || !data->phi_t || !data->finished_mutex
		|| !data->forks || !data->print_mutex || !data->eat_mutex)
		return (1);
	data->finished = false;
	if (pthread_mutex_init(data->print_mutex, NULL) != 0
		|| pthread_mutex_init(data->finished_mutex, NULL) != 0
		|| pthread_mutex_init(data->eat_mutex, NULL) != 0)
		return (1);
	if (gettimeofday(&data->start, NULL) == -1)
		return (1);
	while (++i != data->num_of_philo)
	{
		if (set_individual_philo(data, i) == 1)
			return (1);
	}
	return (0);
}

int	set_individual_philo(t_data *data, unsigned int i)
{
	data->phi_str[i].i = i + 1;
	data->phi_str[i].data = data;
	data->phi_str[i].fork_l = &data->forks[i];
	data->phi_str[i].fork_r = &data->forks[(i + 1) % data->num_of_philo];
	if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		return (1);
	data->phi_str[i].start = data->start;
	data->phi_str[i].eat_n = 0;
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

unsigned int	ft_uatoi(const char *str)
{
	unsigned int	res;
	int				i;

	res = 0;
	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res);
}
