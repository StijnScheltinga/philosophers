/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschelti <sschelti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 14:27:00 by sschelti          #+#    #+#             */
/*   Updated: 2023/06/13 12:57:01 by sschelti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

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

long long	timestamp(struct timeval time)
{
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	accurate_usleep(unsigned int ms)
{
	struct timeval	start;
	struct timeval	current;

	gettimeofday(&start, NULL);
	while (1)
	{
		gettimeofday(&current, NULL);
		if (timestamp(current) - timestamp(start) >= ms)
			break ;
		usleep(300);
	}
}

int	freeall(t_data *data)
{
	unsigned int	i;

	i = 0;
	free(data->phi_str);
	free(data->phi_t);
	if (data->print_mutex)
		pthread_mutex_destroy(data->print_mutex);
	if (data->finished_mutex)
		pthread_mutex_destroy(data->finished_mutex);
	if (data->eat_mutex)
		pthread_mutex_destroy(data->eat_mutex);
	free(data->print_mutex);
	free(data->finished_mutex);
	free(data->eat_mutex);
	while (i != data->num_of_philo && data->forks)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->forks);
	return (1);
}
