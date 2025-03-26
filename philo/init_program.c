/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastrov <acastrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:25:08 by acastrov          #+#    #+#             */
/*   Updated: 2025/03/26 20:35:59 by acastrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Initializes program struct
int	init_program(char **argv, t_program *program)
{
	if (init_program_data(argv, program) != SUCCESS)
		return (THREAD_ERROR);
	if (init_philos_array(program) != SUCCESS)
		return (MALLOC_ERROR);
	if (init_philos_data(program) != SUCCESS)
		return (MALLOC_ERROR);
	return (SUCCESS);
}

// Inits argv data and mutex structs
int	init_program_data(char **argv, t_program *program)
{
	program->number_philo = ft_atoi(argv[1]);
	program->time_die = ft_atoi(argv[2]);
	program->time_eat = ft_atoi(argv[3]);
	program->time_sleep = ft_atoi(argv[4]);
	if (argv[5] != NULL)
		program->number_eat = ft_atoi(argv[5]);
	else
		program->number_eat = -1;
	if (pthread_mutex_init(&program->dead_lock, NULL) != SUCCESS)
		return (THREAD_ERROR);
	if (pthread_mutex_init(&program->meal_lock, NULL) != SUCCESS)
		return (THREAD_ERROR);
	if (pthread_mutex_init(&program->write_lock, NULL) != SUCCESS)
		return (THREAD_ERROR);
	return (SUCCESS);
}

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

int	init_philos_data(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->number_philo)
	{
		program->philo_array[i]->philo_id = i;
		program->philo_array[i]->dead = 0;
		program->philo_array[i]->number_eaten = 0;
		program->philo_array[i]->dead_lock = &program->dead_lock;
		program->philo_array[i]->meal_lock = &program->meal_lock;
		program->philo_array[i]->write_lock = &program->write_lock;
		i++;
	}
	return (SUCCESS);
}
