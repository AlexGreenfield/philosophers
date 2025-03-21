/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:42:14 by alejandro         #+#    #+#             */
/*   Updated: 2025/03/21 19:52:30 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		printf("INVALID ARGS NUMBER\n");
		return (FILE_ERROR);
	}
	if (bad_args(argv) != SUCCESS)
	{
		printf("INVALID ARGS FORMAT\n");
		return (FILE_ERROR);
	}
	if (init_philo(argv) != SUCCESS)
		return (THREAD_ERROR);
	return (SUCCESS);
}

int	init_philo(char **argv)
{

	return (SUCCESS);
}
