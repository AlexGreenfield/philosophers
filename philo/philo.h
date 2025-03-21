/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:45:02 by alejandro         #+#    #+#             */
/*   Updated: 2025/03/21 19:21:40 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

// System libraries
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>

// Macros error
# define SUCCESS 0
# define MALLOC_ERROR -1
# define THREAD_ERROR -2
# define FILE_ERROR -3

// Check args
int				bad_args(char **argv);
int				argv_digits(char **argv);
int				argv_zero(char **argv);

// Args utils
long long int	ft_atoi(const char *nptr);
int				ft_isdigit(int c);

#endif