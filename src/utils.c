#include "philo.h"

int	ft_atoi(const char *str)
{
	int	sign;
	int	num;

	sign = 1;
	num = 0;
	while (*str && (*str == 32 || (*str >= 9 && *str <= 13)))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str && (*str > '0' || *str < '9'))
	{
		num = (num * 10) + (*str - '0');
		str++;
	}
	return (num * sign);
}

time_t ft_time_ms(void)
{
    struct timeval t;
    
    gettimeofday(&t, NULL);
    return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

void clean(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->all_philos[i].check_alive);
		i++;
	}
	pthread_mutex_destroy(&data->m_control);
	pthread_mutex_destroy(&data->m_writing);
    free(data->all_philos);
	free(data->forks);
	free(data);
}