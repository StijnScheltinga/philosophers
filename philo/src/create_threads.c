/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschelti <sschelti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:23:28 by sschelti          #+#    #+#             */
/*   Updated: 2023/06/06 17:20:32 by sschelti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*philo_start(void *phi_struct)
{
	t_philo	*philo;

	philo = (t_philo *)phi_struct;
	if (philo->i % 2 != 0)
		accurate_usleep(philo->data->time_to_eat);
	while (1)
	{
		pthread_mutex_lock(philo->data->finished_mutex);
		if (philo->data->finished == true)
		{
			pthread_mutex_unlock(philo->data->finished_mutex);
			break;
		}
		pthread_mutex_unlock(philo->data->finished_mutex);
		philo_eat(philo);
		pthread_mutex_lock(philo->data->eat_mutex);
		if (++philo->eat_n == philo->data->max_eat)
		{
			pthread_mutex_unlock(philo->data->eat_mutex);
			break ;
		}
		pthread_mutex_unlock(philo->data->eat_mutex);
		philo_sleep(philo);
		print_update("is thinking", NULL, NULL, philo);
	}
	return (NULL);
}

int	create_philosophers(t_data *data)
{
	unsigned int	i;
	void			*phi;

	i = 0;
	phi = NULL;
	while (i != data->num_of_philo)
	{
		phi = (void *)&data->phi_str[i];
		pthread_create(&data->philo_threads[i], NULL, &philo_start, phi);
		i++;
	}
	i = 0;
	philo_check(data);
	while (i != data->num_of_philo)
	{
		pthread_join(data->philo_threads[i], NULL);
		i++;
	}
	return (0);
}
