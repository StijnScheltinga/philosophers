/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschelti <sschelti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 15:20:37 by sschelti          #+#    #+#             */
/*   Updated: 2023/05/30 18:12:40 by sschelti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork_l->mutex);
		set_fork_lock(philo->fork_l, 1, philo);
		print_update("has taken a fork", NULL, philo);
	pthread_mutex_lock(&philo->fork_r->mutex);
		set_fork_lock(philo->fork_r, 1, philo);
		print_update("has taken a fork", "is eating", philo);
	pthread_mutex_lock(philo->data->locked_mutex);
		philo->last_time_eaten = cur_time(&philo->start);
	pthread_mutex_unlock(philo->data->locked_mutex);
	accurate_usleep(philo->safe_time_to_eat);
		set_fork_lock(philo->fork_l, 0, philo);
	pthread_mutex_unlock(&philo->fork_l->mutex);
		set_fork_lock(philo->fork_r, 0, philo);
	pthread_mutex_unlock(&philo->fork_r->mutex);
}

void	philo_sleep(t_philo *philo)
{
	print_update("is sleeping", NULL, philo);
	accurate_usleep(philo->safe_time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	pthread_mutex_lock(philo->data->locked_mutex);
	if ((philo->fork_l->locked == 1 || philo->fork_r->locked == 1))
	{
		pthread_mutex_unlock(philo->data->locked_mutex);
		print_update("is thinking", NULL, philo);
	}
	else
		pthread_mutex_unlock(philo->data->locked_mutex);
}

void	philo_check(t_data *data)
{
	int			i;
	long long	last_eat;

	i = 0;
	last_eat = 0;
	while (1)
	{
		// pthread_mutex_lock(data->locked_mutex);
		if (data->phi_str[i].eat_n == data->max_eat)
			break ;
		last_eat = data->phi_str[i].last_time_eaten;
		// pthread_mutex_unlock(data->locked_mutex);
		if (cur_time(&data->start) - last_eat >= data->time_to_die)
		{
			print_update("died", NULL, &data->phi_str[i]);
			pthread_mutex_lock(&data->finished->mutex);
			data->finished->finished = 1;
			pthread_mutex_unlock(&data->finished->mutex);
			break ;
		}
		usleep (50);
		i++;
		i = i % data->num_of_philo;
	}
}

void	print_update(char *str, char *str_2, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->finished->mutex);
	if (philo->data->finished->finished == 0)
	{
		pthread_mutex_unlock(&philo->data->finished->mutex);
		pthread_mutex_lock(philo->data->print_mutex);
		printf("%lld %d %s\n", cur_time(&philo->start), philo->i, str);
		if (str_2)
				printf("%lld %d %s\n", cur_time(&philo->start), philo->i, str_2);
		pthread_mutex_unlock(philo->data->print_mutex);
	}
	else
		pthread_mutex_unlock(&philo->data->finished->mutex);
}

void	set_fork_lock(t_fork *fork, int value, t_philo *philo)
{
	pthread_mutex_lock(philo->data->locked_mutex);
		fork->locked = value;
	pthread_mutex_unlock(philo->data->locked_mutex);
}