/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_routines.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastrov <acastrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 19:34:51 by acastrov          #+#    #+#             */
/*   Updated: 2025/03/24 20:29:49 by acastrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Small routine for testing
void	*routine(void *param)
{
	t_program	*program;

	program = (t_program *)param;
	printf("In thread, printing %d\n", program->number_philo);
	return (NULL);
}

// Launches al philo threads
int	init_routines(t_program *program)
{
	int			i;
	pthread_t	philo_id[program->number_philo]; // Change

	// Separate philos and launch them
	i = 0;
	while (i < program->number_philo)
	{
		if (pthread_create(&philo_id[i], NULL, routine, program) != SUCCESS)
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
		if (pthread_join(philo_id[i], NULL) != SUCCESS)
			return (THREAD_ERROR);
		i++;
	}
	return (SUCCESS);
}
