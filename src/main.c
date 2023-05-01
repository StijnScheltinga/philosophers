/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschelti <sschelti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 18:01:05 by sschelti          #+#    #+#             */
/*   Updated: 2023/05/01 13:31:01 by sschelti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	leaks(void)
{
	system("leaks philo");
}

int	main(int argc, char **argv)
{
	t_data	data;

	atexit(leaks);
	if (set_data(&data, argc, argv) == 1)
		return (1);
	print_struct(&data);
	if (create_philosophers(&data) == 1)
		return (1);
	return (0);
}
