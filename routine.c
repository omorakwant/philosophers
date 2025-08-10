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

void	take_even_forks(t_data *data)
{
	pthread_mutex_lock(data->right_fork);
	print_data(get_time() - data->start_time, data, "has taken a fork");
	if (data->args.number_of_philos == 1)
	{
		ft_sleep(data, data->args.time_to_die + 1);
		pthread_mutex_unlock(data->right_fork);
		return ;
	}
	pthread_mutex_lock(data->left_fork);
	print_data(get_time() - data->start_time, data, "has taken a fork");
}

void	take_odd_forks(t_data *data)
{
	pthread_mutex_lock(data->left_fork);
	print_data(get_time() - data->start_time, data, "has taken a fork");
	if (data->args.number_of_philos == 1)
	{
		ft_sleep(data, data->args.time_to_die + 1);
		pthread_mutex_unlock(data->left_fork);
		return ;
	}
	pthread_mutex_lock(data->right_fork);
	print_data(get_time() - data->start_time, data, "has taken a fork");
}

void	take_forks(t_data *data)
{
	if (data->id % 2 == 0)
		take_even_forks(data);
	else
		take_odd_forks(data);
}

void	is_eat(t_data *data)
{
	pthread_mutex_lock(data->meals_mutex);
	data->last_eat = get_time();
	pthread_mutex_unlock(data->meals_mutex);
	print_data(get_time() - data->start_time, data, "is eating");
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

void	*routine(void *arg)
{
	t_data				*data;

	data = arg;
	if (data->id % 2 == 0)
		usleep(100);
	while (!is_dead(data))
	{
		if (data->args.n_of_eat != -1)
		{
			pthread_mutex_lock(data->meals_mutex);
			if (data->meals_eaten >= data->args.n_of_eat)
			{
				pthread_mutex_unlock(data->meals_mutex);
				break ;
			}
			pthread_mutex_unlock(data->meals_mutex);
		}
		take_forks(data);
		if (data->args.number_of_philos == 1)
			break ;
		is_eat(data);
		is_sleep(data);
		print_data(get_time() - data->start_time, data, "is thinking");
	}
	return (NULL);
}
