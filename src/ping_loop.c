/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 16:46:30 by adeburea          #+#    #+#             */
/*   Updated: 2026/02/19 18:15:50 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ping.h"

void ping_loop(int sockfd, struct addrinfo *res, char *ip_str, char *host)
{
    int seq = 0;
    t_stats stats;

    init_stats(&stats);

    while (g_running)
    {
        char send_packet[PACKET_SIZE];
        char recv_packet[BUFFER_SIZE];
        struct timeval start, end;

        build_packet(send_packet, seq);

        stats.transmitted++;

        gettimeofday(&start, NULL);

        if (sendto(sockfd, send_packet, PACKET_SIZE, 0,
                res->ai_addr, res->ai_addrlen) <= 0)
        {
            perror("sendto");
            break;
        }

        int status = wait_for_reply(sockfd, seq, recv_packet);

        if (status == -2)
            break;

        if (status == 0)
        {
            gettimeofday(&end, NULL);

            struct iphdr *ip = (struct iphdr *)recv_packet;
            if (ip->ihl >= 5)
            {
                double rtt = time_diff(start, end);

                update_stats(&stats, rtt);

                printf("%d bytes from %s: icmp_seq=%d ttl=%d time=%.3f ms\n",
                    PACKET_SIZE,
                    ip_str,
                    seq,
                    ip->ttl,
                    rtt);
            }
        }

        seq++;
        sleep(1);
    }

    print_stats(&stats, host);
}

