/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odahriz <odahriz@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 11:35:36 by odahriz           #+#    #+#             */
/*   Updated: 2025/08/05 15:38:44 by odahriz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	is_sleep(t_data *data)
{
	print_data(get_time() - data->start_time, data, "is sleeping");
	ft_sleep(data, data->args.time_to_sleep);
}

int	parse_arg(char **str, t_philos_args *args)
{
	args->number_of_philos = ft_atoi(str[1]);
	if (args->number_of_philos <= 0)
		return (0);
	args->time_to_die = ft_atoi(str[2]);
	if (args->time_to_die <= 0)
		return (0);
	args->time_to_eat = ft_atoi(str[3]);
	if (args->time_to_eat <= 0)
		return (0);
	args->time_to_sleep = ft_atoi(str[4]);
	if (args->time_to_sleep <= 0)
		return (0);
	if (str[5])
	{
		args->n_of_eat = ft_atoi(str[5]);
		if (args->n_of_eat <= 0)
			return (0);
	}
	else
		args->n_of_eat = -1;
	return (1);
}

int	main(int ac, char **av)
{
	t_philos_args	*args;
	t_data			*data;

	data = NULL;
	args = malloc(sizeof(t_philos_args));
	if (!args)
		return (printf("Memory allocation error\n"), 1);
	if (ac < 5 || ac > 6)
		return (free(args), printf("Usage: ./philo number_of_philosophers time_to_die\
			time_to_eat time_to_sleep\
			[number_of_times_each_philosopher_must_eat]\n"), 1);
	else if (!parse_arg(av, args))
		return (free(args), printf("Invalid arguments\n"), 1);
	data = malloc(args->number_of_philos * sizeof(t_data));
	if (!data)
		return (free(args), printf("Memory allocation error\n"), 1);
	philo_init(data, args);
	free(args);
	free(data);
	return (0);
}
