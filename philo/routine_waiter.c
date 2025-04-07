/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_waiter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:08:30 by acastrov          #+#    #+#             */
/*   Updated: 2025/04/07 17:58:54 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Checks for dead philo and number of meals
void	*waiter_routine(void *param)
{
	t_program	*program;
	int			i;

	i = 0;
	program = param;
	while (1)
	{
		usleep(100);
		if ((dead_philo(program) == SUCCESS))
			break ;
		if ((program->number_eat >= 0 && all_eated(program) == SUCCESS))
			break ;
		i++;
	}
	return (param);
}

// Checks if any philo died
int	dead_philo(t_program *program)
{
	int			i;
	uint64_t	starved;

	i = 0;
	while (i < program->number_philo)
	{
		pthread_mutex_lock(&program->philo_array[i]->meal_lock);
		if (program->philo_array[i]->last_meal_time == 0)
			starved = 0 ;
		else
			starved = miliseconds_time() - program->philo_array[i]->last_meal_time;
		pthread_mutex_unlock(&program->philo_array[i]->meal_lock);
		if (starved > program->time_die)
		{
			pthread_mutex_lock(&program->dead_lock);
			program->philo_dead = 1;
			print_message("died", program->philo_array[i]);
			pthread_mutex_unlock(&program->dead_lock);
			return (SUCCESS);
		}
		i++;
	} 
	return (1); 
}

// Checks if all philo have eated
int	all_eated(t_program *program)
{
	int	i;
	int	eated;

	i = 0;
	eated = 0;
	while (i < program->number_philo)
	{
		pthread_mutex_lock(&program->philo_array[i]->meal_lock);
		if (program->philo_array[i]->number_eaten >= program->number_eat)
			eated++;
		pthread_mutex_unlock(&program->philo_array[i]->meal_lock);
		i++;
	}
	if (eated >= program->number_philo)
	{
		pthread_mutex_lock(&program->eated_lock);
		program->philo_eated = 1;
		pthread_mutex_unlock(&program->eated_lock);
		return (SUCCESS);
	}
	return (1);
}
