/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpeinado <victor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 21:33:04 by vpeinado          #+#    #+#             */
/*   Updated: 2024/02/16 21:35:11 by vpeinado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

time_t	ft_time_ms(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

void	ft_usleep(t_philo *philo, time_t stop)
{
	time_t	begin;

	begin = ft_time_ms();
	while (!finish_question(philo) && (ft_time_ms() - begin) < stop)
		usleep(100);
}
