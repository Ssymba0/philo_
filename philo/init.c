/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabri <isabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 09:14:47 by isabri            #+#    #+#             */
/*   Updated: 2022/07/22 16:23:09 by isabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_t_main(t_main	*p, int ac, char **av)
{
	int		i;

	p->died = 0;
	p->nb_philo = ft_atoi(av[1]);
	p->philos = (t_philo *)malloc(sizeof(t_philo) * p->nb_philo);
	p->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * p->nb_philo);
	p->print = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	p->die = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	p->start = get_time();
	p->time_to_die = ft_atoi(av[2]);
	p->time_to_eat = ft_atoi(av[3]);
	p->time_to_sleep = ft_atoi(av[4]);
	i = -1;
	while (++i < p->nb_philo)
	{
		p->philos[i].id = i + 1;
		if (ac > 5)
			p->philos[i].n_must_eat = ft_atoi(av[5]);
		else
			p->philos[i].n_must_eat = -1;
		p->philos[i].l_fork = &p->fork[i];
		p->philos[i].r_fork = &p->fork[(i + 1) % p->nb_philo];
		p->philos[i].pm = p;
	}
}

void	init_forks(t_main *p)
{
	int		i;

	i = -1;
	while (++i < p->nb_philo)
	{
		pthread_mutex_init(&p->fork[i], NULL);
		pthread_mutex_init(&p->philos[i].eat, NULL);
	}
	pthread_mutex_init(p->print, NULL);
	pthread_mutex_init(p->die, NULL);
}

void	mutex_destroyer(t_main *p)
{
	int		i;

	i = -1;
	while (++i < p->nb_philo)
	{
		pthread_mutex_destroy(&p->philos[i].eat);
		pthread_mutex_destroy(&p->fork[i]);
	}
	pthread_mutex_destroy(p->print);
	pthread_mutex_destroy(p->die);
}

void	init_threads_forks(t_main *p)
{
	int		i;

	init_forks(p);
	i = 0;
	while (i < p->nb_philo)
	{
		p->philos[i].last_eat = get_time();
		pthread_create(&p->philos[i].th, NULL, (void *)routine, &p->philos[i]);
		i += 2;
	}
	i = 1;
	while (i < p->nb_philo)
	{
		usleep(100);
		p->philos[i].last_eat = get_time();
		pthread_create(&p->philos[i].th, NULL, (void *)routine, &p->philos[i]);
		i += 2;
	}
	i = -1;
	death_checker(p);
	while (++i < p->nb_philo)
		pthread_join(p->philos[i].th, NULL);
}

int	get_condition_var(t_philo *p, int i)
{
	int	res;

	if (i == 1)
	{
		pthread_mutex_lock(p->pm->die);
		res = p->pm->died;
		pthread_mutex_unlock(p->pm->die);
	}
	else
	{
		pthread_mutex_lock(&p->eat);
		res = p->n_must_eat;
		pthread_mutex_unlock(&p->eat);
	}
	return (res);
}
