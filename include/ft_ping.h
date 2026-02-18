/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 14:14:10 by adeburea          #+#    #+#             */
/*   Updated: 2026/02/18 12:35:20 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PING_H
# define FT_PING_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <arpa/inet.h>
# include <sys/socket.h>
# include <netinet/ip_icmp.h>
# include <netdb.h>
# include <sys/time.h>

# define DEFAULT_PORT 80
# define PACKET_SIZE 64

typedef struct s_ft_ping
{
	
}	t_ft_ping;

unsigned short checksum(void *b, int len);

#endif