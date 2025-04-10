/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_routines.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastrov <acastrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 19:34:51 by acastrov          #+#    #+#             */
/*   Updated: 2025/04/10 19:13:45 by acastrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Launches and joins all threads
int	init_routines(t_program *program)
{
	if (launch_threads(program) != SUCCESS)
		return (THREAD_ERROR);
	if (join_threads(program) != SUCCESS)
		return (THREAD_ERROR);
	return (SUCCESS);
}

// Launches philo and waiter threads
int	launch_threads(t_program *program)
{
	int			i;
	t_philo		**philo_array;

	philo_array = program->philo_array;
	assing_start_time(program);
	if (pthread_create(&program->waiter, NULL,
			waiter_routine, program) != SUCCESS)
	{
		printf("Error creating waiter\n");
		return (THREAD_ERROR);
	}
	i = 0;
	while (i < program->number_philo)
	{
		if (pthread_create(&philo_array[i]->philo_thread,
				NULL, philo_routine, philo_array[i]) != SUCCESS)
		{
			printf("Error creating philo %d\n", i);
			return (THREAD_ERROR);
		}
		i++;
	}
	return (SUCCESS);
}

// Joins philo and waiter threads
int	join_threads(t_program *program)
{
	int			i;
	t_philo		**philo_array;

	philo_array = program->philo_array;
	if (pthread_join(program->waiter, NULL) != SUCCESS)
	{
		printf("Error joining waiter\n");
		return (THREAD_ERROR);
	}
	i = 0;
	while (i < program->number_philo)
	{
		if (pthread_join(philo_array[i]->philo_thread, NULL) != SUCCESS)
		{
			printf("Error philo %d\n", i);
			return (THREAD_ERROR);
		}
		i++;
	}
	return (SUCCESS);
}
