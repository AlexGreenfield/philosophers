/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastrov <acastrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:08:30 by acastrov          #+#    #+#             */
/*   Updated: 2025/03/24 20:29:55 by acastrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Checks for dead philo or number of meals
void	waiter(t_program *program)
{
	int	i;

	while(1)
	{
		i = 0;
		while (i < program->number_philo)
		{
			if (program->philo_array[i]->dead == 1)
				break ;
			if (program->philo_array[i]->number_eaten == program->number_eat)
				break;
			i++;
		}
	}
}
