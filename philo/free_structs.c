/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:42:41 by acastrov          #+#    #+#             */
/*   Updated: 2025/04/05 20:00:27 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Frees program struct and philo array inside
int	free_structs(t_program *program, int flag)
{
	int	i;

	i = 0;
	if (program)
	{
		i = 0;
		if (program->philo_array)
		{
			while (i < program->number_philo)
			{
				if (pthread_mutex_destroy(&program->philo_array[i]->meal_lock) != SUCCESS)
					printf("Error freeing meal mutex philo %d\n", i);
				free(program->philo_array[i]);
				i++;
			}
			free(program->philo_array);
			program->philo_array = NULL;
		}
		if (program->stick_lock)
		{
			while (i < program->number_philo)
			{
				if (pthread_mutex_destroy(&program->stick_lock[i]) != SUCCESS)
					printf("Error destroying stick %d\n", i);
				i++;
			}
			free(program->stick_lock);
			program->stick_lock = NULL;
		}
		if (pthread_mutex_destroy(&program->dead_lock) != SUCCESS)
			printf("Error freeing dead mutex\n");
		//if (pthread_mutex_destroy(&program->meal_lock) != SUCCESS)
			//printf("Error freeing meal mutex\n");
		if (pthread_mutex_destroy(&program->write_lock) != SUCCESS)
			printf("Error freeing write mutex\n");
		free (program);
	}
	return (flag);
}
