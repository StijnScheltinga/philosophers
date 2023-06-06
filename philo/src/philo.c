/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschelti <sschelti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 15:20:37 by sschelti          #+#    #+#             */
/*   Updated: 2023/06/06 14:48:56 by sschelti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_l);
	print_update("has taken a fork", philo);
	pthread_mutex_lock(philo->fork_r);
	print_update("has taken a fork", philo);
	print_update("is eating", philo);
	accurate_usleep(philo->safe_time_to_eat);
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_unlock(philo->fork_r);
}

void	philo_sleep(t_philo *philo)
{
	print_update("is sleeping", philo);
	accurate_usleep(philo->safe_time_to_sleep);
}

void	philo_check(t_data *data)
{
	int			i;
	long long	last_eat;

	i = 0;
	last_eat = 0;
	while (1)
	{

		i++;
		i = i % data->num_of_philo;
	}
}

void	print_update(char *str, t_philo *philo)
{
	pthread_mutex_lock(philo->data->print_mutex);
	printf("%lld %d %s\n", cur_time(&philo->start), philo->i, str);
	pthread_mutex_unlock(philo->data->print_mutex);
}