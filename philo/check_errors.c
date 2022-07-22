/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabri <isabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 09:23:41 by isabri            #+#    #+#             */
/*   Updated: 2022/07/22 16:42:46 by isabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_if_digit(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac < 5)
	{
		printf("Error: too few arguments\n");
		return (1);
	}
	while (i < ac)
	{
		if (!is_digit(av[i]))
		{
			printf("Error: argument %d is not a number\n", i + 1);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_arguments(int ac, char **av)
{
	int		i;
	int		res;

	i = 1;
	while (i < ac)
	{
		res = ft_atoi(av[i]);
		if (i == 1 && (res > 200 || res <= 0))
		{
			printf("Error: argument %d is not a valid number\n", i + 1);
			return (1);
		}
		else if (i != 1 && i != ac - 1 && res < 60)
		{
			printf("Error: argument %d is not a valid number\n", i + 1);
			return (1);
		}
		if (res < 0)
		{
			printf("Error: argument %d is not a valid number\n", i + 1);
			return (1);
		}
		i++;
	}
	return (0);
}
