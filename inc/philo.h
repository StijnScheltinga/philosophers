/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschelti <sschelti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 18:12:12 by sschelti          #+#    #+#             */
/*   Updated: 2023/05/20 16:55:35 by sschelti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo	t_philo;
typedef struct s_fork	t_fork;

typedef struct s_data{
	unsigned int	num_of_philo;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	int				max_eat;
	unsigned int	finished;
	struct timeval	start;
	t_philo			*philo_str;
	pthread_t		*philo_threads;
	t_fork			*forks;
	pthread_mutex_t	*print_mutex;
}	t_data;

typedef struct s_philo{
	int				philo_id;
	t_data			*data;
	t_fork			*fork_l;
	t_fork			*fork_r;
	struct timeval	start;
	long long		last_time_eaten;
	int				finished;
	int				eat_n;
}	t_philo;

typedef struct s_fork{
	pthread_mutex_t	mutex;
	int				locked;
}	t_fork;

int				set_data(t_data *data, int argc, char **argv);
int				check_values(int argc, char **argv);
int				create_philosophers(t_data *data);
void			*philo_start(void *philo_struct);
int				set_philo(t_data *data);
int				set_individual_philo(t_data *data, int i);
void			philo_eat(t_philo *philo);
void			philo_sleep(t_philo *philo);
void			philo_think(t_philo *philo);
void			philo_check(t_data *data);

unsigned int	ft_uatoi(const char *str);
int				ft_strlen(const char *str);
void			print_struct(t_data *data);
int				freeall(t_data *data);
long long		cur_time(struct timeval *start);
void			accurate_usleep(unsigned int ms, t_philo *philo);
long long		timestamp(struct timeval time);

#endif