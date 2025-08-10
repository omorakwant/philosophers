/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odahriz <odahriz@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 09:54:26 by odahriz           #+#    #+#             */
/*   Updated: 2025/08/10 09:28:45 by odahriz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	set_dead(t_data *data, unsigned int i)
{
	unsigned int	j;

	(void)i;
	j = 0;
	while (j < data->args.number_of_philos)
	{
		pthread_mutex_lock(data[j].args.dead);
		data[j].args.death = 1;
		pthread_mutex_unlock(data[j].args.dead);
		j++;
	}
}

void	ft_sleep(t_data *data, unsigned long time)
{
	unsigned long	start;
	unsigned long	elapsed;
	unsigned long	sleep_time;

	start = get_time();
	elapsed = 0;
	sleep_time = time;
	while (elapsed < sleep_time)
	{
		if (is_dead(data))
			return ;
		usleep(100);
		elapsed = get_time() - start;
	}
}

int	ft_isdigit(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	ft_atoi(const char *nptr)
{
	long	result;
	int		sign;
	int		i;

	result = 0;
	sign = 1;
	i = 0;
	while (nptr[i] == ' ' || nptr[i] == '\t' || nptr[i] == '\n'
		|| nptr[i] == '\v' || nptr[i] == '\f' || nptr[i] == '\r')
		i++;
	if (nptr[i] == '-' || !ft_isdigit(nptr))
		return (0);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + (nptr[i] - '0');
		if (result > 2147483647)
			return (0);
		i++;
	}
	return ((int)(result * sign));
}
