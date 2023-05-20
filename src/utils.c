/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschelti <sschelti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 14:27:00 by sschelti          #+#    #+#             */
/*   Updated: 2023/05/20 16:55:35 by sschelti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

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

long long	cur_time(struct timeval *start)
{
	struct timeval	time_of_execution;

	gettimeofday(&time_of_execution, NULL);
	return (timestamp(time_of_execution) - timestamp(*start));
}

long long		timestamp(struct timeval time)
{
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	accurate_usleep(unsigned int ms, t_philo *philo)
{
	struct timeval	start;
	struct timeval	current;

	gettimeofday(&start, NULL);
	while (1)
	{
		gettimeofday(&current, NULL);
		if (philo)
			philo->last_time_eaten = cur_time(&philo->start);
		if (timestamp(current) - timestamp(start) >= ms)
			break;
		usleep(75);
	}
}

int	freeall(t_data *data)
{
	int	i;

	i = 0;
	free(data->philo_str);
	free(data->philo_threads);
	pthread_mutex_destroy(data->print_mutex);
	free(data->print_mutex);
	while (i != data->num_of_philo)
	{
		pthread_mutex_destroy(&data->forks[i].mutex);
		i++;
	}
	free(data->forks);
	return (1);
}
