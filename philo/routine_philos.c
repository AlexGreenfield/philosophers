/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 21:24:59 by alejandro         #+#    #+#             */
/*   Updated: 2025/03/31 21:42:23 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// All eat, sleep think routine loop while waiter allows
void	*philo_routine(void *param)
{
	int		i;
	t_philo	*philo;

	philo = (t_philo *)param;
	if (philo->philo_id % 2 != 0)
		usleep(1);
	i = 0;
	while (waiter_allows(philo))
	{
		eat(philo);
		sleepy(philo);
		think(philo);
		i++;
	}
	print_message("finished routine", philo);
	return (param);
}

// Eat routine
void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal_time = miliseconds_time();
	philo->number_eaten++;
	print_message("is eating", philo);
	//printf("Philo %d updated last_meal_time to %lu\n", philo->philo_id, philo->last_meal_time);
	pthread_mutex_unlock(philo->meal_lock);
	usleep(philo->time_eat * 1000);
}

// Sleep routine
void	sleepy(t_philo *philo)
{
	print_message("is sleeping", philo);
	usleep(philo->time_sleep * 1000);
}

// Think Routine
void	think(t_philo *philo)
{
	print_message("is thinking", philo);
}

// Waiter allows routine while no philo dead or all eated
int	waiter_allows(t_philo *philo)
{
	int	flag;

	flag = 0;
	pthread_mutex_lock(philo->meal_lock);
	if (*philo->philo_eated == 1)
		flag = 1;
	pthread_mutex_unlock(philo->meal_lock);
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->philo_dead == 1)
		flag = 1;
	pthread_mutex_unlock(philo->dead_lock);
	if (flag == 1)
		return (0);
	return (1);
}
