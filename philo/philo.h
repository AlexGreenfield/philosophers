/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:45:02 by alejandro         #+#    #+#             */
/*   Updated: 2025/04/03 18:01:07 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

// System libraries
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdint.h>
# include <sys/time.h>

// Macros error
# define SUCCESS 0
# define MALLOC_ERROR -1
# define THREAD_ERROR -2
# define FILE_ERROR -3
# define TIME_ERROR -4

// Philo structs
typedef struct s_philo
{
	pthread_t		philo_thread;
	int				philo_id;
	int				dead;
	int				number_eat;
	int				number_eaten;
	int				number_philo;
	int				*philo_dead;
	int				*philo_eated;
	uint64_t		time_die;
	uint64_t		time_eat;
	uint16_t		time_sleep;
	uint64_t		start_time;
	uint64_t		last_meal_time;
	uint64_t		last_sleep_time;
	pthread_mutex_t	*r_stick;
	pthread_mutex_t	*l_stick;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
	pthread_mutex_t	*write_lock;
}	t_philo;

// Program struct
typedef struct s_program
{
	int				number_eat;
	int				philo_dead;
	int				philo_eated;
	int				number_philo;
	uint64_t		time_die;
	uint64_t		time_eat;
	uint16_t		time_sleep;
	uint64_t		start_time;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	*stick_lock;
	pthread_t		waiter;
	t_philo			**philo_array;
}	t_program;

// Main
int			init_philo(char **argv);

// Check args

int			bad_args(char **argv);
int			argv_digits(char **argv);
int			argv_zero(char **argv);

// Args utils
uint64_t	ft_atoi(const char *nptr);
int			ft_isdigit(int c);

// Routine utils
void		print_message(char *str, t_philo *philo);
uint64_t	miliseconds_time(void);

// Init philo

int			init_program_data(char **argv, t_program *program);
int			init_program(char **argv, t_program *program);
int			init_philos_array(t_program *program);
int			init_philos_data(t_program *program);
int			init_sticks(t_program *program);
int			assign_sticks(t_program *program);

// Routines

int			init_routines(t_program *program);
int			launch_threads(t_program *program);
int			join_threads(t_program *program);

// Philo routine

void		*philo_routine(void *param);
void		eat(t_philo *philo);
void		sleepy(t_philo *philo);
void		think(t_philo *philo);
int			waiter_allows(t_philo *philo);

// Waiter routine

void		*waiter_routine(void *param);
int			dead_philo(t_program *program);
int			all_eated(t_program *program);

// Free

int			free_structs(t_program *program, int flag);

#endif
