/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpeinado <victor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 23:32:32 by vpeinado          #+#    #+#             */
/*   Updated: 2024/02/16 21:43:58 by vpeinado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_threads_and_mutex(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->eat_mutex, NULL);
	pthread_mutex_init(&data->finish_mutex, NULL);
	while (i < data->nbr_philos)
	{
		pthread_mutex_init(&data->fork_mutex[i], NULL);
		i++;
	}
	i = 0;
	while (i < data->nbr_philos)
	{
		pthread_create(&data->philo[i].thread, NULL,
			philo_routine, &data->philo[i]);
		i++;
	}
}

/**
* This function will initialize the philosophers and the forks. It will also
* initialize the mutexes for the forks and the print padlock.
*
* @param data The data structure that contains the information of the dinner
*/
void	init_philosophers(t_data *data)
{
	int	i;

	i = 0;
	data->philo = malloc(sizeof(t_philo) * data->nbr_philos);
	data->fork_mutex = malloc(sizeof(pthread_mutex_t) * data->nbr_philos);
	if (!data->philo || !data->fork_mutex)
		return ;
	data->start_time = ft_time_ms();
	while (i < data->nbr_philos)
	{
		data->philo[i].id = i + 1;
		data->philo[i].l_fork = i;
		data->philo[i].r_fork = (i + 1) % data->nbr_philos;
		data->philo[i].eat_count = 0;
		data->philo[i].last_eat = data->start_time;
		data->philo[i].data = data;
		i++;
	}
}
