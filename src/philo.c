/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschelti <sschelti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 15:20:37 by sschelti          #+#    #+#             */
/*   Updated: 2023/05/09 13:50:07 by sschelti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	eat(t_philo *philo)
{
    pthread_mutex_lock(philo->fork_l);
        printf("%ldms philo: %d has taken left fork.\n", calculate_timestamp(&philo->start_of_program), philo->philo_id);
    pthread_mutex_lock(philo->fork_r);
        printf("%ldms philo: %d has taken right fork.\n", calculate_timestamp(&philo->start_of_program), philo->philo_id);
    usleep(philo->data->time_to_eat);
    pthread_mutex_unlock(philo->fork_l);
    pthread_mutex_unlock(philo->fork_r);
}
