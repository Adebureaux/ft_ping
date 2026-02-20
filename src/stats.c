/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 17:52:09 by adeburea          #+#    #+#             */
/*   Updated: 2026/02/20 11:38:57 by adeburea         ###   ########.fr       */
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