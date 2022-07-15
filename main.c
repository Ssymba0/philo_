/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabri <isabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 00:55:17 by isabri            #+#    #+#             */
/*   Updated: 2022/07/15 15:57:46 by isabri           ###   ########.fr       */
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
	i = -1;
	while (++i < p->nb_philo)
	{
		p->philos[i].id = i;
		p->philos[i].start = get_time();
		p->philos[i].last_eat = p->philos[i].start;
		p->philos[i].time_to_die = ft_atoi(av[2]);
		p->philos[i].time_to_eat = ft_atoi(av[3]);
		p->philos[i].time_to_sleep = ft_atoi(av[4]);
		if (ac > 5)
			p->philos[i].n_must_eat = ft_atoi(av[5]);
		else
			p->philos[i].n_must_eat = -1;
		p->philos[i].l_fork = &p->fork[i];
		p->philos[i].r_fork = &p->fork[(i + 1) % p->nb_philo];
		p->philos[i].p_main = p;
	}
}

void	print(t_main *p, long time, int id, char *str)
{
	pthread_mutex_lock(p->print);
	printf("%ldms %d %s\n", time, id, str);
	pthread_mutex_unlock(p->print);
}

void	philo_thread(t_philo *p)
{
	while (get_time() - p->last_eat < p->time_to_die && !p->p_main->died)
	{
		pthread_mutex_lock(p->l_fork);
		print(p->p_main, get_time() - p->start, p->id, "has taken a fork");
		pthread_mutex_lock(p->r_fork);
		print(p->p_main, get_time() - p->start, p->id, "has taken a fork");
		print(p->p_main, get_time() - p->start, p->id, "is eating");
		tsleep(p->time_to_eat);
		p->last_eat = get_time();
		pthread_mutex_unlock(p->l_fork);
		pthread_mutex_unlock(p->r_fork);
		print(p->p_main, get_time() - p->start, p->id, "is sleeping");
		tsleep(p->time_to_sleep);
		print(p->p_main, get_time() - p->start, p->id, "is thinking");
	}
	p->p_main->died = 1;
	print(p->p_main, get_time() - p->start, p->id, "is dead");
	return ;
}

void	init_threads_forks(t_main	*p)
{
	int		i;

	i = -1;
	while (++i < p->nb_philo)
	{
		pthread_mutex_init(&p->fork[i], NULL);
	}
	pthread_mutex_init(p->print, NULL);
	i = 0;
	while (i < p->nb_philo)
	{
		pthread_create(&p->philos[i].th, NULL, (void *)philo_thread, &p->philos[i]);
		usleep(20);
		i += 2;
	}
	i = 1;
	while (i < p->nb_philo)
	{
		pthread_create(&p->philos[i].th, NULL, (void *)philo_thread, &p->philos[i]);
		usleep(20);
		i += 2;
	}
	i = 0;
	while (i < p->nb_philo)
	{
		pthread_join(p->philos[i].th, NULL);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_main	p;

	init_t_main(&p, ac, av);
	init_threads_forks(&p);
	return (0);
}
