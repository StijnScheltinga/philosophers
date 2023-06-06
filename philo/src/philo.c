/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschelti <sschelti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 15:20:37 by sschelti          #+#    #+#             */
/*   Updated: 2023/06/06 12:19:42 by sschelti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_l);
	print_update("has taken a fork", NULL, philo);
	pthread_mutex_lock(philo->fork_r);
	print_update("has taken a fork", "is eating", philo);
	pthread_mutex_lock(philo->data->general_mutex);
	philo->last_time_eaten = cur_time(&philo->start);
	pthread_mutex_unlock(philo->data->general_mutex);
	accurate_usleep(philo->safe_time_to_eat);
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_unlock(philo->fork_r);
}

void	philo_sleep(t_philo *philo)
{
	print_update("is sleeping", NULL, philo);
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
		pthread_mutex_lock(data->general_mutex);
		if (data->phi_str[i].eat_n == data->max_eat)
		{
			pthread_mutex_unlock(data->general_mutex);
			break ;
		}
		last_eat = data->phi_str[i].last_time_eaten;
		pthread_mutex_unlock(data->general_mutex);
		if (cur_time(&data->start) - last_eat >= data->time_to_die)
		{
			print_update("died", NULL, &data->phi_str[i]);
			pthread_mutex_lock(data->fin_mutex);
			data->fin_bool = true;
			pthread_mutex_unlock(data->fin_mutex);
			break ;
		}
		usleep (50);
		i++;
		i = i % data->num_of_philo;
	}
}

void	print_update(char *str, char *str_2, t_philo *philo)
{
	pthread_mutex_lock(philo->data->fin_mutex);
	if (philo->data->fin_bool == false)
	{
		pthread_mutex_unlock(philo->data->fin_mutex);
		pthread_mutex_lock(philo->data->print_mutex);
		printf("%lld %d %s\n", cur_time(&philo->start), philo->i, str);
		if (str_2)
				printf("%lld %d %s\n", cur_time(&philo->start), philo->i, str_2);
		pthread_mutex_unlock(philo->data->print_mutex);
	}
	else
		pthread_mutex_unlock(philo->data->fin_mutex);
}
