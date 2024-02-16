/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpeinado <victor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 16:45:52 by vpeinado          #+#    #+#             */
/*   Updated: 2024/02/16 21:26:50 by vpeinado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/*
** This function is the main function of the program. It will parse the input
** arguments, call the function to initialize the threads and mutexes, and
** start the dinner monitor.
*/
int	main(int argc, char **argv)
{
	t_data	data;

	if (parse_input(argc, argv, &data))
	{
		printf("Error: invalid arguments\n");
		return (1);
	}
	init_philosophers(&data);
	init_threads_and_mutex(&data);
	control_dinner(&data);
	finish_dinner(&data);
	return (0);
}
