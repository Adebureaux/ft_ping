/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 12:50:01 by adeburea          #+#    #+#             */
/*   Updated: 2026/02/17 18:33:16 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

unsigned short checksum(void *b, int len)
{
	unsigned short *buf = b;
	unsigned int sum = 0;
	unsigned short result;

	for (sum = 0; len > 1; len -= 2)
		sum += *buf++;
	if (len == 1)
		sum += *(unsigned char*)buf;
	sum = (sum >> 16) + (sum & 0xFFFF);
	sum += (sum >> 16);
	result = ~sum;
	return result;
}

int main(int argc, char **argv)
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

	printf("Ping sent\n");

	freeaddrinfo(res);
	close(sockfd);
	return 0;
}
