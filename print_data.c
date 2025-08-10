/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odahriz <odahriz@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 10:19:27 by odahriz           #+#    #+#             */
/*   Updated: 2025/08/10 09:28:45 by odahriz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_dead(t_data *data)
{
	pthread_mutex_lock(data->args.dead);
	if (data->args.death == 1)
	{
		pthread_mutex_unlock(data->args.dead);
		return (1);
	}
	pthread_mutex_unlock(data->args.dead);
	return (0);
}

void	print_data(unsigned long time, t_data *data, char *action)
{
	if (!action)
		return ;
	pthread_mutex_lock(data->args.dead);
	if (data->args.death == 0)
		printf("%lu %d %s\n", time, data->id, action);
	pthread_mutex_unlock(data->args.dead);
}
