/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odahriz <odahriz@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 11:35:36 by odahriz           #+#    #+#             */
/*   Updated: 2025/07/24 10:50:29 by odahriz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int parse_arg(char **str, t_philos_args *philo)
{
	philo->number_of_philos = ft_atoi(str[1]);
	if (philo->number_of_philos <= 0)
		return (0);
	philo->time_to_die = ft_atoi(str[2]);
	if (philo->time_to_die <= 0)
		return (0);
	philo->time_to_eat = ft_atoi(str[3]);
	if (philo->time_to_eat <= 0)
		return (0);
	philo->time_to_sleep = ft_atoi(str[4]);
	if (philo->time_to_sleep <= 0)
		return (0);
	if (str[5])
	{
		philo->n_of_eat = ft_atoi(str[5]);
		if (philo->n_of_eat <= 0)
			return (0);
	}
	printf("%d : %d : %d : %d : %d\n", philo->n_of_eat, philo->number_of_philos, philo->time_to_die, philo->time_to_eat, philo->time_to_sleep);
	return (1);
}
int main(int ac, char **av)
{
	t_philos_args *philo;

	philo = malloc(sizeof(t_philos_args));
	if (ac < 5 || ac > 6)
		return (printf("eroor\n"), 1);
	else if (!parse_arg(av, philo))
		return (printf("parse error\n"), 1);
	
	
}
