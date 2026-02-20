/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 14:14:10 by adeburea          #+#    #+#             */
/*   Updated: 2026/02/20 15:55:23 by adeburea         ###   ########.fr       */
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
# include <signal.h>
# include <errno.h>
# include <math.h>
# include <time.h>

# define PACKET_SIZE 64
# define DATA_SIZE 56
# define BUFFER_SIZE 1024

extern volatile sig_atomic_t g_running;

typedef struct s_stats
{
    int     transmitted;
    int     received;
    double  min_rtt;
    double  max_rtt;
    double  total_rtt;
    double  total_rtt_sq;
}   t_stats;

void            init_signals(void);
void            init_stats(t_stats *stats);
void            update_stats(t_stats *stats, double rtt);
int             create_socket(void);
int             resolve_host(char *host, struct addrinfo **res, char *ip_str);
void            print_usage(void);
void            print_ping_header(char *host, char *ip_str, int v);
void            print_ping(int size, char *ip_str, int seq, uint8_t ttl, double rtt);
void            print_stats(t_stats *stats, char *host);
unsigned short  checksum(void *b, int len);
void            build_packet(char *packet, int seq);
int             wait_for_reply(int sockfd, char *recv_packet);
void            ping_loop(int sockfd, struct addrinfo *res, char *ip_str, char *host);

#endif