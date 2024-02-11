/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpeinado <victor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 17:07:48 by vpeinado          #+#    #+#             */
/*   Updated: 2024/02/11 20:47:24 by vpeinado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
void	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		pthread_join(data->all_philos[i].philo, NULL);

		i++;
	}
	pthread_join(data->supervise, NULL);
}

void    forks_init(t_data *data)
{
    int i;
    i = 0;
    data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philo);
    if (!data->forks)
        return ;
    while (i < data->n_philo)
    {
        pthread_mutex_init(&data->forks[i], NULL);
        i++;
    }
    pthread_mutex_init(&data->m_control, NULL);
    pthread_mutex_init(&data->m_writing, NULL);
}

void philos_init(t_data *data)
{
    int i;
    i = 0;
    data->all_philos = malloc(sizeof(t_philosofer) * data->n_philo);
    if (!data->all_philos)
        return ;
    while (i < data->n_philo)
    {
        data->all_philos[i].philo_id = i + 1;
        data->all_philos[i].times_eat = 0;
        data->all_philos[i].last_meal_time = ft_time_ms();
        data->all_philos[i].data = data;
        data->all_philos[i].left_fork = &data->forks[i];
        data->all_philos[i].right_fork = &data->forks[(i + 1) % data->n_philo];
        pthread_mutex_init(&data->all_philos[i].check_alive, NULL);
        i++;
    }
}

void thread_init(t_data *data)
{
    int i;
    i = 0;

    while (i < data->n_philo)
    {
        if(i % 2 == 0)
            pthread_create(&data->all_philos[i].philo, NULL, &philo_routine, &data->all_philos[i]);
        i++;
        usleep(5);
    }
    usleep(200);
    i = 0;
    while (i < data->n_philo)
    {
        if(i % 2 != 0)
            pthread_create(&data->all_philos[i].philo, NULL, &philo_routine, &data->all_philos[i]);
        i++;
    }
    pthread_create(&data->supervise, NULL, &check_philos, data);
}