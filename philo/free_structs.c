/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastrov <acastrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:42:41 by acastrov          #+#    #+#             */
/*   Updated: 2025/03/26 20:38:42 by acastrov         ###   ########.fr       */
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
		if (program->philo_array)
		{
			while (i < program->number_philo)
			{
				free(program->philo_array[i]);
				i++;
			}
			free(program->philo_array);
			program->philo_array = NULL;
		}
		if (pthread_mutex_destroy(&program->dead_lock) != SUCCESS)
			printf("Error freeing dead mutex\n");
		if (pthread_mutex_destroy(&program->meal_lock) != SUCCESS)
			printf("Error freeing meal mutex\n");
		if (pthread_mutex_destroy(&program->write_lock) != SUCCESS)
			printf("Error freeing write mutex\n");
		free (program);
	}
	return (flag);
}
