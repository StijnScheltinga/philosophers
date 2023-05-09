/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschelti <sschelti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:23:28 by sschelti          #+#    #+#             */
/*   Updated: 2023/05/09 17:05:57 by sschelti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*philo_start(void *philo_struct)
{
	t_philo	*philo;

	philo = (t_philo *)philo_struct;
	
	if (philo->philo_id % 2 == 0)
		philo_eat(philo);
	else
	{
		usleep(100);
		philo_eat(philo);
	}
	while (1)
	{
		philo_sleep(philo);
		printf("%ld %d is thinking\n", calculate_timestamp(&philo->start_of_program), philo->philo_id);
		philo_eat(philo);
	}
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
	while (i != data->number_of_philosophers)
	{
		pthread_join(data->philo_threads[i], NULL);
		i++;
	}
	return (0);
}
