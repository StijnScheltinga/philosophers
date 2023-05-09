/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschelti <sschelti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 15:20:37 by sschelti          #+#    #+#             */
/*   Updated: 2023/05/09 16:58:48 by sschelti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_l);
		printf("%ld %d has taken a fork.\n", calculate_timestamp(&philo->start_of_program), philo->philo_id);
	pthread_mutex_lock(philo->fork_r);
		printf("%ld %d has taken a fork.\n", calculate_timestamp(&philo->start_of_program), philo->philo_id);
	printf("%ld %d is eating\n", calculate_timestamp(&philo->start_of_program), philo->philo_id);
	usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_unlock(philo->fork_r);
	philo->num_of_times_eaten++;
}

void	philo_sleep(t_philo *philo)
{
	printf("%ld %d is sleeping\n", calculate_timestamp(&philo->start_of_program), philo->philo_id);
	usleep(philo->data->time_to_sleep);
}