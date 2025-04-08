/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:42:41 by acastrov          #+#    #+#             */
/*   Updated: 2025/04/08 19:36:07 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Frees program struct and philo array inside
int	free_structs(t_program *program, int flag)
{
	if (program)
	{
		if (free_philo_array(program) != SUCCESS)
			return (THREAD_ERROR);
		if (free_mutex_sticks(program) != SUCCESS)
			return (THREAD_ERROR);
		if (free_mutex_dead_write(program) != SUCCESS)
			return (THREAD_ERROR);
		free (program);
	}
	return (flag);
}

// Frees philo array and meal lock mutex
int	free_philo_array(t_program *program)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	if (program->philo_array)
	{
		while (i < program->number_philo)
		{
			if (pthread_mutex_destroy(&program->philo_array[i]->meal_lock)
				!= SUCCESS)
			{
				printf("Error freeing meal mutex philo %d\n", i);
				flag = 1;
			}
			free(program->philo_array[i]);
			i++;
		}
		free(program->philo_array);
		program->philo_array = NULL;
	}
	if (flag == 1)
		return (THREAD_ERROR);
	return (SUCCESS);
}

// Frees program sticks
int	free_mutex_sticks(t_program *program)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	if (program->stick_lock)
	{
		while (i < program->number_philo)
		{
			if (pthread_mutex_destroy(&program->stick_lock[i]) != SUCCESS)
			{
				flag = 1;
				printf("Error destroying stick %d\n", i);
			}
			i++;
		}
		free(program->stick_lock);
		program->stick_lock = NULL;
	}
	if (flag == 1)
		return (THREAD_ERROR);
	return (SUCCESS);
}

// Frees program dead write mutex
int	free_mutex_dead_write(t_program *program)
{
	int	flag;

	flag = 0;
	if (pthread_mutex_destroy(&program->dead_lock) != SUCCESS)
	{
		printf("Error freeing dead mutex\n");
		flag = 1;
	}
	if (pthread_mutex_destroy(&program->write_lock) != SUCCESS)
	{
		printf("Error freeing write mutex\n");
		flag = 1;
	}
	if (flag == 1)
		return (THREAD_ERROR);
	return (SUCCESS);
}
