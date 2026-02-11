/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:36:47 by edi-maio          #+#    #+#             */
/*   Updated: 2026/02/11 20:39:37 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_running(t_table *table)
{
	int	running;

	pthread_mutex_lock(&table->lock_running);
	running = table->running;
	pthread_mutex_unlock(&table->lock_running);
	return (running);
}

void	routine_think(t_philo *philo)
{
	long	time_to_think;

	pthread_mutex_lock(&philo->lock_last);
	time_to_think = philo->table->time_to_die
		- (get_time() - philo->last_eat) - philo->table->time_to_eat;
	pthread_mutex_unlock(&philo->lock_last);
	display_status(THINKING, philo);
	ft_sleep(philo->table, time_to_think);
}

void	routine_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->l_fork->lock);
	display_status(L_FORK, philo);
	pthread_mutex_lock(&philo->r_fork->lock);
	display_status(R_FORK, philo);
	display_status(EATING, philo);
	pthread_mutex_lock(&philo->lock_last);
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->lock_last);
	pthread_mutex_lock(&philo->lock_ate);
	philo->times_ate++;
	pthread_mutex_unlock(&philo->lock_ate);
	ft_sleep(philo->table, philo->table->time_to_eat);
	display_status(SLEEPING, philo);
	pthread_mutex_unlock(&philo->l_fork->lock);
	pthread_mutex_unlock(&philo->r_fork->lock);
	ft_sleep(philo->table, philo->table->time_to_sleep);
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	pthread_mutex_lock(&philo->lock_last);
	philo->last_eat = philo->table->start;
	pthread_mutex_unlock(&philo->lock_last);
	if (philo->table->nb_philo == 1)
	{
		pthread_mutex_lock(&philo->l_fork->lock);
		display_status(L_FORK, philo);
		ft_sleep(philo->table, philo->table->time_to_die + 10);
		pthread_mutex_unlock(&philo->l_fork->lock);
		return (0);
	}
	if (philo->id % 2)
		usleep(1000);
	while (check_running(philo->table))
	{
		routine_eat(philo);
		if (!check_running(philo->table))
			break ;
		routine_think(philo);
	}
	return (0);
}

void	start_routine(t_table *table)
{
	int	i;

	i = 0;
	pthread_create(&(table->monitor), NULL, monitor_routine, table);
	while (i < table->nb_philo)
	{
		pthread_create(&table->philos[i].thread,
			NULL, routine, &table->philos[i]);
		i++;
	}
}
