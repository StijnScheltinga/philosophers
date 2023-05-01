/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschelti <sschelti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:23:28 by sschelti          #+#    #+#             */
/*   Updated: 2023/05/01 14:25:07 by sschelti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

//gets a certain philosopher struct as input
void	*philo_start(void *philo_struct)
{
	t_philo	*philo;

	philo = (t_philo *)philo_struct;
	printf("this is philosopher: %d\n", philo->philo_id);
	return (NULL);
}

//create different threads, every philosopher has its own struct
// + a pointer to the constant data
int	create_philosophers(t_data *data)
{
	t_philo		*philo_structs;
	pthread_t	*philo_threads;
	int			i;

	philo_structs = malloc(data->number_of_philosophers * sizeof(t_philo));
	if (!philo_structs)
		return (1);
	philo_threads = malloc(data->number_of_philosophers * sizeof(pthread_t));
	if (!philo_structs)
		return (1);
	i = 0;
	while (i != data->number_of_philosophers)
	{
		philo_structs[i].philo_id = i + 1;
		philo_structs[i].data = data;
		pthread_create(&philo_threads[i], NULL, &philo_start, (void *)&philo_structs[i]);
		i++;
	}
	i = 0;
	while (i != data->number_of_philosophers)
	{
		pthread_join(philo_threads[i], NULL);
		i++;
	}
	free(philo_structs);
	free(philo_threads);
	return (0);
}
