/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpeinado <victor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:59:01 by vpeinado          #+#    #+#             */
/*   Updated: 2024/02/11 20:47:08 by vpeinado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <stdbool.h>
# include <time.h>
# include <sys/time.h>

typedef struct s_philosofer
{
    int						philo_id;
	int						times_eat;
	time_t				    last_meal_time;
	pthread_t				philo;
	pthread_mutex_t			*left_fork; //mutex to take the left fork
	pthread_mutex_t			*right_fork; //mutex to take the right fork
	pthread_mutex_t			check_alive; //mutex to check if the philo is alive
	struct s_data			*data;
} t_philosofer;

typedef struct s_data // data struct
{
    int					n_philo; //number of philos
	int					time_die;
	int					time_eat;
	int					time_sleep;
	int					times_must_eat;
	int					dead;
	int					satisfied;
	time_t			    time_start;
	t_philosofer		*all_philos;
	pthread_mutex_t		m_writing; //mutex to print
	pthread_mutex_t		m_control; //mutex to verify if the philo is alive
	pthread_mutex_t		*forks; //mutex to take the forks
	pthread_t			supervise; //thread to supervise the philos
}               t_data;


/* PARSE */
int parse_and_init(int argc, char **argv, t_data *data);

/*  utils*/
int	ft_atoi(const char *str);
time_t	ft_time_ms(void);   

/* threads and mutex init */
void forks_init(t_data *data);
void philos_init(t_data *data);
void thread_init(t_data *data);
void threads_join(t_data *data);
void clean(t_data *data);

/* philos routine */
void *philo_routine(void *philo);
void write_msg(t_philosofer *philo, char *msg);
int take_forks(t_philosofer *philo);
int eating(t_philosofer *philo);
int sleeping(t_philosofer *philo);
int thinking(t_philosofer *philo);
void *check_philos(void *data);

#endif