/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odahriz <odahriz@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 10:00:00 by odahriz           #+#    #+#             */
/*   Updated: 2025/08/10 10:00:00 by odahriz          ###   ########.fr       */
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
