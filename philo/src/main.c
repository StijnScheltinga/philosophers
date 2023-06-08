/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschelti <sschelti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 18:01:05 by sschelti          #+#    #+#             */
/*   Updated: 2023/06/08 17:54:51 by sschelti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	f(void)
{
	system("leaks -s philo");
}

int	main(int argc, char **argv)
{
	t_data	data;

	atexit(f);
	if (set_data(&data, argc, argv) == 1)
		return (1);
	if (set_philo(&data) == 1)
		return (freeall(&data));
	if (create_philosophers(&data) == 1)
		return (freeall(&data));
	freeall(&data);
	return (0);
}
