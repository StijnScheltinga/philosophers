/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschelti <sschelti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 18:12:12 by sschelti          #+#    #+#             */
/*   Updated: 2023/05/09 16:58:14 by sschelti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo t_philo;

typedef struct s_data{
	unsigned int	number_of_philosophers;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	number_of_times_each_philosopher_must_eat;
	struct timeval	start_of_program;
	t_philo			*philo_structs;
	pthread_t		*philo_threads;
	pthread_mutex_t	*forks;
}	t_data;

typedef struct s_philo{
	int				philo_id;
	unsigned int	num_of_times_eaten;
	pthread_mutex_t	*fork_l;
	pthread_mutex_t *fork_r;
	struct timeval	start_of_program;
	t_data			*data;
}	t_philo;

int				set_data(t_data *data, int argc, char **argv);
int				check_values(int argc, char **argv);
int				create_philosophers(t_data *data);
void			*philo_start(void *philo_struct);
int				set_philo(t_data *data);
void			philo_eat(t_philo *philo);
void			philo_sleep(t_philo *philo);

void			get_start_of_program(t_data *data);
long			calculate_timestamp(struct timeval *start_of_program);
unsigned int	ft_uatoi(const char *str);
int				ft_strlen(const char *str);
void			print_struct(t_data *data);
void			*ft_test(void *in);
void			freeall(t_data *data);

#endif