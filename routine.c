/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odahriz <odahriz@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:22:07 by odahriz           #+#    #+#             */
/*   Updated: 2025/08/05 15:38:35 by odahriz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	is_eat(t_data *data)
{
	print_data(get_time() - data->start_time, data, "is eating");
	pthread_mutex_lock(data->meals_mutex);
	data->last_eat = get_time();
	pthread_mutex_unlock(data->meals_mutex);
	ft_sleep(data, data->args.time_to_eat);
	pthread_mutex_lock(data->meals_mutex);
	data->meals_eaten++;
	pthread_mutex_unlock(data->meals_mutex);
	if (data->id % 2 == 0)
	{
		pthread_mutex_unlock(data->right_fork);
		pthread_mutex_unlock(data->left_fork);
	}
	else
	{
		pthread_mutex_unlock(data->left_fork);
		pthread_mutex_unlock(data->right_fork);
	}
}

int	should_stop_eating(t_data *data)
{
	if (data->args.n_of_eat != -1)
	{
		pthread_mutex_lock(data->meals_mutex);
		if (data->meals_eaten >= data->args.n_of_eat)
		{
			data->finished = 1;
			pthread_mutex_unlock(data->meals_mutex);
			return (1);
		}
		pthread_mutex_unlock(data->meals_mutex);
	}
	return (0);
}

void	*routine(void *arg)
{
	t_data				*data;

	data = arg;
	if (data->id % 2 == 0)
		usleep(100);
	while (!is_dead(data))
	{
		if (should_stop_eating(data))
			break ;
		take_forks(data);
		if (data->args.number_of_philos == 1)
			break ;
		is_eat(data);
		is_sleep(data);
		print_data(get_time() - data->start_time, data, "is thinking");
	}
	return (NULL);
}
