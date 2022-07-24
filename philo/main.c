/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabri <isabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 00:55:17 by isabri            #+#    #+#             */
/*   Updated: 2022/07/24 16:47:23 by isabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print(t_main *p, unsigned long long time, int id, char *str)
{
	int	died;

	pthread_mutex_lock(p->die);
	died = p->died;
	pthread_mutex_unlock(p->die);
	if (!died)
	{
		pthread_mutex_lock(p->print);
		printf("%llums %d %s\n", time, id, str);
		pthread_mutex_unlock(p->print);
	}
}

int	time_to_commit_die(t_main *p, unsigned long long last, int i)
{
	if (get_time() - last > p->time_to_die)
	{
		pthread_mutex_lock(p->die);
			p->died = 1;
		pthread_mutex_unlock(p->die);
		pthread_mutex_lock(p->print);
		printf("%llums %d %s\n", get_time() - p->start, p->philos[i].id, "died");
		pthread_mutex_unlock(p->print);
		pthread_mutex_unlock(&p->philos[i].eat);
		return (0);
	}
	return (1);
}

void	routine(t_philo *p)
{
	while (!get_condition_var(p, 1) && get_condition_var(p, 2) != 0)
	{
		pthread_mutex_lock(p->l_fork);
		print(p->pm, get_time() - p->pm->start, p->id, "has taken a fork");
		pthread_mutex_lock(p->r_fork);
		print(p->pm, get_time() - p->pm->start, p->id, "has taken a fork");
		print(p->pm, get_time() - p->pm->start, p->id, "is eating");
		pthread_mutex_lock(&p->eat);
		p->last_eat = get_time();
		if (p->n_must_eat != -1)
			p->n_must_eat--;
		pthread_mutex_unlock(&p->eat);
		tsleep(p->pm->time_to_eat);
		print(p->pm, get_time() - p->pm->start, p->id, "is sleeping");
		pthread_mutex_unlock(p->l_fork);
		pthread_mutex_unlock(p->r_fork);
		tsleep(p->pm->time_to_sleep);
		print(p->pm, get_time() - p->pm->start, p->id, "is thinking");
	}
}

int	death_checker(t_main *p)
{
	t_help	s;

	s.ate = (char *)malloc(sizeof(char) * p->nb_philo);
	while (1)
	{
		s.i = -1;
		usleep(100);
		while (++s.i < p->nb_philo)
		{
			pthread_mutex_lock(&p->philos[s.i].eat);
			s.last_eat = p->philos[s.i].last_eat;
			if (!time_to_commit_die(p, s.last_eat, s.i))
				return (0);
			if (!p->philos[s.i].n_must_eat)
				s.ate[s.i] = 1;
			pthread_mutex_unlock(&p->philos[s.i].eat);
			if (!check_eat(p, s.ate))
				return (0);
		}
	}
}

// int	death_checker(t_main *p)
// {
// 	t_help	s;

// 	s.j = 0;
// 	while (1)
// 	{
// 		s.i = -1;
// 		while (++s.i < p->nb_philo)
// 		{
// 			usleep(100);
// 			s.eat = 1;
// 			pthread_mutex_lock(&p->philos[s.i].eat);
// 			s.last_eat = p->philos[s.i].last_eat;
// 			if (!p->philos[s.i].n_must_eat)
// 			{
// 				p->philos[s.i].n_must_eat = -1;
// 				s.eat = 0;
// 			}
// 			if (!time_to_commit_die(p, s.last_eat, s.i))
// 				return (0);
// 			pthread_mutex_unlock(&p->philos[s.i].eat);
// 			if (!s.eat)
// 				if (++s.j == p->nb_philo)
// 					return (0);
// 		}
// 	}
// }

int	main(int ac, char **av)
{
	t_main	p;

	if (check_if_digit(ac, av) || check_arguments(ac, av))
		return (0);
	init_t_main(&p, ac, av);
	init_threads_forks(&p);
	return (0);
}
