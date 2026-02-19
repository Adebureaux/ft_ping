/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 14:25:20 by adeburea          #+#    #+#             */
/*   Updated: 2026/02/19 17:01:29 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ping.h"

double time_diff(struct timeval start, struct timeval end)
{
    double rtt = (end.tv_sec - start.tv_sec) * 1000.0;
    rtt += (end.tv_usec - start.tv_usec) / 1000.0;
    return (rtt);
}