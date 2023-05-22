/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschelti <sschelti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 15:20:37 by sschelti          #+#    #+#             */
/*   Updated: 2023/05/22 14:31:23 by sschelti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	philo_eat(t_philo *philo)
{
	unsigned int	safe_time_to_eat;

	pthread_mutex_lock(&philo->fork_l->mutex);
	pthread_mutex_lock(philo->data->general_mutex);
	if (philo->data->finished == 0)
		printf("%lld %d has taken a fork.\n", cur_time(&philo->start), philo->i);
	philo->fork_l->locked = 1;
	pthread_mutex_unlock(philo->data->general_mutex);
	pthread_mutex_lock(&philo->fork_r->mutex);
	philo->fork_r->locked = 1;
	pthread_mutex_lock(philo->data->general_mutex);
	if (philo->data->finished == 0)
	{
		printf("%lld %d has taken a fork.\n", cur_time(&philo->start), philo->i);
		printf("%lld %d is eating\n", cur_time(&philo->start), philo->i);
	}
	safe_time_to_eat = philo->data->time_to_eat;
	pthread_mutex_unlock(philo->data->general_mutex);
	philo->last_time_eaten = cur_time(&philo->start);
	accurate_usleep(safe_time_to_eat);
	philo->fork_l->locked = 0;
	pthread_mutex_unlock(&philo->fork_l->mutex);
	philo->fork_r->locked = 0;
	pthread_mutex_unlock(&philo->fork_r->mutex);
}

void	philo_sleep(t_philo *philo)
{
	unsigned int	safe_time_to_sleep;

	pthread_mutex_lock(philo->data->general_mutex);
	if (philo->data->finished == 0)
		printf("%lld %d is sleeping\n", cur_time(&philo->start), philo->i);
	safe_time_to_sleep = philo->data->time_to_sleep;
	pthread_mutex_unlock(philo->data->general_mutex);
	accurate_usleep(safe_time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	pthread_mutex_lock(philo->data->general_mutex);
	if ((philo->fork_l->locked == 1 || philo->fork_r->locked == 1))
	{
		if (philo->data->finished == 0)
			printf("%lld %d is thinking\n", cur_time(&philo->start), philo->i);
	}
	pthread_mutex_unlock(philo->data->general_mutex);
}

void	philo_check(t_data *data)
{
	int			i;
	long long	last_eat;

	i = 0;
	last_eat = 0;
	while (1)
	{
		if (data->phi_str[i].eat_n == data->max_eat)
			break ;
		pthread_mutex_lock(data->general_mutex);
		last_eat = data->phi_str[i].last_time_eaten;
		if (cur_time(&data->start) - last_eat >= data->time_to_die)
		{
			printf("%lld %d died\n", cur_time(&data->start), data->phi_str[i].i);
			data->finished = 1;
			pthread_mutex_unlock(data->general_mutex);
			break ;
		}
		pthread_mutex_unlock(data->general_mutex);
		usleep(100);
		i++;
		i = i % data->num_of_philo;
	}
}
