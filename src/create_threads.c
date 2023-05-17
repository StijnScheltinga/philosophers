/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschelti <sschelti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:23:28 by sschelti          #+#    #+#             */
/*   Updated: 2023/05/17 17:41:23 by sschelti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*philo_start(void *philo_struct)
{
	t_philo	*philo;
	philo = (t_philo *)philo_struct;
	
	if (philo->philo_id % 2 != 0)
		usleep(100);
	while (1)
	{
		pthread_mutex_lock(philo->data->print_mutex);
		if (philo->data->finished == 1)
			break ;
		pthread_mutex_unlock(philo->data->print_mutex);
		philo_eat(philo);
		philo_sleep(philo);
		usleep(100);
		philo_think(philo);
	}
	pthread_mutex_unlock(philo->data->print_mutex);
	return (NULL);
}

int	create_philosophers(t_data *data)
{
	int			i;

	i = 0;
	while (i != data->number_of_philosophers)
	{
		pthread_create(&data->philo_threads[i], NULL, &philo_start, (void *)&data->philo_structs[i]);
		i++;
	}
	i = 0;
	philo_check(data);
	while (i != data->number_of_philosophers)
	{
		pthread_join(data->philo_threads[i], NULL);
		i++;
	}
	return (0);
}
