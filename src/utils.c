/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschelti <sschelti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 14:27:00 by sschelti          #+#    #+#             */
/*   Updated: 2023/05/09 15:11:56 by sschelti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	print_struct(t_data *data)
{
	printf("philosophers: %u\n", data->number_of_philosophers);
	printf("time to die: %u\n", data->time_to_die);
	printf("time to eat: %u\n", data->time_to_eat);
	printf("time to sleep: %u\n", data->time_to_sleep);
	printf("number of times each philosopher must eat: ");
	printf("%u\n", data->number_of_times_each_philosopher_must_eat);
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

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

long	calculate_timestamp(struct timeval *start_of_program)
{
	struct timeval	time_of_execution;
	long			timestamp_sec;
	long			timestamp_usec;

	gettimeofday(&time_of_execution, NULL);
	timestamp_sec = time_of_execution.tv_sec - start_of_program->tv_sec;
	timestamp_usec = time_of_execution.tv_usec - start_of_program->tv_usec;
	timestamp_usec /= 1000;
	timestamp_usec += timestamp_sec * 1000;
	return (timestamp_usec);
}

void	freeall(t_data *data)
{
	int	i;

	i = 0;
	free(data->philo_structs);
	free(data->philo_threads);
	while (i != data->number_of_philosophers)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->forks);
}
