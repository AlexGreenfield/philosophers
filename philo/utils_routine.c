/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastrov <acastrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:55:13 by alejandro         #+#    #+#             */
/*   Updated: 2025/04/10 18:59:34 by acastrov         ###   ########.fr       */
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

void	assing_start_time(t_program *program)
{
	int	i;

	i = 0;
	program->start_time = miliseconds_time();
	while (i < program->number_philo)
	{
		program->philo_array[i]->start_time = program->start_time;
		i++;
	}
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
