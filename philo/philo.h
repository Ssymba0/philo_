/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabri <isabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 16:33:27 by isabri            #+#    #+#             */
/*   Updated: 2022/07/22 16:23:21 by isabri           ###   ########.fr       */
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
	int					id;
	int					n_must_eat;
	unsigned long long	last_eat;
	pthread_mutex_t		eat;
	pthread_mutex_t		*l_fork;
	pthread_mutex_t		*r_fork;
	pthread_t			th;
	t_main				*pm;
}	t_philo;

typedef struct s_main
{
	int					nb_philo;
	unsigned long long	time_to_die;
	unsigned long long	time_to_eat;
	unsigned long long	time_to_sleep;
	int					died;
	unsigned long long	start;
	t_philo				*philos;
	pthread_mutex_t		*die;
	pthread_mutex_t		*fork;
	pthread_mutex_t		*print;
}	t_main;

typedef struct s_help
{
	int					i;
	unsigned long long	last_eat;
	int					j;
	int					eat;
}	t_help;

int					ft_atoi(char *s);
int					is_digit(char *s);
void				tsleep(unsigned long long usecs);
unsigned long long	get_time(void);
int					death_checker(t_main *p);
void				init_threads_forks(t_main *p);
void				routine(t_philo *p);
void				init_t_main(t_main	*p, int ac, char **av);
int					check_if_digit(int ac, char **av);
int					check_arguments(int ac, char **av);
void				mutex_destroyer(t_main *p);
int					get_condition_var(t_philo *p, int i);

#endif