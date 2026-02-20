/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 12:50:01 by adeburea          #+#    #+#             */
/*   Updated: 2026/02/20 16:06:07 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ping.h"


int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("ft_ping: missing host operand\n");
        return (-1);
    }

    char *host = NULL;
    int verbose = 0;

    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] != '-')
        {
            host = argv[i];
            break;
        }

        if (strcmp(argv[i], "-v") == 0)
        {
            verbose = 1;
        }
        else if (strcmp(argv[i], "-?") == 0)
        {
            print_usage();
            return (0);
        }
        else
        {
            printf("ft_ping: invalid option '%s'\n", argv[i]);
            return (-1);
        }
    }

    if (!host)
    {
        printf("ft_ping: missing host operand\n");
        return (-1);
    }

    struct addrinfo *res;
    char ip_str[INET_ADDRSTRLEN];

    if (resolve_host(host, &res, ip_str) < 0)
        return (-1);

    print_ping_header(host, ip_str, verbose);

    int sockfd = create_socket();
    if (sockfd < 0)
    {
        freeaddrinfo(res);
        return (-1);
    }

    init_signals();

    ping_loop(sockfd, res, ip_str, host);

    freeaddrinfo(res);
    close(sockfd);

    return (0);
}
