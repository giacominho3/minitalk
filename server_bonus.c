/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gifulvi <gifulvi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 14:21:16 by gifulvi           #+#    #+#             */
/*   Updated: 2022/09/01 15:35:45 by gifulvi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./lib.h"

void	ft_acknowledgement(pid_t cpid)
{
	usleep(1000);
	kill(cpid, SIGUSR2);
}

void	ft_printer(int num, pid_t cpid)
{
	write(1, &num, 1);
	if (num == 0)
		ft_acknowledgement(cpid);
}

void	ft_signal(int sg, siginfo_t *si, void *cont)
{
	static int	num;
	static int	counter;
	pid_t		cpid;

	cpid = si->si_pid;
	if (cont)
		;
	if (counter < 8)
	{
		num *= 2;
		if (sg == SIGUSR1)
			num += 1;
		if (counter == 7)
			ft_printer(num, cpid);
	}
	else
	{
		num = 0;
		if (sg == SIGUSR1)
			num = 1;
		counter = 0;
	}
	counter++;
}

int	main(void)
{
	struct sigaction	s_sa;
	int					pid;

	pid = getpid();
	memset(&s_sa, 0, sizeof(s_sa));
	write(1, "Il PID del processo server: ", 29);
	ft_putnbr(pid);
	write(1, "\n", 1);
	s_sa.sa_flags = SA_SIGINFO;
	s_sa.sa_sigaction = ft_signal;
	sigaction(SIGUSR1, &s_sa, 0);
	sigaction(SIGUSR2, &s_sa, 0);
	while (1)
		pause();
}
