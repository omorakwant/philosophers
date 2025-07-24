/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odahriz <odahriz@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 11:36:30 by odahriz           #+#    #+#             */
/*   Updated: 2025/07/24 10:11:57 by odahriz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <unistd.h>
#include <threads.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct s_philos_args
{
	unsigned int number_of_philos;
	unsigned int time_to_die;
	unsigned int time_to_eat;
	unsigned int time_to_sleep;
	unsigned int n_of_eat;
}	t_philos_args;


void	handle_five_args(char **av);
void	handle_four_args(char **av);
int		ft_atoi(const char *nptr);

#endif