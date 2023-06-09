/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschelti <sschelti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 15:20:37 by sschelti          #+#    #+#             */
/*   Updated: 2023/06/09 13:19:18 by sschelti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_l);
	print_update("has taken a fork", NULL, philo);
	pthread_mutex_lock(philo->fork_r);
	print_update("has taken a fork", "is eating", philo);
	pthread_mutex_lock(philo->data->eat_mutex);
		philo->last_eat = cur_time(&philo->data->start);
	pthread_mutex_unlock(philo->data->eat_mutex);
	accurate_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_unlock(philo->fork_r);
}

void	philo_check(t_data *data)
{
	int				i;

	i = 0;
	while (1)
	{
		check_max_eat(data, i);
		if (data->philos_finished == data->num_of_philo)
			break ;
		if (cur_time(&data->start) - data->last_eat >= data->time_to_die)
		{
			print_update("died", NULL, &data->phi_str[i]);
			pthread_mutex_lock(data->finished_mutex);
			data->finished = true;
			pthread_mutex_unlock(data->finished_mutex);
			break ;
		}
		i++;
		i = i % data->num_of_philo;
	}
}

void	check_max_eat(t_data *data, int i)
{
	pthread_mutex_lock(data->eat_mutex);
	if (data->phi_str[i].eat_n == data->max_eat)
	{
		data->philos_finished++;
		data->phi_str[i].eat_n++;
	}
	data->last_eat = data->phi_str[i].last_eat;
	pthread_mutex_unlock(data->eat_mutex);
}

void	print_update(char *s, char *s2, t_philo *philo)
{
	pthread_mutex_lock(philo->data->finished_mutex);
	if (philo->data->finished == false)
	{
		pthread_mutex_unlock(philo->data->finished_mutex);
		pthread_mutex_lock(philo->data->print_mutex);
		printf("%lld %d %s\n", cur_time(&philo->start), philo->i, s);
		if (s2)
			printf("%lld %d %s\n", cur_time(&philo->start), philo->i, s2);
		pthread_mutex_unlock(philo->data->print_mutex);
	}
	else
		pthread_mutex_unlock(philo->data->finished_mutex);
}

int	detach_threads(t_data *data, int i)
{
	int	j;

	j = 0;
	while (j <= i)
	{
		pthread_detach(data->phi_t[j]);
		j++;
	}
	pthread_mutex_lock(data->finished_mutex);
	data->finished = true;
	pthread_mutex_unlock(data->finished_mutex);
	accurate_usleep(data->time_to_die);
	accurate_usleep(data->time_to_eat);
	accurate_usleep(data->time_to_sleep);
	return (1);
}
