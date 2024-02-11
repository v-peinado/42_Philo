/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpeinado <victor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 17:32:59 by vpeinado          #+#    #+#             */
/*   Updated: 2024/02/11 20:55:21 by vpeinado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

void write_msg(t_philosofer *philo, char *msg)
{
    time_t time;
    
    time = ft_time_ms() - philo->data->time_start;
    pthread_mutex_lock(&philo->data->m_writing);
	pthread_mutex_lock(&philo->data->m_control);
	if (philo->data->dead != 0
		|| philo->data->satisfied == philo->data->n_philo)
	{
		pthread_mutex_unlock(&philo->data->m_control);
		pthread_mutex_unlock(&philo->data->m_writing);
		return ;
	}
    printf("%ld %d %s\n", time, philo->philo_id, msg);
    pthread_mutex_unlock(&philo->data->m_control);
	pthread_mutex_unlock(&philo->data->m_writing);    
}
int take_forks(t_philosofer *philo)
{
    if(pthread_mutex_lock(&philo->data->m_control))
        return 1;
    if (philo->data->dead != 0
		|| philo->data->satisfied == philo->data->n_philo)
	{
		pthread_mutex_unlock(&philo->data->m_control);
	}
    pthread_mutex_unlock(&philo->data->m_control);
	if (philo->philo_id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		write_msg(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		write_msg(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		write_msg(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		write_msg(philo, "has taken a fork");
	}
    return 0;
}

int eating(t_philosofer *philo)
{
	pthread_mutex_lock(&philo->data->m_control);
	if (philo->data->dead != 0
		|| philo->data->satisfied == philo->data->n_philo)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(&philo->data->m_control);
        return 1;
	}
	pthread_mutex_unlock(&philo->data->m_control);
	pthread_mutex_lock(&philo->check_alive);
	write_msg(philo, "is eating");
	philo->last_meal_time = ft_time_ms();
	pthread_mutex_lock(&philo->data->m_control);
	if (philo->data->times_must_eat != 0)
	{
		philo->times_eat++;
		if (philo->times_eat == philo->data->times_must_eat)
			philo->data->satisfied++;
	}
	pthread_mutex_unlock(&philo->data->m_control);
	pthread_mutex_unlock(&philo->check_alive);
	usleep(philo->data->time_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
    return 0;
}

int sleeping(t_philosofer *philo)
{
    pthread_mutex_lock(&philo->data->m_control);
	if (philo->data->dead != 0
		|| philo->data->satisfied == philo->data->n_philo)
	{
		pthread_mutex_unlock(&philo->data->m_control);
        return 1;
	}
	pthread_mutex_unlock(&philo->data->m_control);
	write_msg(philo, "is sleeping");
	usleep(philo->data->time_sleep * 1000);
    return 0;
}

int thinking(t_philosofer *philo)
{
    pthread_mutex_lock(&philo->data->m_control);
    if (philo->data->dead != 0
        || philo->data->satisfied == philo->data->n_philo)
    {
        pthread_mutex_unlock(&philo->data->m_control);
        return 1;
    }
    pthread_mutex_unlock(&philo->data->m_control);
    write_msg(philo, "is thinking");
    return 0;
}
void *philo_routine(void *arg)
{
    t_philosofer *philo;
    
    philo = (t_philosofer *)arg;
    if (philo->data->n_philo == 1) 
	{
		pthread_mutex_lock(philo->right_fork);
		write_msg(philo, "has taken a fork");
		pthread_mutex_unlock(philo->right_fork);
		return (NULL);
	}
    //if (philo->philo_id % 2 == 0)
		//usleep(100);
    while (1)
	{
        if (take_forks(philo) == 1)
			return (NULL);
		if (eating(philo) == 1)
			return (NULL);
		if (sleeping(philo) == 1)
			return (NULL);
		if (thinking(philo) == 1)
			return (NULL);
	}
    return (NULL);
}
int	everyone_ate(t_data *data)
{
	pthread_mutex_lock(&data->m_control);
	if (data->satisfied == data->n_philo)
	{
        printf("\033[1;32mAll philos ate %d times\n\n\033[0m", data->times_must_eat);
		pthread_mutex_unlock(&data->m_control);
		return (0);
	}
	pthread_mutex_unlock(&data->m_control);
	return (1);
}

int is_dead(t_data *data)
{
    int i;
    
    i = 0;
    while (i < data->n_philo)
    {
        pthread_mutex_lock(&data->all_philos[i].check_alive);
		if (ft_time_ms() - data->all_philos[i].last_meal_time > data->time_die)
		{
			write_msg(&data->all_philos[i], "died");
			pthread_mutex_lock(&data->m_control);
			data->dead++;
			pthread_mutex_unlock(&data->m_control);
			pthread_mutex_unlock(&data->all_philos[i].check_alive);
			return (0);
		}
		pthread_mutex_unlock(&data->all_philos[i].check_alive);
		i++;
    }
    return (1);
}

void	*check_philos(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		if (is_dead(data) == 0)
			return (NULL);
		if (data->times_must_eat != 0)
			if (everyone_ate(data) == 0)
				return (NULL);
	}
}

void    threads_join(t_data *data)
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