/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschelti <sschelti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 18:01:05 by sschelti          #+#    #+#             */
/*   Updated: 2023/05/09 12:24:47 by sschelti         ###   ########.fr       */
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
	gettimeofday(&data.start_of_program, NULL);
	if (set_data(&data, argc, argv) == 1)
		return (1);
	if (set_philo(&data) == 1)
		return (1);
	print_struct(&data);
	if (create_philosophers(&data) == 1)
		return (1);
	calculate_timestamp(&data.start_of_program);
	freeall(&data);
	return (0);
}
