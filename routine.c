/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odahriz <odahriz@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:22:07 by odahriz           #+#    #+#             */
/*   Updated: 2025/07/31 11:47:44 by odahriz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take_forks(t_data *data)
{

	pthread_mutex_lock(data->left_fork);
	print_data(get_time() - data->start_time, data, "has taken a fork");
	pthread_mutex_lock(data->right_fork);
	print_data(get_time() - data->start_time, data, "has taken a fork");
}

void	is_eat(t_data *data)
{
	pthread_mutex_lock(&data->meals);
	data->last_eat = get_time() - data->start_time;
	pthread_mutex_unlock(&data->meals);
	print_data(get_time() - data->start_time, data, "is eating");
	ft_sleep(data, data->args.time_to_eat);
	pthread_mutex_unlock(data->left_fork);
	pthread_mutex_unlock(data->right_fork);
}

void	is_sleep(t_data *data)
{
	print_data(get_time() - data->start_time, data, "is sleeping");
	ft_sleep(data, data->args.time_to_sleep);
}

void	*routine(void *arg)
{
	t_data			*data;
	data = arg;
	data->last_eat = get_time() - data->start_time;
	if (data->id % 2 == 0)
		usleep(100);
	while(!is_dead(data))
	{
		take_forks(data);
		is_eat(data);
		is_sleep(data);
		print_data(get_time() - data->start_time, data, "is thinking");
	}
	return (NULL);
}
