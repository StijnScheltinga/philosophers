/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschelti <sschelti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 15:20:37 by sschelti          #+#    #+#             */
/*   Updated: 2023/06/06 17:59:10 by sschelti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_l);
	pthread_mutex_lock(philo->fork_r);
	print_update("has taken a fork", "has taken a fork", "is eating", philo);
	pthread_mutex_lock(philo->data->eat_mutex);
		philo->last_eat = cur_time(&philo->data->start);
	pthread_mutex_unlock(philo->data->eat_mutex);
	accurate_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_unlock(philo->fork_r);
}

void	philo_sleep(t_philo *philo)
{
	print_update("is sleeping", NULL, NULL, philo);
	accurate_usleep(philo->data->time_to_sleep);
}

void	philo_check(t_data *data)
{
	int				i;
	long long		last_eat;
	unsigned int	philos_finished;

	i = 0;
	last_eat = 0;
	philos_finished = 0;
	while (1)
	{
		pthread_mutex_lock(data->eat_mutex);
		if (data->phi_str[i].eat_n == data->max_eat)
		{
			philos_finished++;
			data->phi_str[i].eat_n++;
		}
		last_eat = data->phi_str[i].last_eat;
		pthread_mutex_unlock(data->eat_mutex);
		if (philos_finished == data->num_of_philo)
			break ;
		if (cur_time(&data->start) - last_eat >= data->time_to_die)
		{
			print_update("has died", NULL, NULL, &data->phi_str[i]);
			pthread_mutex_lock(data->finished_mutex);
			data->finished = true;
			pthread_mutex_unlock(data->finished_mutex);
			break ;
		}
		i++;
		i = i % data->num_of_philo;
	}
}

void	print_update(char *s, char *s2, char *s3, t_philo *philo)
{
	pthread_mutex_lock(philo->data->finished_mutex);
	if (philo->data->finished == false)
	{
		pthread_mutex_unlock(philo->data->finished_mutex);
		pthread_mutex_lock(philo->data->print_mutex);
		printf("%lld %d %s\n", cur_time(&philo->start), philo->i, s);
		if (s2)
			printf("%lld %d %s\n", cur_time(&philo->start), philo->i, s2);
		if (s3)
			printf("%lld %d %s\n", cur_time(&philo->start), philo->i, s3);
		pthread_mutex_unlock(philo->data->print_mutex);
	}
	else
		pthread_mutex_unlock(philo->data->finished_mutex);
}