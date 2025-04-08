/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 21:24:59 by alejandro         #+#    #+#             */
/*   Updated: 2025/04/08 20:02:58 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// All eat, sleep think routine loop while waiter allows
void	*philo_routine(void *param)
{
	int		i;
	t_philo	*philo;

	philo = (t_philo *)param;
	philo->start_time = miliseconds_time();
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal_time = miliseconds_time();
	pthread_mutex_unlock(&philo->meal_lock);
	i = 0;
	while (waiter_allows(philo))
	{
		if (waiter_allows(philo))
			eat(philo);
		if (waiter_allows(philo))
			sleepy(philo);
		if (waiter_allows(philo))
			think(philo);
		i++;
	}
	return (param);
}

// Sleep routine
void	sleepy(t_philo *philo)
{
	uint64_t	current_time;

	print_message("is sleeping", philo);
	philo->last_sleep_time = miliseconds_time();
	current_time = miliseconds_time();
	while (current_time - philo->last_sleep_time < philo->time_sleep)
	{
		current_time = miliseconds_time();
		if (!waiter_allows(philo))
			break ;
		usleep(100);
	}
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
	pthread_mutex_lock(philo->eated_lock);
	if (*philo->philo_eated == 1)
		flag = 1;
	pthread_mutex_unlock(philo->eated_lock);
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->philo_dead == 1)
		flag = 1;
	pthread_mutex_unlock(philo->dead_lock);
	if (flag == 1)
		return (SUCCESS);
	return (1);
}
