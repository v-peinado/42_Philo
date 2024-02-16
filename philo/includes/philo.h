/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpeinado <victor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:59:01 by vpeinado          #+#    #+#             */
/*   Updated: 2024/02/16 21:39:34 by vpeinado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <string.h>
# include <time.h>
# include <sys/time.h>

# define TAKE "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIE "died"
# define FINISH "finished eating"
# define FIN_MSG "All philosophers ate!"
# define YES 1
# define NO 0

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	int				eat_count;
	int				l_fork;
	int				r_fork;
	time_t			last_eat;
	t_data			*data;
	pthread_t		thread;
}	t_philo;

typedef struct s_data
{
	int				nbr_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_times;
	int				philos_satisfied;
	int				finish_flag;
	time_t			start_time;
	t_philo			*philo;
	pthread_mutex_t	*fork_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	eat_mutex;
	pthread_mutex_t	finish_mutex;
}	t_data;	

/* PARSE */
int		parse_input(int argc, char **argv, t_data *data);

/* PHILOSOPHERS */
void	init_philosophers(t_data *data);
void	init_threads_and_mutex(t_data *data);

/* ROUTINE */
void	*philo_routine(void *philo);
void	print_action(t_philo *philo, char *action);

/* UTILS */
int		ft_atoi(const char *str);
time_t	ft_time_ms(void);
void	ft_usleep(t_philo *philo, time_t stop);

/* CONTROL */
void	control_dinner(t_data *data);
int		finish_question(t_philo *philo);
void	kill_philo(t_philo *philo);
void	finish_dinner(t_data *data);

#endif