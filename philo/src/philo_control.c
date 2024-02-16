/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpeinado <victor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:32:11 by vpeinado          #+#    #+#             */
/*   Updated: 2024/02/16 21:44:29 by vpeinado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	kill_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->finish_mutex);
	philo->data->finish_flag = 1;
	pthread_mutex_unlock(&philo->data->finish_mutex);
}

int	finish_question(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->finish_mutex);
	if (philo->data->finish_flag)
	{
		pthread_mutex_unlock(&philo->data->finish_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->finish_mutex);
	return (0);
}

int	is_someone_dead_or_full(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->eat_mutex);
	if (ft_time_ms() - philo->last_eat >= philo->data->time_to_die)
	{
		print_action(philo, DIE);
		kill_philo(philo);
		pthread_mutex_unlock(&philo->data->eat_mutex);
		return (1);
	}
	else if (philo->data->must_eat_times > 0
		&& philo->eat_count >= philo->data->must_eat_times)
	{
		philo->data->philos_satisfied++;
		if (philo->data->philos_satisfied >= philo->data->nbr_philos)
		{
			kill_philo(philo);
			print_action(philo, FINISH);
			pthread_mutex_unlock(&philo->data->eat_mutex);
			return (1);
		}
	}
	pthread_mutex_unlock(&philo->data->eat_mutex);
	return (0);
}

void	finish_dinner(t_data *data)
{
	int	i;

	i = 0;
	while (i++ < data->nbr_philos)
		pthread_mutex_destroy(&data->fork_mutex[i]);
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->eat_mutex);
	pthread_mutex_destroy(&data->finish_mutex);
	free (data->philo);
	free (data->fork_mutex);
}

void	control_dinner(t_data *data)
{
	int	i;
	int	continue_flag;

	continue_flag = 1;
	while (continue_flag)
	{	
		i = 0;
		data->philos_satisfied = 0;
		while (i < data->nbr_philos)
		{
			if (continue_flag
				&& is_someone_dead_or_full(&data->philo[i]))
				continue_flag = 0;
			i++;
		}
		usleep(20);
	}
	i = 0;
	while (i < data->nbr_philos)
	{
		pthread_join(data->philo[i].thread, NULL);
		i++;
	}
}
