/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:23:26 by edi-maio          #+#    #+#             */
/*   Updated: 2026/02/23 14:19:59 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	test_values(char **av)
{
	if (ft_atol(av[1]) > 200 || ft_atol(av[1]) <= 0)
		return (0);
	if (ft_atol(av[2]) > 2147483647 || ft_atol(av[2]) <= 0)
		return (0);
	if (ft_atol(av[3]) > 2147483647 || ft_atol(av[3]) <= 0)
		return (0);
	if (ft_atol(av[4]) > 2147483647 || ft_atol(av[4]) <= 0)
		return (0);
	if (av[5] && (ft_atol(av[5]) > 2147483647 || ft_atol(av[5]) <= 0))
		return (0);
	return (1);
}

void	ft_parse(int ac, char **av, t_table *table)
{
	if (!test_values(av))
	{
		free(table);
		exit(0);
	}
	table->nb_philo = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	table->start = get_time();
	table->forks = init_forks(table);
	table->running = 1;
	table->valid_running = pthread_mutex_init(&(table->lock_running), NULL);
	table->valid_start = pthread_mutex_init(&(table->lock_start), NULL);
	if (!table->forks || table->valid_running || table->valid_start)
		clear_table(table);
	table->philos = init_philos(table);
	if (!table->philos)
		clear_table(table);
	table->nb_to_eat = -1;
	if (ac == 6)
		table->nb_to_eat = ft_atoi(av[5]);
}
