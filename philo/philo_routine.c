/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 19:19:37 by acastrov          #+#    #+#             */
/*   Updated: 2025/03/27 17:11:29by alejandro        ###   ########.fr       */
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
	while (!philo->philo_dead || !philo->philo_eated)
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
	usleep(1000000);
	pthread_mutex_unlock(philo->meal_lock);
}

void	sleepy(t_philo *philo)
{
	//pthread_mutex_lock(philo->write_lock);
	//printf("Philo %d is sleeping\n", philo->philo_id);
	//pthread_mutex_unlock(philo->write_lock);
	print_message("is sleeping", philo);
	usleep(200);
}

void	think(t_philo *philo)
{
	//pthread_mutex_lock(philo->write_lock);
	//printf("Philo %d is thinking\n", philo->philo_id);
	//pthread_mutex_unlock(philo->write_lock);
	print_message("is thinking", philo);

}

void	print_message(char *str, t_philo *philo)
{
	pthread_mutex_lock(philo->write_lock);
	printf("%d %s\n", philo->philo_id, str);
	pthread_mutex_unlock(philo->write_lock);
}
