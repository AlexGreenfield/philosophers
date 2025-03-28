/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastrov <acastrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:08:30 by acastrov          #+#    #+#             */
/*   Updated: 2025/03/28 17:28:42 by acastrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Checks for dead philo or number of meals

void	*waiter_routine(void *param)
{
	t_program	*program;
	int			i;

	i = 0;
	program = param;
	while (1)
	{
		usleep(200); // Same as time sleeping, for reference
		if ((dead_philo(program) == SUCCESS) || (all_eated(program) == SUCCESS))
			break ;
		i++;
	}
	printf("Waiter finished routine\n\n");
	return (param);
}

int	dead_philo(t_program *program)
{
	int	i;
	int	dead;

	i = 0;
	dead = 0;
	while (i < 5)
	{
		pthread_mutex_lock(&program->dead_lock);
		if (program->philo_array[i]->dead)
			dead = 1;
		pthread_mutex_unlock(&program->dead_lock);
		i++;
	}
	if (dead == 1)
	{
		print_message("%d is dead\n", program->philo_array[i]);
		return (SUCCESS);
	}
	return (1);
}

int	all_eated(t_program *program) // We should pass program
{
	int	i;
	int	eated;

	i = 0;
	eated = 0;
	while (i < program->number_philo)
	{
		pthread_mutex_lock(&program->meal_lock); // All philo increase their meals...
		if (program->philo_array[i]->number_eaten == program->number_eat)
			eated++;
		pthread_mutex_unlock(&program->meal_lock);
		i++;
	}
	if (eated == program->number_philo)
	{
		pthread_mutex_lock(&program->meal_lock); // But this flag is never reached
		program->philo_eated = 1;
		pthread_mutex_unlock(&program->meal_lock);
		printf("All eated\n");
		return (SUCCESS);
	}
	return (1);
}
