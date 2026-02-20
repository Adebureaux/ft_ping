/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 16:46:54 by adeburea          #+#    #+#             */
/*   Updated: 2026/02/20 15:55:48 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ping.h"

void print_usage(void)
{
    printf("Usage: ft_ping [OPTION...] HOST\n");
    printf("Options:\n");
    printf("  -v     verbose output\n");
    printf("  -?     display this help and exit\n");
}

void print_ping_header(char *host, char *ip_str, int v)
{
    if (v)
    {
        printf("PING %s (%s): %d data bytes, id 0x%x = %d\n",
               host,
               ip_str,
               DATA_SIZE,
               getpid() & 0xFFFF,
               getpid() & 0xFFFF);
    }
    else
    {
        printf("PING %s (%s): %d data bytes\n",
               host,
               ip_str,
               DATA_SIZE);
    }
}

void print_ping(int size, char *ip_str, int seq, uint8_t ttl, double rtt)
{
    printf("%d bytes from %s: icmp_seq=%d ttl=%d time=%.3f ms\n",
        size,
        ip_str,
        seq,
        ttl,
        rtt);
}

void print_stats(t_stats *stats, char *host)
{
    double loss = 0;
    double avg = 0;
    double stddev = 0;

    if (stats->transmitted > 0)
        loss = ((stats->transmitted - stats->received) * 100.0)
                / stats->transmitted;

    if (stats->received > 0)
    {
        avg = stats->total_rtt / stats->received;
        stddev = sqrt((stats->total_rtt_sq / stats->received)
                    - (avg * avg));
    }

    printf("\n--- %s ping statistics ---\n", host);
    printf("%d packets transmitted, %d packets received, %.0f%% packet loss\n",
        stats->transmitted,
        stats->received,
        loss);

    if (stats->received > 0)
    {
        printf("round-trip min/avg/max/stddev = %.3f/%.3f/%.3f/%.3f ms\n",
            stats->min_rtt,
            avg,
            stats->max_rtt,
            stddev);
    }
}

