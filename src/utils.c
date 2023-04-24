/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschelti <sschelti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 14:27:00 by sschelti          #+#    #+#             */
/*   Updated: 2023/04/24 12:18:12 by sschelti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	print_struct(t_rules *rules)
{
	printf("philosophers: %u\n", rules->number_of_philosophers);
	printf("time to die: %u\n", rules->time_to_die);
	printf("time to eat: %u\n", rules->time_to_eat);
	printf("time to sleep: %u\n", rules->time_to_sleep);
	printf("number of times each hilosopher must eat: ");
	printf("%u\n", rules->number_of_times_each_philosopher_must_eat);
}

unsigned int	ft_uatoi(const char *str)
{
	unsigned int	res;
	int				i;

	res = 0;
	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res);
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
