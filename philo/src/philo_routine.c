/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpeinado <victor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 10:12:39 by vpeinado          #+#    #+#             */
/*   Updated: 2024/02/18 01:35:31 by vpeinado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_msg(t_philo *philo, char *status)
{
	time_t	time;

	pthread_mutex_lock(&philo->data->print_mutex);
	if (!finish_question(philo))
	{
		time = ft_time_ms() - philo->data->start_time;
		printf("%lu %d %s\n", time, philo->id, status);
	}
	pthread_mutex_unlock(&philo->data->print_mutex);
	if (status[0] == 'f')
		printf("%s\n", FIN_MSG);
}

void	one_philo(t_data *data)
{
	write_msg(&data->philo[0], TAKE);
	ft_usleep(&data->philo[0], data->time_to_die);
	write_msg(&data->philo[0], DIE);
	end_philo(&data->philo[0]);
}

void	time_to_eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->data->fork_mutex[philo->l_fork]);
		pthread_mutex_lock(&philo->data->fork_mutex[philo->r_fork]);
	}
	else
	{
		pthread_mutex_lock(&philo->data->fork_mutex[philo->r_fork]);
		pthread_mutex_lock(&philo->data->fork_mutex[philo->l_fork]);
	}
	write_msg(philo, TAKE);
	write_msg(philo, TAKE);
	write_msg(philo, EAT);
	ft_usleep(philo, philo->data->time_to_eat);
	pthread_mutex_lock(&philo->data->eat_mutex);
	philo->eat_count++;
	philo->last_eat = ft_time_ms();
	pthread_mutex_unlock(&philo->data->eat_mutex);
	pthread_mutex_unlock(&philo->data->fork_mutex[philo->r_fork]);
	pthread_mutex_unlock(&philo->data->fork_mutex[philo->l_fork]);
}

/**
 * This function will start the dinner for the philosopher. It will make the
 * philosopher eat, sleep and think until the dinner is over.
 * Put a delay for even philosophers to avoid deadlocks
 * Los filosofos pares tienen ventaja a la hora de coger tenedores
 * por lo que se anade un delay para que los impares no mueran, si el numero
 * de filosofos es impares se anade un delay para todos, para evitar deadlocks
 * en el caso de que el ultimo filosofo no pueda coger el tenedor derecho
 * esto funciona porque el ultimo filosofo coge el tenedor derecho primero
 * y el tenedor izquierdo despues y el delay es suficiente para que el primer
 * filosofo pueda coger el tenedor izquierdo de su vecino derecho antes de que
 * el ultimo filosofo coja el tenedor izquierdo
 * @param ptr The pointer to the philosopher
 *
 */
void	*philo_routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->id % 2 == 0)
		usleep(philo->data->time_to_eat);
	while (1)
	{
		if (philo->data->nbr_philos == 1)
		{
			one_philo(philo->data);
			return (0);
		}
		if (finish_question(philo))
			return (0);
		time_to_eat(philo);
		write_msg(philo, SLEEP);
		ft_usleep(philo, philo->data->time_to_sleep);
		write_msg(philo, THINK);
		if (philo->data->nbr_philos % 2 != 0)
			ft_usleep(philo, philo->data->time_to_eat);
	}	
	return (0);
}
