/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_routines.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastrov <acastrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 19:34:51 by acastrov          #+#    #+#             */
/*   Updated: 2025/03/26 19:37:06 by acastrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Launches al philo threads
int	init_routines(t_program *program)
{
	int			i;
	pthread_t	waiter;
	t_philo		**philo_array;

	philo_array = program->philo_array;
	if (pthread_create(&waiter, NULL, waiter_routine, philo_array) != SUCCESS)
		return (THREAD_ERROR);
	i = 0;
	while (i < program->number_philo)
	{
		if (pthread_create(&philo_array[i]->philo_thread,
				NULL, philo_routine, philo_array[i]) != SUCCESS)
			return (THREAD_ERROR);
		i++;
	}
	if (pthread_join(waiter, NULL) != SUCCESS)
		return (THREAD_ERROR);
	i = 0;
	while (i < program->number_philo)
	{
		if (pthread_join(philo_array[i]->philo_thread, NULL) != SUCCESS)
			return (THREAD_ERROR);
		i++;
	}
	return (SUCCESS);
}
