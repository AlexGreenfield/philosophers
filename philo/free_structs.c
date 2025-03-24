/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastrov <acastrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:42:41 by acastrov          #+#    #+#             */
/*   Updated: 2025/03/24 19:20:56 by acastrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	free_structs(t_program *program, int flag)
{
	int	i;

	i = 0;
	if (program)
	{
		if (program->philo_array)
		{
			while (i < program->number_philo)
			{
				free(program->philo_array[i]);
				i++;
			}
			free(program->philo_array);
			program->philo_array = NULL;
		}
		free (program);
	}
	return (flag);
}
