/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschelti <sschelti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 18:01:05 by sschelti          #+#    #+#             */
/*   Updated: 2023/04/24 14:24:53 by sschelti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int argc, char **argv)
{
	t_rules	rules;

	if (set_rules(&rules, argc, argv) == 1)
		return (1);
	print_struct(&rules);
	if (create_philosophers(&rules) == 1)
		return (1);
	return (0);
}
