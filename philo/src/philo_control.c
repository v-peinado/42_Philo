/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpeinado <vpeinado@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:32:11 by vpeinado          #+#    #+#             */
/*   Updated: 2024/03/16 12:30:40 by vpeinado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	end_philo(t_philo *philo)
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
		write_msg(philo, DIE);
		end_philo(philo);
		pthread_mutex_unlock(&philo->data->eat_mutex);
		return (1);
	}
	else if (philo->data->must_eat_times > 0
		&& philo->eat_count >= philo->data->must_eat_times)
	{
		philo->data->philos_satisfied++;
		if (philo->data->philos_satisfied >= philo->data->nbr_philos)
		{
			end_philo(philo);
			write_msg(philo, FINISH);
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
}
