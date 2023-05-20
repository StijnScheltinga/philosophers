/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschelti <sschelti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 18:12:12 by sschelti          #+#    #+#             */
/*   Updated: 2023/05/20 15:02:59 by sschelti         ###   ########.fr       */
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
typedef struct s_fork t_fork;

typedef struct s_data{
	unsigned int	number_of_philosophers;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	unsigned int	finished;
	struct timeval	start_of_program;
	t_philo			*philo_structs;
	pthread_t		*philo_threads;
	t_fork			*forks;
	pthread_mutex_t	*print_mutex;
}	t_data;

typedef struct s_philo{
	int				philo_id;
	t_fork			*fork_l;
	t_fork			*fork_r;
	struct timeval	start_of_program;
	long long		last_time_eaten;
	int				eat_n;
	t_data			*data;
}	t_philo;

typedef struct s_fork{
	pthread_mutex_t mutex;
	int				locked;
}	t_fork;

int				set_data(t_data *data, int argc, char **argv);
int				check_values(int argc, char **argv);
int				create_philosophers(t_data *data);
void			*philo_start(void *philo_struct);
int				set_philo(t_data *data);
void			philo_eat(t_philo *philo);
void			philo_sleep(t_philo *philo);
void			philo_think(t_philo *philo);
void			philo_check(t_data *data);

unsigned int	ft_uatoi(const char *str);
int				ft_strlen(const char *str);
void			print_struct(t_data *data);
int				freeall(t_data *data);
long long		calculate_timestamp(struct timeval *start);
void			accurate_usleep(unsigned int ms, t_philo *philo);
long long		timestamp(struct timeval time);

#endif