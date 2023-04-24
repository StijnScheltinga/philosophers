/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschelti <sschelti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 18:12:12 by sschelti          #+#    #+#             */
/*   Updated: 2023/04/24 18:19:15 by sschelti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>

typedef struct s_rules{
	unsigned int	number_of_philosophers;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	number_of_times_each_philosopher_must_eat;
}	t_rules;

int				set_rules(t_rules *rules, int argc, char **argv);
int				check_values(int argc, char **argv);
int				create_philosophers(t_rules *rules);

unsigned int	ft_uatoi(const char *str);
int				ft_strlen(const char *str);
void			print_struct(t_rules *rules);
void			*ft_test(void *in);

#endif