/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:55:13 by alejandro         #+#    #+#             */
/*   Updated: 2025/04/05 19:36:18 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Prints philo status message with write lock
void	print_message(char *str, t_philo *philo)
{
	uint64_t	current_time;

	pthread_mutex_lock(philo->write_lock);
	current_time = miliseconds_time() - philo->start_time;
	printf("%lu %d %s\n", current_time, philo->philo_id, str);
	pthread_mutex_unlock(philo->write_lock);
}

// Gets EPOCH time in miniseconds, uses uint64_t
uint64_t	miliseconds_time(void)
{
	struct timeval	current_time;
	uint64_t		miliseconds;

	if (gettimeofday(&current_time, NULL) == -1)
		return (1);
	miliseconds = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (miliseconds);
}
