/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-04-16 11:08:03 by user              #+#    #+#             */
/*   Updated: 2024-04-16 11:08:03 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>

int	ft_atoi(const char *str)
{
	int	sign;
	int	result;

	sign = 1;
	result = 0;
	while (*str == 32 || (8 < *str && *str < 14))
		str++;
	if ((*str == '+' || *str == '-') && (*(str + 1)))
	{
		if (*str == '-')
			sign = sign * -1;
		str++;
	}
	while (*str)
	{
		if (*str >= 48 && *str <= 57)
		{
			result = result * 10 + (*str - 48);
			str++;
		}
		else
			break ;
	}
	return (result * sign);
}

void	ft_send( int server_pid, char *msg)
{
	int             i;
    char            c;
    unsigned int    bit;

    while (*msg)
    {
        c = *msg;
        i = 0;
        while (i <= 7 && i >= 0)
    	{

        	bit = ((c >>(7 - i)) & 1);
        	if (bit == 1)
				kill(server_pid, SIGUSR1);
			else
				kill(server_pid, SIGUSR2);
			usleep(100);
        	i++;
    	}
		msg++;
	}

}

int	main(int argc, char **argv)
{
	int	server_pid;
	int	i;

	i = 2;
	server_pid = ft_atoi(argv[1]);
	while (i < argc)
	{
		ft_send(server_pid, argv[i]);
		if (i < argc -1)
			ft_send(server_pid, " ");
		i++;
		if (i == argc)
			ft_send(server_pid, "\n");
	}
	return (0);
}
