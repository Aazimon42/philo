/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 12:54:10 by edi-maio          #+#    #+#             */
/*   Updated: 2026/02/11 20:47:37 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_fork
{
	pthread_mutex_t	lock;
	int				valid_mutex;
}	t_fork;

typedef struct s_philo
{
	int				id;
	t_fork			*l_fork;
	t_fork			*r_fork;
	long			last_eat;
	pthread_mutex_t	lock_last;
	int				valid_last;
	int				times_ate;
	pthread_mutex_t	lock_ate;
	int				valid_ate;
	pthread_t		thread;
	struct s_table	*table;
}	t_philo;

typedef struct s_table
{
	t_philo			*philos;
	t_fork			*forks;
	pthread_t		monitor;
	int				running;
	pthread_mutex_t	lock_running;
	int				valid_running;
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_to_eat;
	long			start;
}	t_table;

typedef enum e_status
{
	DIED = 0,
	EATING = 1,
	SLEEPING = 2,
	THINKING = 3,
	L_FORK = 4,
	R_FORK = 4,
}	t_status;

int		ft_atoi(const char *str);
long	ft_atol(const char *str);
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_bzero(void *s, size_t n);
void	clear_table(t_table *table);
t_fork	*init_forks(t_table *table);
t_philo	*init_philos(t_table *table);
void	ft_parse(int ac, char **av, t_table *table);
long	get_time(void);
void	display_status(int status, t_philo *philo);
void	start_routine(t_table *table);
void	*monitor_routine(void *data);
void	ft_sleep(t_table *table, long duration);
int		check_running(t_table *table);

#endif
