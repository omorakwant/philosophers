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

void	monitor(t_data *data)
{
	unsigned int	i;

	while (1)
	{
		i = 0;
		while (i < data->args.number_of_philos)
		{
			if (check_philosopher_death(data, i))
				return ;
			i++;
		}
		if (all_eaten_enough(data))
			return ;
		usleep(1000);
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
		data[i].last_eat = get_time();
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
	args->dead = dead;
	init_philos_data(data, args, meals_mutex, forks);
	create_threads(data);
	cleanup_resources(data, forks, meals_mutex);
}
