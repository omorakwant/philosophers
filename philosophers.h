/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odahriz <odahriz@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 11:36:30 by odahriz           #+#    #+#             */
/*   Updated: 2025/07/31 13:06:55 by odahriz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philos_args
{
	unsigned int	number_of_philos;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	n_of_eat;
	int				death;
	pthread_mutex_t	dead;
}					t_philos_args;

typedef struct s_data
{
	int				id;
	unsigned long	start_time;
	unsigned long	last_eat;
	pthread_mutex_t	meals;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	die;
	pthread_t		thread;
	t_philos_args	args;
}					t_data;

int					ft_atoi(const char *nptr);
unsigned long		get_time(void);
void				philo_init(t_data *data, t_philos_args *philo);
void				*routine(void *data);
void				print_data(unsigned long time, t_data *data, char *action);
void				ft_sleep(t_data *data, unsigned long time);
int					is_dead(t_data *data);

#endif