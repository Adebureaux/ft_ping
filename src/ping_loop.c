/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 16:46:30 by adeburea          #+#    #+#             */
/*   Updated: 2026/02/20 16:04:51 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ping.h"

int send_loop(int sockfd,
              struct addrinfo *res,
              int *seq,
              struct timespec *send_times,
              struct timespec *next_send,
              t_stats *stats)
{
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);

    if ((now.tv_sec > next_send->tv_sec) ||
        (now.tv_sec == next_send->tv_sec &&
         now.tv_nsec >= next_send->tv_nsec))
    {
        char send_packet[PACKET_SIZE];
        build_packet(send_packet, *seq);

        ssize_t ret = sendto(sockfd, send_packet, PACKET_SIZE, 0,
                            res->ai_addr, res->ai_addrlen);

        if (ret <= 0)
        {
            perror("ft_ping: sending packet: ");
            g_running = 0;
            return (-1);
        }
        else
        {
            clock_gettime(CLOCK_MONOTONIC,
                        &send_times[*seq % 1024]);

            stats->transmitted++;
            (*seq)++;
        }

        next_send->tv_sec += 1;
        return (1);
    }

    return (0);
}

void recv_loop(int sockfd,
               struct timespec *next_send,
               struct timespec *send_times,
               t_stats *stats,
               char *ip_str)
{
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);

    long sec_diff = next_send->tv_sec - now.tv_sec;
    long nsec_diff = next_send->tv_nsec - now.tv_nsec;

    if (nsec_diff < 0)
    {
        sec_diff--;
        nsec_diff += 1000000000L;
    }

    if (sec_diff < 0)
    {
        sec_diff = 0;
        nsec_diff = 0;
    }

    struct timeval timeout;
    timeout.tv_sec = sec_diff;
    timeout.tv_usec = nsec_diff / 1000;

    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(sockfd, &readfds);

    int ret = select(sockfd + 1, &readfds,
                     NULL, NULL, &timeout);

    if (ret <= 0)
        return;

    if (!FD_ISSET(sockfd, &readfds))
        return;

    while (1)
    {
        struct sockaddr_in addr;
        socklen_t addrlen = sizeof(addr);
        char recv_packet[BUFFER_SIZE];

        ssize_t size = recvfrom(sockfd, recv_packet, BUFFER_SIZE,
         MSG_DONTWAIT,
         (struct sockaddr *)&addr, &addrlen);

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
            int reply_seq = icmp->un.echo.sequence;

            struct timespec sent =
                send_times[reply_seq % 1024];

            struct timespec recv_time;
            clock_gettime(CLOCK_MONOTONIC,
                          &recv_time);

            double rtt =
                (recv_time.tv_sec - sent.tv_sec) * 1000.0;

            rtt += (recv_time.tv_nsec -
                    sent.tv_nsec) / 1e6;

            update_stats(stats, rtt);

            print_ping(PACKET_SIZE,
                       ip_str,
                       reply_seq,
                       ip->ttl,
                       rtt);
        }
        else if (icmp->type == ICMP_DEST_UNREACH)
        {
            ssize_t icmp_size = size - ip->ihl * 4;
            printf("%zd bytes from %s: Destination Net Unreachable\n",
                   icmp_size, inet_ntoa(*(struct in_addr *)&ip->saddr));
        }
    }
}

void ping_loop(int sockfd,
               struct addrinfo *res,
               char *ip_str,
               char *host)
{
    int seq = 0;
    t_stats stats;
    struct timespec send_times[1024];
    struct timespec next_send;

    init_stats(&stats);
    memset(send_times, 0, sizeof(send_times));

    clock_gettime(CLOCK_MONOTONIC, &next_send);

    while (g_running)
    {
        send_loop(sockfd,
                  res,
                  &seq,
                  send_times,
                  &next_send,
                  &stats);

        recv_loop(sockfd,
                  &next_send,
                  send_times,
                  &stats,
                  ip_str);
    }

    if (stats.transmitted > 0)
    {
        print_stats(&stats, host);
    }
}

