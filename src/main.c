/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 12:50:01 by adeburea          #+#    #+#             */
/*   Updated: 2026/02/18 14:36:10 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ping.h"

int main(int argc, char *argv[])
{
	if (argc == 1) {
		printf("ft_ping: missing host operand\n");
		printf("Try 'ft_ping -?' for more information\n");
		return 64;
	}

	struct addrinfo hints = {0}, *res;
	hints.ai_family = AF_INET;

	if (getaddrinfo(argv[1], NULL, &hints, &res) != 0)
	{
		perror("getaddrinfo");
		return 1;
	}

	int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (sockfd < 0)
	{
		perror("socket");
		return 1;
	}

	char packet[PACKET_SIZE];
	struct icmphdr *icmp = (struct icmphdr *)packet;

	icmp->type = ICMP_ECHO;
	icmp->code = 0;
	icmp->un.echo.id = getpid();
	icmp->un.echo.sequence = 1;
	icmp->checksum = 0;
	icmp->checksum = checksum(packet, PACKET_SIZE);

	if (sendto(sockfd, packet, PACKET_SIZE, 0,
		res->ai_addr, res->ai_addrlen) <= 0)
	{
		perror("sendto");
		return 1;
	}

    char buff[1024];


// ssize_t sendto(int sockfd, const void *buf, size_t len, int flags,
//                const struct sockaddr *dest_addr, socklen_t addrlen);

// ssize_t recvfrom(int s, void *buf, size_t len, int flags,
//                  struct sockaddr *from, socklen_t *fromlen);

    int ret = recvfrom(sockfd, buff, PACKET_SIZE, 0, res->ai_addr, &res->ai_addrlen);



    printf("%d\n", ret);
    // printf(buff);

	printf("Ping sent\n");

	freeaddrinfo(res);
	close(sockfd);
	return 0;
}
