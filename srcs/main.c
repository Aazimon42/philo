/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 12:54:29 by edi-maio          #+#    #+#             */
/*   Updated: 2026/02/23 14:15:11 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	join_threads(t_table *table)
{
	int	i;

	i = 0;
	pthread_join(table->monitor, NULL);
	while (i < table->nb_philo)
	{
		pthread_join(table->philos[i].thread, NULL);
		i++;
	}
}

void	clear_table(t_table *table)
{
	int	i;

	i = 0;
	if (table->forks)
	{
		while (i < table->nb_philo && table->forks->valid_mutex)
			pthread_mutex_destroy(&table->forks[i++].lock);
		free(table->forks);
	}
	i = 0;
	if (table->philos)
	{
		while (i < table->nb_philo)
		{
			pthread_mutex_destroy(&table->philos[i].lock_ate);
			pthread_mutex_destroy(&table->philos[i].lock_last);
			i++;
		}
		free(table->philos);
	}
	if (table->valid_running)
		pthread_mutex_destroy(&table->lock_running);
	if (table->valid_start)
		pthread_mutex_destroy(&table->lock_start);
	free(table);
}

t_fork	*init_forks(t_table *table)
{
	t_fork	*forks;
	int		i;

	i = 0;
	forks = ft_calloc(sizeof(t_fork), table->nb_philo);
	if (!forks)
		return (0);
	while (i < table->nb_philo)
	{
		forks[i].valid_mutex = pthread_mutex_init(&(forks[i].lock), NULL);
		if (forks[i].valid_mutex != 0)
			return (0);
		i++;
	}
	return (forks);
}

t_philo	*init_philos(t_table *table)
{
	t_philo	*philos;
	int		i;

	i = 0;
	philos = ft_calloc(sizeof(t_philo), table->nb_philo);
	if (!philos)
		return (0);
	while (i < table->nb_philo)
	{
		philos[i].table = table;
		philos[i].id = i + 1;
		philos[i].l_fork = &(table->forks[i]);
		philos[i].r_fork = &(table->forks[(i + 1) % table->nb_philo]);
		philos[i].last_eat = table->start;
		philos[i].valid_last = pthread_mutex_init(&(philos[i].lock_last), NULL);
		philos[i].valid_ate = pthread_mutex_init(&(philos[i].lock_ate), NULL);
		if (philos[i].valid_last || philos[i].valid_ate)
			return (0);
		i++;
	}
	return (philos);
}

int	main(int ac, char **av)
{
	t_table	*table;

	if (!(ac == 5 || ac == 6))
		return (0);
	table = malloc(sizeof(t_table));
	if (!table)
		return (0);
	ft_parse(ac, av, table);
	start_routine(table);
	join_threads(table);
	clear_table(table);
}
