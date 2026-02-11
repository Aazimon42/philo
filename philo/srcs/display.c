/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:42:46 by edi-maio          #+#    #+#             */
/*   Updated: 2026/02/11 19:52:49 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((long)((t.tv_sec * 1000) + (t.tv_usec / 1000)));
}

void	display_status(int status, t_philo *philo)
{
	static char	*tab[] = {"%dl %d died\n",
		"%d %d is eating\n",
		"%d %d is sleeping\n",
		"%d %d is thinking\n",
		"%d %d has taken a fork\n"};

	pthread_mutex_lock(&philo->table->lock_running);
	if (philo->table->running)
		printf(tab[status], get_time(), philo->id);
	pthread_mutex_unlock(&philo->table->lock_running);
}
