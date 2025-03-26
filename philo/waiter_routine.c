/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastrov <acastrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:08:30 by acastrov          #+#    #+#             */
/*   Updated: 2025/03/26 20:17:45 by acastrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Checks for dead philo or number of meals
void	*waiter_routine(void *param)
{
	int			i;
	t_philo		**philo_array;

	philo_array = param;
	while (1)
	{
		i = 0;
		while (i < 5) // change for number of philo
		{
			pthread_mutex_lock(philo_array[i]->dead_lock);
			if (philo_array[i]->dead == 1)
			{
				pthread_mutex_lock(philo_array[i]->write_lock);
				printf("Philo %d has exploded\n",
					philo_array[i]->philo_id);
				pthread_mutex_unlock(philo_array[i]->write_lock);
			}
			pthread_mutex_unlock(philo_array[i]->dead_lock);
			pthread_mutex_lock(philo_array[i]->meal_lock);
			if (philo_array[i]->number_eaten == 5)
			{

				pthread_mutex_lock(philo_array[i]->write_lock);
				printf("Philo %d has exploded\n",
					philo_array[i]->philo_id);
				pthread_mutex_unlock(philo_array[i]->write_lock);
			}
			pthread_mutex_unlock(philo_array[i]->meal_lock);
			i++;
		}
	}
	return (param);
}
