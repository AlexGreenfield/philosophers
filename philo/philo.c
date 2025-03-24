/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastrov <acastrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:42:14 by alejandro         #+#    #+#             */
/*   Updated: 2025/03/24 19:12:21 by acastrov         ###   ########.fr       */
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

// Inits main philo proccess
int	init_philo(char **argv)
{
	t_program	*program;

	program = malloc(sizeof(t_program));
	if (!program)
		return (MALLOC_ERROR);
	if (init_program(argv, program) != SUCCESS)
		return (free_structs(program, MALLOC_ERROR));
	return (free_structs(program, SUCCESS));
}
