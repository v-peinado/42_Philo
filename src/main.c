/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpeinado <victor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 16:45:52 by vpeinado          #+#    #+#             */
/*   Updated: 2024/02/11 20:36:06 by vpeinado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"
int main(int argc, char **argv)
{
    t_data *data;
    data = malloc(sizeof(t_data));
    if(!data)
        return (1);
    memset(data, 0, sizeof(t_data));
    if(parse_and_init(argc, argv, data))
    {
        printf("Error: invalid arguments\n");
        free(data);
        return (1);
    }
    forks_init(data);
    philos_init(data);
    thread_init(data);
    threads_join(data);
    clean(data);
    return (0);
}