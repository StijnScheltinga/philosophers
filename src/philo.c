/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschelti <sschelti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 15:20:37 by sschelti          #+#    #+#             */
/*   Updated: 2023/05/17 11:26:55 by sschelti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork_l->mutex);
		printf("%lld %d has taken a fork.\n", calculate_timestamp(&philo->start_of_program), philo->philo_id);
		philo->fork_l->locked = 1;
	pthread_mutex_lock(&philo->fork_r->mutex);
		printf("%lld %d has taken a fork.\n", calculate_timestamp(&philo->start_of_program), philo->philo_id);
		philo->fork_r->locked = 1;
	pthread_mutex_lock(philo->data->print_mutex);
	printf("%lld %d is eating\n", calculate_timestamp(&philo->start_of_program), philo->philo_id);
	pthread_mutex_unlock(philo->data->print_mutex);
	accurate_usleep(philo->data->time_to_eat);
	// usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->fork_l->mutex);
	philo->fork_l->locked = 0;
	pthread_mutex_unlock(&philo->fork_r->mutex);
	philo->fork_r->locked = 0;
	philo->num_of_times_eaten++;
}

void	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(philo->data->print_mutex);
	printf("%lld %d is sleeping\n", calculate_timestamp(&philo->start_of_program), philo->philo_id);
	pthread_mutex_unlock(philo->data->print_mutex);
	accurate_usleep(philo->data->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	if (philo->fork_l->locked == 1 || philo->fork_r->locked == 1)
	{
		pthread_mutex_lock(philo->data->print_mutex);
		printf("%lld %d is thinking\n", calculate_timestamp(&philo->start_of_program), philo->philo_id);
		pthread_mutex_unlock(philo->data->print_mutex);
	}
}
