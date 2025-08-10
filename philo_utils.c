/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odahriz <odahriz@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 10:00:00 by odahriz           #+#    #+#             */
/*   Updated: 2025/08/10 10:00:00 by odahriz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_philosopher_death(t_data *data, unsigned int i)
{
	int	died;

	died = 0;
	pthread_mutex_lock(data[i].meals_mutex);
	if (get_time() - data[i].last_eat > data[i].args.time_to_die)
	{
		pthread_mutex_unlock(data[i].meals_mutex);
		set_dead(data, i);
		pthread_mutex_lock(data->args.dead);
		if (data->args.death == 1)
			printf("%lu %d %s\n", get_time() - data[i].start_time,
				data[i].id, "died");
		pthread_mutex_unlock(data->args.dead);
		died = 1;
	}
	else
		pthread_mutex_unlock(data[i].meals_mutex);
	return (died);
}

int	all_eaten_enough(t_data *data)
{
	unsigned int	i;
	unsigned int	finished_eating;

	if (data->args.n_of_eat == -1)
		return (0);
	i = 0;
	finished_eating = 0;
	while (i < data->args.number_of_philos)
	{
		pthread_mutex_lock(data[i].meals_mutex);
		if (data[i].meals_eaten >= data->args.n_of_eat || data[i].finished)
			finished_eating++;
		pthread_mutex_unlock(data[i].meals_mutex);
		i++;
	}
	return (finished_eating == data->args.number_of_philos);
}

void	cleanup_resources(t_data *data, pthread_mutex_t *forks,
		pthread_mutex_t *meals_mutex)
{
	unsigned int	i;

	i = 0;
	while (i < data->args.number_of_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		pthread_mutex_destroy(&meals_mutex[i]);
		i++;
	}
	pthread_mutex_destroy(data->args.dead);
	free(forks);
	free(meals_mutex);
	free(data->args.dead);
}

pthread_mutex_t	*forks_init(t_data *data, t_philos_args *args)
{
	pthread_mutex_t	*forks;
	unsigned int	i;

	(void)data;
	forks = malloc(args->number_of_philos * sizeof(pthread_mutex_t));
	if (!forks)
		return (NULL);
	i = 0;
	while (i < args->number_of_philos)
	{
		if (pthread_mutex_init(&(forks[i]), NULL) != 0)
		{
			while (i > 0)
			{
				i--;
				pthread_mutex_destroy(&(forks[i]));
			}
			free(forks);
			return (NULL);
		}
		i++;
	}
	return (forks);
}
