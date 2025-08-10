/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odahriz <odahriz@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 11:11:07 by odahriz           #+#    #+#             */
/*   Updated: 2025/08/10 09:28:45 by odahriz          ###   ########.fr       */
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
	unsigned int	i;

	while (1)
	{
		if (all_eaten_enough(data))
			return ;
		i = 0;
		while (i < data->args.number_of_philos)
		{
			if (check_philosopher_death(data, i))
				return ;
			i++;
		}
		usleep(100);
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
		data[i].last_eat = start_time;
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

void	init_philos_data(t_data *data, t_philos_args *args,
		pthread_mutex_t *meals_mutex, pthread_mutex_t *forks)
{
	unsigned int	i;

	i = 0;
	while (i < args->number_of_philos)
	{
		pthread_mutex_init(&meals_mutex[i], NULL);
		data[i].id = i + 1;
		data[i].meals_eaten = 0;
		data[i].finished = 0;
		data[i].meals_mutex = &meals_mutex[i];
		data[i].left_fork = &forks[i];
		data[i].right_fork = &forks[(i + 1) % args->number_of_philos];
		data[i].args = *args;
		i++;
	}
}

void	philo_init(t_data *data, t_philos_args *args)
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	*dead;
	pthread_mutex_t	*meals_mutex;

	if (!data)
		return ;
	forks = forks_init(data, args);
	dead = malloc(sizeof(pthread_mutex_t));
	meals_mutex = malloc(args->number_of_philos * sizeof(pthread_mutex_t));
	if (!dead || !meals_mutex || !forks)
		return ;
	pthread_mutex_init(dead, NULL);
	args->death = 0;
	args->all_ate = 0;
	args->dead = dead;
	init_philos_data(data, args, meals_mutex, forks);
	create_threads(data);
	cleanup_resources(data, forks, meals_mutex);
}
