/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastrov <acastrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 21:24:59 by alejandro         #+#    #+#             */
/*   Updated: 2025/03/28 17:28:12 by acastrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *param)
{
	int		i;
	t_philo	*philo;

	philo = (t_philo *)param;
	if (philo->philo_id % 2 != 0)
		usleep(1);
	i = 0;
	while (i < 6)
	{
		eat(philo);
		sleepy(philo);
		think(philo);
		i++;
	}
	print_message("finished routine", philo);
	return (param);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->meal_lock);
	philo->number_eaten++;
	print_message("is eating", philo);
	pthread_mutex_unlock(philo->meal_lock);
	usleep(1000000);
}

void	sleepy(t_philo *philo)
{
	print_message("is sleeping", philo);
	usleep(200);
}

void	think(t_philo *philo)
{
	print_message("is thinking", philo);
}

void	print_message(char *str, t_philo *philo)
{
	pthread_mutex_lock(philo->write_lock);
	printf("%d %s\n", philo->philo_id, str);
	pthread_mutex_unlock(philo->write_lock);
}

int	waiter_allows(t_philo *philo)
{
	int	flag;

	flag = 0;
	pthread_mutex_lock(philo->meal_lock); // Doesnt leave lock
	if (philo->philo_eated)
		flag = 1;
	pthread_mutex_unlock(philo->meal_lock);
	pthread_mutex_lock(philo->dead_lock); // Doesnt leave lock
	if (philo->philo_dead)
		flag = 1;
	pthread_mutex_unlock(philo->dead_lock);
	if (flag == 1)
		return (1);
	return(0);
}
