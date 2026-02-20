/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   icmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 15:03:49 by adeburea          #+#    #+#             */
/*   Updated: 2026/02/20 13:53:40 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ping.h"

void build_packet(char *packet, int seq)
{
    struct icmphdr *icmp = (struct icmphdr *)packet;

    memset(packet, 0, PACKET_SIZE);

    icmp->type = ICMP_ECHO;
    icmp->code = 0;
    icmp->un.echo.id = getpid() & 0xFFFF;
    icmp->un.echo.sequence = seq;
    icmp->checksum = 0;

    icmp->checksum = checksum(packet, PACKET_SIZE);
}

int wait_for_reply(int sockfd, char *recv_packet)
{
    fd_set readfds;
    struct timeval timeout;

    FD_ZERO(&readfds);
    FD_SET(sockfd, &readfds);

    timeout.tv_sec = 1;
    timeout.tv_usec = 0;

    int ret = select(sockfd + 1, &readfds, NULL, NULL, &timeout);

    if (ret < 0)
    {
        if (errno == EINTR)
            return (-2);
        return (-1);
    }

    if (ret == 0)
        return (-1);

    while (1)
    {
        ssize_t size = recvfrom(sockfd, recv_packet, BUFFER_SIZE,
                                MSG_DONTWAIT, NULL, NULL);

        if (size <= 0)
            break;

        struct iphdr *ip = (struct iphdr *)recv_packet;

        if (ip->ihl < 5)
            continue;

        struct icmphdr *icmp =
            (struct icmphdr *)(recv_packet + ip->ihl * 4);

        if (icmp->type == ICMP_ECHOREPLY &&
            icmp->un.echo.id == (getpid() & 0xFFFF))
        {
            return (icmp->un.echo.sequence);
        }
    }

    return (-1);
}


