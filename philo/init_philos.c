/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 00:13:23 by alejandro         #+#    #+#             */
/*   Updated: 2025/04/08 00:15:05 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Allocates array of philosophers inside program struct
int	init_philos_array(t_program *program)
{
	int			i;
	int			number_philo;

	number_philo = program->number_philo;
	program->philo_array = malloc(sizeof(t_philo *) * number_philo);
	if (!program->philo_array)
		return (MALLOC_ERROR);
	i = 0;
	while (i < program->number_philo)
	{
		program->philo_array[i] = malloc(sizeof(t_philo));
		if (!program->philo_array[i])
		{
			while (i > 0)
				free(program->philo_array[--i]);
			free(program->philo_array);
			return (MALLOC_ERROR);
		}
		i++;
	}
	return (SUCCESS);
}

// Init all philo data
int	init_philos_data(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->number_philo)
	{
		program->philo_array[i]->philo_id = i + 1;
		program->philo_array[i]->dead = 0;
		program->philo_array[i]->number_philo = program->number_philo;
		program->philo_array[i]->philo_dead = &program->philo_dead;
		program->philo_array[i]->number_eat = program->number_eat;
		program->philo_array[i]->number_eaten = 0;
		program->philo_array[i]->last_meal_time = 0;
		program->philo_array[i]->philo_eated = &program->philo_eated;
		program->philo_array[i]->time_die = program->time_die;
		program->philo_array[i]->time_eat = program->time_eat;
		program->philo_array[i]->time_sleep = program->time_sleep;
		program->philo_array[i]->dead_lock = &program->dead_lock;
		program->philo_array[i]->eated_lock = &program->eated_lock;
		program->philo_array[i]->write_lock = &program->write_lock;
		i++;
	}
	return (SUCCESS);
}

// Asssign R and L stick (n + 1 or 0 if n philo number)
int	assign_sticks(t_program *program)
{
	int		i;
	t_philo	**philo_array;

	i = 0;
	philo_array = program->philo_array;
	if (program->number_philo == 1)
	{
		philo_array[0]->r_stick = &program->stick_lock[0];
		return (SUCCESS);
	}
	while (i < program->number_philo)
	{
		philo_array[i]->r_stick = &program->stick_lock[i];
		i++;
	}
	i = 0;
	while (i < program->number_philo)
	{
		if (i == program->number_philo - 1)
			philo_array[i]->l_stick = &program->stick_lock[0];
		else
			philo_array[i]->l_stick = &program->stick_lock[i + 1];
		i++;
	}
	return (SUCCESS);
}

int	mtx_init_meals(t_program *program)
{
	int		i;
	t_philo	**philo_array;

	i = 0;
	philo_array = program->philo_array;
	while (i < program->number_philo)
	{
		if (pthread_mutex_init(&philo_array[i]->meal_lock, NULL) != SUCCESS)
			return (THREAD_ERROR);
		i++;
	}
	return (SUCCESS);
}
