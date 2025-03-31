/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_waiter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:08:30 by acastrov          #+#    #+#             */
/*   Updated: 2025/03/31 21:44:06 by alejandro        ###   ########.fr       */
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
		usleep(1);
		if ((dead_philo(program) == SUCCESS))
			break ;
		if ((program->number_eat >= 0 && all_eated(program) == SUCCESS))
			break ;
		i++;
	}
	pthread_mutex_lock(&program->write_lock);
	//printf("\nWaiter finished routine\n\n");
	pthread_mutex_unlock(&program->write_lock);
	return (param);
}

// Checks if any philo died
int	dead_philo(t_program *program)
{
	int			i;
	int			dead;
	uint64_t	starved;

	i = 0;
	dead = 0;
	while (i < program->number_philo)
	{
		pthread_mutex_lock(&program->meal_lock);
		starved = miliseconds_time() - program->philo_array[i]->last_meal_time;
		pthread_mutex_unlock(&program->meal_lock);
		//printf("%d starved time is %lu\n", i, starved);
		if (starved > program->time_die)
		{
			pthread_mutex_lock(&program->dead_lock);
			program->philo_dead = 1;
			pthread_mutex_unlock(&program->dead_lock);
			print_message("died", program->philo_array[i]);
			dead = 1;
			break ;
		}
		i++;
	}
	if (dead == 1)
		return (SUCCESS);
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
		pthread_mutex_lock(&program->meal_lock);
		if (program->philo_array[i]->number_eaten == program->number_eat)
			eated++;
		pthread_mutex_unlock(&program->meal_lock);
		i++;
	}
	if (eated == program->number_philo)
	{
		pthread_mutex_lock(&program->meal_lock);
		program->philo_eated = 1;
		pthread_mutex_unlock(&program->meal_lock);
		pthread_mutex_lock(&program->write_lock);
		printf("\nAll eated\n");
		pthread_mutex_unlock(&program->write_lock);
		return (SUCCESS);
	}
	return (1);
}
