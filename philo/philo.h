/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:45:02 by alejandro         #+#    #+#             */
/*   Updated: 2025/03/27 21:24:37 by alejandro        ###   ########.fr       */
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

// Philo structs
typedef struct s_philo
{
	pthread_t		philo_thread;
	int				philo_id;
	int				dead;
	int				number_eat;
	int				number_eaten;
	int				*philo_dead; // Metodoly doubt
	int				*philo_eated;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
	pthread_mutex_t	*write_lock;
}	t_philo;

// Program struct
typedef struct s_program
{
	int				number_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				number_eat;
	int				philo_dead;
	int				philo_eated;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_philo			**philo_array;
}	t_program;

// Main
int		init_philo(char **argv);

// Check args

int		bad_args(char **argv);
int		argv_digits(char **argv);
int		argv_zero(char **argv);

// Args utils

int		ft_atoi(const char *nptr);
int		ft_isdigit(int c);

// Init philo

int		init_program_data(char **argv, t_program *program);
int		init_program(char **argv, t_program *program);
int		init_philos_array(t_program *program);
int		init_philos_data(t_program *program);

// Routines

int		init_routines(t_program *program);

// Philo routine

void	*philo_routine(void *param);
void	eat(t_philo *philo);
void	sleepy(t_philo *philo);
void	think(t_philo *philo);
void	print_message(char *str, t_philo *philo);

// Waiter routine

void	*waiter_routine(void *param);
int		dead_philo(t_program *program); // We should pass program
int		all_eated(t_program *program); // We should pass program

// Free

int		free_structs(t_program *program, int flag);

#endif
