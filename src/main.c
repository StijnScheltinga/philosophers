/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschelti <sschelti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 18:01:05 by sschelti          #+#    #+#             */
/*   Updated: 2023/05/15 13:28:09 by sschelti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	leaks(void)
{
	system("leaks -s philo");
}

int	main(int argc, char **argv)
{
	t_data	data;

	atexit(leaks);
	data.philo_structs = NULL;
	data.philo_threads = NULL;
	data.forks = NULL;
	if (set_data(&data, argc, argv) == 1)
		return (1);
	if (set_philo(&data) == 1)
		return (freeall(&data));
	print_struct(&data);
	if (create_philosophers(&data) == 1)
		return (freeall(&data));
	freeall(&data);
	return (0);
}
