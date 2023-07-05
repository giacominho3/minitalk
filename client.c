/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gifulvi <gifulvi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 14:46:58 by gifulvi           #+#    #+#             */
/*   Updated: 2022/09/05 14:58:46 by gifulvi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./lib.h"

int	*char_to_binary(char c)
{
	int		*line;
	int		i;

	line = malloc(8 * sizeof(int));
	i = 7;
	while (i >= 0)
	{
		line[7 - i] = (c >> i) & 1;
		i--;
	}
	return (line);
}

void	pass_message(int **mat, int pid, int len)
{
	int	i;
	int	j;

	i = 0;
	while (i <= len)
	{
		j = 0;
		while (j < 8)
		{
			if (mat[i][j] == 1)
				kill(pid, SIGUSR1);
			else if (mat[i][j] == 0)
				kill(pid, SIGUSR2);
			usleep(100);
			j++;
		}
		i++;
	}
}

void	fill_matrix(int **mat, char *str, int len)
{
	int	i;

	i = 0;
	while (i <= len)
	{
		mat[i] = char_to_binary(str[i]);
		i++;
	}
}

void	ft_received(int sg, siginfo_t *si, void *cont)
{
	if (cont)
		;
	if (si)
		;
	if (sg == SIGUSR2)
		exit(0);
}

int	main(int argc, char **argv)
{
	char				*str;
	int					**mat;
	int					len;
	struct sigaction	s_rec;

	if (argc != 3)
		return (write(2, "ERROR\n", 7));
	memset(&s_rec, 0, sizeof(s_rec));
	write (1, "Il PID passato: ", 17);
	ft_putnbr(ft_atoi(argv[1]));
	write (1, "\n", 1);
	str = argv[2];
	len = ft_strlen(str);
	mat = (int **)malloc((len + 1) * sizeof(int *));
	fill_matrix(mat, str, len);
	pass_message(mat, ft_atoi(argv[1]), len);
	while (len > -1)
		free(mat[len--]);
	free(mat);
	s_rec.sa_flags = SA_SIGINFO;
	s_rec.sa_sigaction = &ft_received;
	sigaction(SIGUSR2, &s_rec, 0);
	while (1)
		pause();
}
