/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_routines.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 19:34:51 by acastrov          #+#    #+#             */
/*   Updated: 2025/03/25 20:07:38 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Small routine for testing
void	*routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	while (philo->number_eaten < 5 && !dead_philo(philo))
	{
		printf("In thread, philo %d has %d eats\n", philo->philo_id, philo->number_eaten);
		philo->number_eaten++;
		printf("In thread, philo %d has eated, now has %d eats\n", philo->philo_id, philo->number_eaten);
		usleep(2000000);
	}
	return (NULL);
}

// Launches al philo threads
int	init_routines(t_program *program)
{
	int			i;
	t_philo	**philo_array;

	philo_array = program->philo_array;
	i = 0;
	while (i < program->number_philo)
	{
		if (pthread_create(&philo_array[i]->philo_thread, NULL, routine, philo_array[i]) != SUCCESS)
			return (THREAD_ERROR);
		i++;
	}
	//i = 0;
	//while (i < program->number_philo)
	//{
		//if (pthread_detach(philo_id[i]) != SUCCESS)
			//return (THREAD_ERROR);
		//printf("Philo %d detached\n", i);
		//i++;
	//}
	usleep(500);
	//waiter(program);
	i = 0;
	while (i < program->number_philo)
	{
		if (pthread_join(philo_array[i]->philo_thread, NULL) != SUCCESS)
			return (THREAD_ERROR);
		i++;
	}
	return (SUCCESS);
}

int	dead_philo(t_philo *philo)
{
	printf("Philo %d its trying to mutex\n", philo->philo_id);
	pthread_mutex_lock(philo->dead_lock);
	printf("Philo %d has locked the mutex\n", philo->philo_id);
	if (philo->dead == 1)
		return (pthread_mutex_unlock(philo->dead_lock), 1);
	if (philo->number_eaten == 4)
	{
		printf("Philo %d has exploded\n", philo->philo_id);
		return (pthread_mutex_unlock(philo->dead_lock), 1);
	}
	usleep(5000000);
	return (pthread_mutex_unlock(philo->dead_lock), 0);
}
