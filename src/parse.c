#include "philo.h"

int parse_and_init(int argc, char **argv, t_data *data)
{
    struct timeval t_start;
    
    if (argc < 5 || argc > 6)
        return (1);
    gettimeofday(&t_start, NULL);
    data->time_start = t_start.tv_sec * 1000 + t_start.tv_usec / 1000;
    data->n_philo = ft_atoi(argv[1]);
    data->time_die = ft_atoi(argv[2]);
    data->time_eat = ft_atoi(argv[3]);
    data->time_sleep = ft_atoi(argv[4]);
    if (argc == 6)
        data->times_must_eat = ft_atoi(argv[5]);
    else
        data->times_must_eat = 0;
    if(argc == 5 && (data->n_philo <= 0 ||
        data->time_die <= 0 ||
        data->time_eat <= 0 ||
        data->time_sleep <= 0))
        return (1);
    else if(argc == 6 && (data->n_philo <= 0 ||
        data->time_die <= 0 ||
        data->time_eat <= 0 ||
        data->time_sleep <= 0 || data->times_must_eat <= 0))
        return (1);
    return (0);
}
