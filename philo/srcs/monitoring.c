/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:37:05 by edi-maio          #+#    #+#             */
/*   Updated: 2026/02/11 20:46:41 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_sleep(t_table *table, long duration)
{
	long	start;

	start = get_time();
	while (get_time() - start < duration)
	{
		if (!check_running(table))
			return ;
		usleep(100);
	}
}

int	check_eat(t_table *table)
{
	int	i;

	i = 0;
	if (table->nb_to_eat < 0)
		return (0);
	while (i < table->nb_philo)
	{
		pthread_mutex_lock(&table->philos[i].lock_ate);
		if (table->philos[i].times_ate < table->nb_to_eat)
		{
			pthread_mutex_unlock(&table->philos[i].lock_ate);
			return (0);
		}
		pthread_mutex_unlock(&table->philos[i].lock_ate);
		i++;
	}
	return (1);
}

int	check_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		pthread_mutex_lock(&table->philos[i].lock_last);
		if (get_time() >= table->philos[i].last_eat + table->time_to_die)
		{
			pthread_mutex_unlock(&table->philos[i].lock_last);
			display_status(0, &table->philos[i]);
			return (0);
		}
		pthread_mutex_unlock(&table->philos[i].lock_last);
		i++;
	}
	return (1);
}

void	*monitor_routine(void *data)
{
	t_table	*table;

	table = (t_table *) data;
	while (1)
	{
		if (!check_philos(table) || check_eat(table))
		{
			pthread_mutex_lock(&table->lock_running);
			table->running = 0;
			pthread_mutex_unlock(&table->lock_running);
			return (0);
		}
		usleep(100);
	}
	return (0);
}
