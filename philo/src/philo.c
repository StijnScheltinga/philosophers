/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschelti <sschelti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 15:20:37 by sschelti          #+#    #+#             */
/*   Updated: 2023/06/06 15:41:43 by sschelti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_l);
	pthread_mutex_lock(philo->fork_r);
	print_update("has taken a fork", NULL, philo);
	print_update("has taken a fork", "is eating", philo);
	accurate_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_unlock(philo->fork_r);
}

void	philo_sleep(t_philo *philo)
{
	print_update("is sleeping", NULL, philo);
	accurate_usleep(philo->data->time_to_sleep);
}

void	philo_check(t_data *data)
{
	int			i;
	long long	last_eat;

	i = 0;
	last_eat = 0;
	while (1)
	{
		accurate_usleep(1000);
		pthread_mutex_lock(data->finished_mutex);
		data->finished = true;
		pthread_mutex_unlock(data->finished_mutex);
		break;
		i++;
		i = i % data->num_of_philo;
	}
}

void	print_update(char *str, char *str2, t_philo *philo)
{
	pthread_mutex_lock(philo->data->finished_mutex);
	if (philo->data->finished == false)
	{
		pthread_mutex_unlock(philo->data->finished_mutex);
		pthread_mutex_lock(philo->data->print_mutex);
		printf("%lld %d %s\n", cur_time(&philo->start), philo->i, str);
		if (str2)
			printf("%lld %d %s\n", cur_time(&philo->start), philo->i, str2);
		pthread_mutex_unlock(philo->data->print_mutex);
	}
	else
		pthread_mutex_unlock(philo->data->finished_mutex);
}