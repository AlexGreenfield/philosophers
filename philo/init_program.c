/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 00:11:03 by alejandro         #+#    #+#             */
/*   Updated: 2025/04/08 00:15:10 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Initializes all the program struct
int	init_program(char **argv, t_program *program)
{
	if (init_program_data(argv, program) != SUCCESS)
		return (THREAD_ERROR);
	if (init_philos_array(program) != SUCCESS)
		return (MALLOC_ERROR);
	if (init_philos_data(program) != SUCCESS)
		return (MALLOC_ERROR);
	if (mtx_init_meals(program) != SUCCESS)
		return (THREAD_ERROR);
	if (init_sticks(program) != SUCCESS)
		return (THREAD_ERROR);
	assign_sticks(program);
	return (SUCCESS);
}

// Inits argv data and mutex structs
int	init_program_data(char **argv, t_program *program)
{
	program->number_philo = ft_atoi(argv[1]);
	program->time_die = ft_atoi(argv[2]);
	usleep(10000);
	program->time_eat = ft_atoi(argv[3]);
	program->time_sleep = ft_atoi(argv[4]);
	if (argv[5] != NULL)
		program->number_eat = ft_atoi(argv[5]);
	else
		program->number_eat = -1;
	program->philo_dead = 0;
	program->philo_eated = 0;
	if (pthread_mutex_init(&program->dead_lock, NULL) != SUCCESS)
		return (THREAD_ERROR);
	if (pthread_mutex_init(&program->eated_lock, NULL) != SUCCESS)
		return (THREAD_ERROR);
	if (pthread_mutex_init(&program->write_lock, NULL) != SUCCESS)
		return (THREAD_ERROR);
	return (SUCCESS);
}

// Init shared stick mutex
int	init_sticks(t_program *program)
{
	int	i;
	int	size;

	size = program->number_philo;
	program->stick_lock = malloc(sizeof(pthread_mutex_t) * size);
	if (!program->stick_lock)
		return (MALLOC_ERROR);
	i = 0;
	while (i < program->number_philo)
	{
		if (pthread_mutex_init(&program->stick_lock[i], NULL) != SUCCESS)
			return (THREAD_ERROR);
		i++;
	}
	return (SUCCESS);
}
