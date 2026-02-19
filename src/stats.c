/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 17:52:09 by adeburea          #+#    #+#             */
/*   Updated: 2026/02/19 17:53:39 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ping.h"

void init_stats(t_stats *stats)
{
    stats->transmitted = 0;
    stats->received = 0;
    stats->min_rtt = 0;
    stats->max_rtt = 0;
    stats->total_rtt = 0;
    stats->total_rtt_sq = 0;
}

void update_stats(t_stats *stats, double rtt)
{
    if (stats->received == 0)
    {
        stats->min_rtt = rtt;
        stats->max_rtt = rtt;
    }
    else
    {
        if (rtt < stats->min_rtt)
            stats->min_rtt = rtt;
        if (rtt > stats->max_rtt)
            stats->max_rtt = rtt;
    }

    stats->total_rtt += rtt;
    stats->total_rtt_sq += rtt * rtt;
    stats->received++;
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