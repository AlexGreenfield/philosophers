/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philos_eat.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:11:15 by alejandro         #+#    #+#             */
/*   Updated: 2025/04/08 00:15:25 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	pthread_mutex_t	*first_stick;
	pthread_mutex_t	*second_stick;

	if (philo->philo_id % 2 != 0)
	{
		first_stick = philo->r_stick;
		second_stick = philo->l_stick;
	}
	else
	{
		first_stick = philo->l_stick;
		second_stick = philo->r_stick;
	}
	if (pick_f_stick(philo, first_stick) != SUCCESS)
		return ;
	if (pick_s_stick(philo, first_stick, second_stick) != SUCCESS)
		return ;
	if (start_eating(philo, first_stick, second_stick) != SUCCESS)
		return ;
}

int	pick_f_stick(t_philo *philo, pthread_mutex_t *f_s)
{
	if (waiter_allows(philo))
		pthread_mutex_lock(f_s);
	else
		return (1);
	if (waiter_allows(philo))
		print_message("has taken a fork", philo);
	else
	{
		pthread_mutex_unlock(f_s);
		return (1);
	}
	if (philo->number_philo == 1)
	{
		usleep(philo->time_die * 1000);
		pthread_mutex_unlock(f_s);
		return (1);
	}
	return (SUCCESS);
}

int	pick_s_stick(t_philo *philo, pthread_mutex_t *f_s, pthread_mutex_t *s_s)
{
	if (waiter_allows(philo))
		pthread_mutex_lock(s_s);
	else
	{
		pthread_mutex_unlock(f_s);
		return (1);
	}
	if (waiter_allows(philo))
		print_message("has taken a fork", philo);
	else
	{
		pthread_mutex_unlock(s_s);
		pthread_mutex_unlock(f_s);
		return (1);
	}
	return (SUCCESS);
}

int	start_eating(t_philo *philo, pthread_mutex_t *f_s, pthread_mutex_t *s_s)
{
	uint64_t	current_time;

	current_time = miliseconds_time();
	if (waiter_allows(philo))
		pthread_mutex_lock(&philo->meal_lock);
	else
	{
		pthread_mutex_unlock(s_s);
		pthread_mutex_unlock(f_s);
		return (1);
	}
	if (waiter_allows(philo))
	{
		philo->last_meal_time = miliseconds_time();
		current_time = miliseconds_time();
		philo->number_eaten++;
		pthread_mutex_unlock(&philo->meal_lock);
		print_message("is eating", philo);
		eat_time(philo, current_time);
	}
	pthread_mutex_unlock(s_s);
	pthread_mutex_unlock(f_s);
	return (SUCCESS);
}

void	eat_time(t_philo *philo, uint64_t current_time)
{
	while (current_time - philo->last_meal_time < philo->time_eat)
	{
		current_time = miliseconds_time();
		if (!waiter_allows(philo))
			break ;
		usleep(100);
	}
}
