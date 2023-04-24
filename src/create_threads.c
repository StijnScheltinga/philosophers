/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschelti <sschelti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:23:28 by sschelti          #+#    #+#             */
/*   Updated: 2023/04/24 18:18:51 by sschelti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*ft_test(void *in)
{
	printf("jo\n");
	return (NULL);
}

int	create_philosophers(t_rules *rules)
{
	pthread_t	*philo_id;
	int			i;

	philo_id = (pthread_t *)malloc(rules->number_of_philosophers * sizeof(pthread_t));
	if (!philo_id)
		return (1);
	i = 0;
	while (i != rules->number_of_philosophers)
	{
		if (pthread_create(&philo_id[i], NULL, &ft_test, NULL) != 0)
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
