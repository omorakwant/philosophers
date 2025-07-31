/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odahriz <odahriz@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 11:11:07 by odahriz           #+#    #+#             */
/*   Updated: 2025/07/31 12:07:07 by odahriz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	monitor(t_data *data)
{
	unsigned int i;
	int 		die;
	while(1)
	{
		i = 0;
		while(i < data->args.number_of_philos)
		{
			pthread_mutex_lock(&data[i].meals);
			if(data[i].last_eat > data[i].args.time_to_die)
			{
				pthread_mutex_unlock(&data[i].meals);
				die = i;
				i = 0;
				while(i < data->args.number_of_philos)
				{
					pthread_mutex_lock(&data[i].args.dead);
					data[i].args.death = 1;
					pthread_mutex_unlock(&data[i].args.dead);
					i++;
				}
				printf("%lu %d %s\n", get_time() - data[die].start_time, data->id, "died");
				return ;
			}
			pthread_mutex_unlock(&data[i].meals);
			i++;
		}
	}
}

int	create_threads(t_data *data)
{
	unsigned int	i;
	unsigned long	start_time;

	i = 0;
	start_time = get_time();
	while (i < data->args.number_of_philos)
	{
		data[i].start_time = start_time;
		pthread_create(&(data[i].thread), NULL, routine, &(data[i]));
		i++;
	}
	monitor(data);
	i = 0;
	while (i < data->args.number_of_philos)
	{
		pthread_join(data[i].thread, NULL);
		i++;
	}
	return (0);
}

pthread_mutex_t	*forks_init(t_data *data, t_philos_args *args)
{
	pthread_mutex_t	*forks;
	unsigned int	i;

	(void)data;
	forks = malloc(args->number_of_philos * sizeof(pthread_mutex_t));
	i = 0;
	while (i < args->number_of_philos)
	{
		if (pthread_mutex_init(&(forks[i]), NULL) != 0)
		{
			i--;
			while (i >= 0)
				pthread_mutex_destroy(&(forks[i--]));
			free(forks);
			return (NULL);
		}
		i++;
	}
	return (forks);
}

void	philo_init(t_data *data, t_philos_args *args)
{
	pthread_mutex_t	*forks;
	unsigned int	i;

	i = 0;
	if (!data)
		return ;
	forks = forks_init(data, args);
	pthread_mutex_init(&args->dead, NULL);
	pthread_mutex_init(&data->meals, NULL);
	args->death = 0;
	while (i < args->number_of_philos)
	{
		data[i].id = i + 1;
		data[i].left_fork = &forks[(i + 1) % args->number_of_philos];
		data[i].right_fork = &forks[i];
		data[i].args.number_of_philos = args->number_of_philos;
		data[i].args.time_to_die = args->time_to_die;
		data[i].args.time_to_eat = args->time_to_eat;
		data[i].args.time_to_sleep = args->time_to_sleep;
		data[i].args.dead = args->dead;
		i++;
	}
	create_threads(data);
}
