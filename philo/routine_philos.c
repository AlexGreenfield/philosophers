/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastrov <acastrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 21:24:59 by alejandro         #+#    #+#             */
/*   Updated: 2025/04/01 20:20:41 by acastrov         ###   ########.fr       */
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
		usleep(10000);
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
	//print_message("finished routine", philo);
	return (param);
}

// Eat routine
void	eat(t_philo *philo)
{
	uint64_t	current_time;

	pthread_mutex_lock(&philo->r_stick);
	print_message("has taken a fork", philo);
	pthread_mutex_lock(&philo->l_stick);
	print_message("has taken a fork", philo);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal_time = miliseconds_time();
	current_time = miliseconds_time();
	philo->number_eaten++;
	print_message("is eating", philo);
	//printf("Philo %d updated last_meal_time to %lu\n", philo->philo_id, philo->last_meal_time);
	pthread_mutex_unlock(&philo->r_stick);
	pthread_mutex_unlock(&philo->l_stick);
	pthread_mutex_unlock(philo->meal_lock);
	while (current_time - philo->last_meal_time < philo->time_eat)
	{
		current_time = miliseconds_time();
		if (!waiter_allows(philo))
			break ;
		usleep(1000);
	}
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
		usleep(1000);
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
