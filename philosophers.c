/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odahriz <odahriz@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 11:35:36 by odahriz           #+#    #+#             */
/*   Updated: 2025/07/31 11:31:34 by odahriz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
	return (1);
}

int	main(int ac, char **av)
{
	t_philos_args	*args;
	t_data			*data;

	data = NULL;
	args = malloc(sizeof(t_philos_args));
	if (ac < 5 || ac > 6)
		return (printf("error\n"), 1);
	else if (!parse_arg(av, args))
		return (printf("parse error\n"), 1);
	data = malloc(args->number_of_philos * sizeof(t_data));
	philo_init(data, args);
}
