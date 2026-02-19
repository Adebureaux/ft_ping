/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 16:46:54 by adeburea          #+#    #+#             */
/*   Updated: 2026/02/19 16:51:14 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ping.h"

void print_ping_header(char *host, char *ip_str)
{
    printf("PING %s (%s): %d data bytes\n",
        host,
        ip_str,
        DATA_SIZE);
}

