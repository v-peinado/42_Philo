/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpeinado <victor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:59:01 by vpeinado          #+#    #+#             */
/*   Updated: 2024/02/18 00:19:25 by vpeinado         ###   ########.fr       */
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

# define TAKE "\033[1;36mhas taken a fork\033[0;0m"
# define EAT "\033[1;35mis eating\033[0;0m"
# define SLEEP "\033[1;33mis sleeping\033[0;0m"
# define THINK "\033[1;30mis thinking\033[0;0m"
# define DIE "\033[1;31mdied\033[0;0m"
# define FINISH "finished eating"
# define FIN_MSG "\033[1;32mAll philosophers ate!\033[0;0m\n"
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
void	join_philosophers(t_data *data);
void	write_msg(t_philo *philo, char *action);

/* UTILS */
int		ft_atoi(const char *str);
time_t	ft_time_ms(void);
void	ft_usleep(t_philo *philo, time_t stop);

/* CONTROL */
void	control_dinner(t_data *data);
int		finish_question(t_philo *philo);
void	end_philo(t_philo *philo);
void	finish_dinner(t_data *data);

#endif