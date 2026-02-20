/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 16:08:05 by adeburea          #+#    #+#             */
/*   Updated: 2026/02/20 13:52:17 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ping.h"

int create_socket(void)
{
    int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (sockfd < 0)
    {
        perror("socket");
        return (-1);
    }

    int broadcast = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST,
                   &broadcast, sizeof(broadcast)) < 0)
    {
        perror("setsockopt SO_BROADCAST");
        close(sockfd);
        return (-1);
    }

    return sockfd;
}

int resolve_host(char *host, struct addrinfo **res, char *ip_str)
{
    struct addrinfo hints;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_RAW;
    hints.ai_protocol = IPPROTO_ICMP;

    if (getaddrinfo(host, NULL, &hints, res) != 0)
    {
        fprintf(stderr, "ft_ping: unknown host\n");
        return (-1);
    }

    struct sockaddr_in *addr = (struct sockaddr_in *)(*res)->ai_addr;

    if (!inet_ntop(AF_INET, &addr->sin_addr, ip_str, INET_ADDRSTRLEN))
    {
        perror("inet_ntop");
        freeaddrinfo(*res);
        return (-1);
    }

    return (0);
}

