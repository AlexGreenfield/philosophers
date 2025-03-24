/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastrov <acastrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:53:15 by alejandro         #+#    #+#             */
/*   Updated: 2025/03/24 18:09:01 by acastrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Takes a const char, manages spaces and symbols and returns an int
int	ft_atoi(const char *nptr)
{
	int	symbol;
	int	result;

	symbol = 1;
	result = 0;
	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '-')
	{
		symbol = -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		result = (result * 10) + (*nptr - '0');
		nptr++;
	}
	return (result * symbol);
}

// Checks if a char(ASCII value) digit
int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (SUCCESS);
	return (FILE_ERROR);
}
