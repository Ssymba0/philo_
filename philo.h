/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabri <isabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 16:33:27 by isabri            #+#    #+#             */
/*   Updated: 2022/07/15 15:55:13 by isabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>	
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>

typedef struct s_main	t_main;

typedef struct s_philo
{
	int				id;
	long			start;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_must_eat;
	long			last_eat;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_t		th;
	t_main			*p_main;
}	t_philo;

typedef struct s_main
{
	int				nb_philo;
	int				died;
	t_philo			*philos;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*print;
}	t_main;

int			ft_atoi(char *s);
int			is_digit(char *s);
void		tsleep(int usecs);
long int	get_time(void);

#endif