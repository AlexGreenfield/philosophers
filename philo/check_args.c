/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:52:09 by alejandro         #+#    #+#             */
/*   Updated: 2025/03/21 19:33:15 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Checks if args are valid
int	bad_args(char **argv)
{
	if (argv_digits(argv) != SUCCESS)
		return (FILE_ERROR);
	if (argv_zero(argv) != SUCCESS)
		return (FILE_ERROR);
	return (SUCCESS);
}

// Checks if there's a non digit in argv
int	argv_digits(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (ft_isdigit((unsigned char)argv[i][j]))
				return (FILE_ERROR);
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

// Checks if any argument it's zero and philo n limit
int	argv_zero(char **argv)
{
	int	i;

	if (ft_atoi(argv[1]) > 200)
		return (FILE_ERROR);
	i = 1;
	while (argv[i])
	{
		if (ft_atoi(argv[i]) <= 0)
			return (FILE_ERROR);
		i++;
	}
	return (SUCCESS);
}
