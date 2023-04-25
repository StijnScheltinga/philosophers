/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschelti <sschelti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:23:28 by sschelti          #+#    #+#             */
/*   Updated: 2023/04/25 12:59:13 by sschelti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*philosopher(void *rules)
{
	t_rules	*data;

	data = (t_rules *)rules;
	return (NULL);
}

int	create_philosophers(t_rules *rules)
{
	int				i;

	rules->philo_id = malloc(rules->number_of_philosophers * sizeof(pthread_t));
	if (!rules->philo_id)
		return (1);
	i = 0;
	create_forks(rules);
	while (i != rules->number_of_philosophers)
	{
		if (pthread_create(&rules->philo_id[i], NULL, &philosopher, rules) != 0)
			return (1);
		i++;
	}
	i = 0;
	while (i != rules->number_of_philosophers)
	{
		pthread_join(rules->philo_id[i], NULL);
		i++;
	}
	destroy_forks(rules);
	free (rules->philo_id);
	return (0);
}

void	create_forks(t_rules *rules)
{
	int	number_of_forks;
	int	i;

	number_of_forks = rules->number_of_philosophers;
	rules->forks = malloc(number_of_forks * sizeof(pthread_mutex_t));
	while (i != number_of_forks)
	{
		pthread_mutex_init(&rules->forks[i], NULL);
		i++;
	}
}

void	destroy_forks(t_rules *rules)
{
	int	number_of_forks;
	int	i;

	number_of_forks = rules->number_of_philosophers;
	while (i != number_of_forks)
	{
		pthread_mutex_destroy(&rules->forks[i]);
		i++;
	}
	free(rules->forks);
}
