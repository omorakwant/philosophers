/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odahriz <odahriz@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 11:36:30 by odahriz           #+#    #+#             */
/*   Updated: 2025/08/10 09:28:45 by odahriz          ###   ########.fr       */
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
	int				n_of_eat;
	int				death;
	pthread_mutex_t	*dead;
}					t_philos_args;

typedef struct s_data
{
	int				id;
	unsigned long	start_time;
	unsigned long	last_eat;
	int				meals_eaten;
	pthread_mutex_t	*meals_mutex;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
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
void				set_dead(t_data *data, unsigned int i);
void				cleanup_resources(t_data *data, pthread_mutex_t *forks,
						pthread_mutex_t *meals_mutex);
int					all_eaten_enough(t_data *data);
void				take_even_forks(t_data *data);
void				take_odd_forks(t_data *data);
void				init_philos_data(t_data *data, t_philos_args *args,
						pthread_mutex_t *meals_mutex, pthread_mutex_t *forks);
int					check_philosopher_death(t_data *data, unsigned int i);
void				is_sleep(t_data *data);

#endif