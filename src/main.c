/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 12:50:01 by adeburea          #+#    #+#             */
/*   Updated: 2026/02/18 17:45:51 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ping.h"

double time_diff(struct timeval start, struct timeval end)
{
    double rtt = (end.tv_sec - start.tv_sec) * 1000.0;
    rtt += (end.tv_usec - start.tv_usec) / 1000.0;
    return rtt;
}

void build_packet(char *packet, int seq)
{
    struct icmphdr *icmp = (struct icmphdr *)packet;

    memset(packet, 0, PACKET_SIZE);

    icmp->type = ICMP_ECHO;
    icmp->code = 0;
    icmp->un.echo.id = getpid();
    icmp->un.echo.sequence = seq;
    icmp->checksum = 0;

    icmp->checksum = checksum(packet, PACKET_SIZE);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("ft_ping: missing host operand\n");
        return 1;
    }

    struct addrinfo hints = {0}, *res;
    hints.ai_family = AF_INET;

    if (getaddrinfo(argv[1], NULL, &hints, &res) != 0)
    {
        perror("getaddrinfo");
        return 1;
    }

    char ip_str[INET_ADDRSTRLEN];
    struct sockaddr_in *addr = (struct sockaddr_in *)res->ai_addr;
    inet_ntop(AF_INET, &addr->sin_addr, ip_str, sizeof(ip_str));

    printf("PING %s (%s): %d data bytes\n",
        argv[1], ip_str, DATA_SIZE);

    int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (sockfd < 0)
    {
        perror("socket");
        return 1;
    }

    struct timeval tv = {1, 0};
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

    int seq = 0;

    while (1)
    {
        char send_packet[PACKET_SIZE];
        char recv_packet[1024];
        struct timeval start, end;

        build_packet(send_packet, seq);

        gettimeofday(&start, NULL);

        if (sendto(sockfd, send_packet, PACKET_SIZE, 0,
                   res->ai_addr, res->ai_addrlen) <= 0)
        {
            perror("sendto");
            break;
        }

        while (1)
        {
            socklen_t addr_len = res->ai_addrlen;

            if (recvfrom(sockfd, recv_packet, sizeof(recv_packet), 0,
                        res->ai_addr, &addr_len) <= 0)
            {
                perror("recvfrom");
                break;
            }

            struct iphdr *ip = (struct iphdr *)recv_packet;
            struct icmphdr *icmp = (struct icmphdr *)
                (recv_packet + (ip->ihl * 4));

            if (icmp->type == ICMP_ECHOREPLY &&
                icmp->un.echo.id == getpid() &&
                icmp->un.echo.sequence == seq)
            {
                break;
            }
        }

        gettimeofday(&end, NULL);

        struct iphdr *ip = (struct iphdr *)recv_packet;
        struct icmphdr *icmp = (struct icmphdr *)
            (recv_packet + (ip->ihl * 4));

        if (icmp->type == ICMP_ECHOREPLY &&
            icmp->un.echo.id == getpid())
        {
            double rtt = time_diff(start, end);

            printf("%d bytes from %s: icmp_seq=%d ttl=%d time=%.3f ms\n",
                PACKET_SIZE,
                ip_str,
                seq,
                ip->ttl,
                rtt);
        }

        seq++;
        sleep(1);
    }

    freeaddrinfo(res);
    close(sockfd);
    return 0;
}
