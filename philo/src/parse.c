/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpeinado <victor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 21:27:02 by vpeinado          #+#    #+#             */
/*   Updated: 2024/02/16 21:30:47 by vpeinado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
* This function will parse the input arguments and store them in the t_data
* structure. It will also check if the arguments are valid.
*
*   @return 1 if the arguments are invalid, 0 if they are valid.
*
*   @param argc The number of arguments.
*
*   @param argv The arguments.
*
*   @param data The t_data structure where the arguments will be stored.
*/
int	parse_input(int argc, char **argv, t_data *data)
{
	if (argc < 5 || argc > 6)
		return (1);
	data->nbr_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->finish_flag = 0;
	if (argc == 6)
		data->must_eat_times = ft_atoi(argv[5]);
	else
		data->must_eat_times = -1;
	if (argc == 5 && (data->nbr_philos <= 0
			|| data->time_to_die <= 0
			|| data->time_to_eat <= 0
			|| data->time_to_sleep <= 0))
		return (1);
	else if (argc == 6 && (data->nbr_philos <= 0
			|| data->time_to_die <= 0
			|| data->time_to_eat <= 0
			|| data->time_to_sleep <= 0 || data->must_eat_times <= 0))
		return (1);
	return (0);
}
