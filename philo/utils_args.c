/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:53:15 by alejandro         #+#    #+#             */
/*   Updated: 2025/04/05 19:36:15 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Takes a const char, manages spaces and symbols and returns an int
uint64_t	ft_atoi(const char *nptr)
{
	uint64_t	result;

	result = 0;
	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '-')
		nptr++;
	else if (*nptr == '+')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		result = (result * 10) + (*nptr - '0');
		nptr++;
	}
	return (result);
}

// Checks if a char(ASCII value) digit
int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (SUCCESS);
	return (FILE_ERROR);
}
