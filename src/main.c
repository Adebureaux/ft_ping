/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 12:50:01 by adeburea          #+#    #+#             */
/*   Updated: 2026/02/19 18:15:36 by adeburea         ###   ########.fr       */
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

    struct addrinfo *res;
    char ip_str[INET_ADDRSTRLEN];

    if (resolve_host(argv[1], &res, ip_str) < 0)
        return (-1);

    print_ping_header(argv[1], ip_str);

    int sockfd = create_socket();
    if (sockfd < 0)
        return (-1);

    init_signals();

    ping_loop(sockfd, res, ip_str, argv[1]);

    freeaddrinfo(res);
    close(sockfd);
    return (0);
}

