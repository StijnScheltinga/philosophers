/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschelti <sschelti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:23:28 by sschelti          #+#    #+#             */
/*   Updated: 2023/04/25 17:13:56 by sschelti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*philosopher(void *philo_data)
{
	t_philo_data	*philo;

	philo = (t_philo_data *)philo_data;
	
	printf("%d\n", j);
	return (NULL);
}

int	create_philosophers(t_rules *rules)
{
	pthread_t		*philo_id;
	t_philo_data	philo_data;
	int				i;

	philo_id = malloc(rules->number_of_philosophers * sizeof(pthread_t));
	if (!philo_id)
		return (1);
	i = 0;
	while (i != rules->number_of_philosophers)
	{
		philo_data.which_philo = i + 1;
		if (pthread_create(&philo_id[i], NULL, &philosopher, &philo_data) != 0)
			return (1);
		i++;
	}
	i = 0;
	while (i != rules->number_of_philosophers)
	{
		pthread_join(philo_id[i], NULL);
		i++;
	}
	free (philo_id);
	return (0);
}
