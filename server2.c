/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-04-16 13:22:30 by user              #+#    #+#             */
/*   Updated: 2024-04-16 13:22:30 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <signal.h>
#include <unistd.h>

void	ft_putnbr_recursive(int nb)
{
	char	digit;

	if (nb / 10 != 0)
	{
		ft_putnbr_recursive(nb / 10);
	}
	digit = (nb % 10) + '0';
	write(1, &digit, 1);
}

void    handler(int signal)
{
    static unsigned char    binary_rep = 0;
    static unsigned int     received = 0;

    if (signal == SIGUSR1)
        binary_rep = (binary_rep << 1) | 1;
    else if (signal == SIGUSR2)
        binary_rep = binary_rep << 1;
    received++;
    if (received == 8)
    {
        write(1, &binary_rep, 1);
        binary_rep = 0;
        received = 0;
    }
}

int	main(void)
{
    struct sigaction sa;

    sa.sa_handler = handler;
    sa.sa_flags = SA_RESTART;
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGUSR1, &sa, NULL) == -1)
        return (1);
    if (sigaction(SIGUSR2, &sa, NULL) == -1)    
        return (1);
    ft_putnbr_recursive(getpid());
	write(1, "\n", 1);
	while (1)
		pause();
	return (0);
}