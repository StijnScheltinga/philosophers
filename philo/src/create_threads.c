/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschelti <sschelti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:23:28 by sschelti          #+#    #+#             */
/*   Updated: 2023/05/30 18:11:58 by sschelti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*philo_start(void *phi_struct)
{
	t_philo	*philo;

	philo = (t_philo *)phi_struct;
	if (philo->i % 2 != 0)
		usleep(1000);
	while (1)
	{
		philo_eat(philo);
		// pthread_mutex_lock(philo->data->locked_mutex);
		if (++philo->eat_n == philo->data->max_eat)
			break ;
		// pthread_mutex_unlock(philo->data->locked_mutex);
		pthread_mutex_lock(&philo->data->finished->mutex);
		if (philo->data->finished->finished == 1)
			break ;
		pthread_mutex_unlock(&philo->data->finished->mutex);
		philo_sleep(philo);
		philo_think(philo);
	}
	pthread_mutex_unlock(philo->data->print_mutex);
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
