/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 14:14:10 by adeburea          #+#    #+#             */
/*   Updated: 2026/02/17 16:01:59 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PING_H
# define FT_PING_H
# include <arpa/inet.h>
# include <stdio.h>
# include <string.h>
# include <sys/socket.h>
# include <unistd.h>
#define DEFAULT_PORT 8080

// htons()/ntohs(), htonl()/ntohl(), recvfrom (), sendto () & setsockopt ()
// getaddrinfo (), perror (), struct sockaddr_in, struct icmp & struct ip

typedef struct s_ft_ping
{
    
}   t_pip;

#endif