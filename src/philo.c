/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschelti <sschelti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 15:20:37 by sschelti          #+#    #+#             */
/*   Updated: 2023/05/20 16:36:15 by sschelti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork_l->mutex);
	pthread_mutex_lock(philo->data->print_mutex);
	if (philo->data->finished == 0)
		printf("%lld %d has taken a fork.\n", calculate_timestamp(&philo->start_of_program), philo->philo_id);
	philo->fork_l->locked = 1;
	pthread_mutex_unlock(philo->data->print_mutex);
	pthread_mutex_lock(&philo->fork_r->mutex);
	philo->fork_r->locked = 1;
	pthread_mutex_lock(philo->data->print_mutex);
	if (philo->data->finished == 0)
		printf("%lld %d has taken a fork.\n", calculate_timestamp(&philo->start_of_program), philo->philo_id);
	if (philo->data->finished == 0)
		printf("%lld %d is eating\n", calculate_timestamp(&philo->start_of_program), philo->philo_id);
	pthread_mutex_unlock(philo->data->print_mutex);
	accurate_usleep(philo->data->time_to_eat, philo);
	pthread_mutex_unlock(&philo->fork_l->mutex);
	philo->fork_l->locked = 0;
	pthread_mutex_unlock(&philo->fork_r->mutex);
	philo->fork_r->locked = 0;
}

void	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(philo->data->print_mutex);
	if (philo->data->finished == 0)
		printf("%lld %d is sleeping\n", calculate_timestamp(&philo->start_of_program), philo->philo_id);
	pthread_mutex_unlock(philo->data->print_mutex);
	accurate_usleep(philo->data->time_to_sleep, NULL);
}

void	philo_think(t_philo *philo)
{
	if ((philo->fork_l->locked == 1 || philo->fork_r->locked == 1))
	{
		pthread_mutex_lock(philo->data->print_mutex);
		if (philo->data->finished == 0)
			printf("%lld %d is thinking\n", calculate_timestamp(&philo->start_of_program), philo->philo_id);
		pthread_mutex_unlock(philo->data->print_mutex);
	}
}

void	philo_check(t_data *data)
{
	int	i;

	i = 0;
	while (1)
	{
		pthread_mutex_lock(data->print_mutex);
		if (data->philo_str[i].eat_n == data->max_eat)
			break ;
		if (calculate_timestamp(&data->start_of_program) - data->philo_str[i].last_time_eaten > data->time_to_die)
		{
			printf("%lld %d has died\n", calculate_timestamp(&data->start_of_program), data->philo_str[i].philo_id);
			data->finished = 1;
			pthread_mutex_unlock(data->print_mutex);
			break ;
		}
		pthread_mutex_unlock(data->print_mutex);
		usleep(100);
		i++;
		i = i % data->num_of_philo;
	}
}