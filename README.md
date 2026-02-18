## Commandes utiles
### Affiche les echanges ICMP
```sudo tshark -V -Y 'icmp'```
### Ignore les pings
```sudo iptables -A INPUT -p icmp --icmp-type echo-request -j DROP```
### Ne recoit jamais le retour de ping
```sudo iptables -A OUTPUT -p icmp -j DROP```
### Perte de paquets
```sudo tc qdisc add dev enp0s3 root netem loss 5%```
### Ajoute de la latence
```sudo tc qdisc add dev enp0s3 root netem delay 200ms```

## Todo
- Ajouter SO_RCVTIMEO (timeout)
- Gérer le ttl
- Gérer Ctrl+C
- Gérer packet loss
- Afficher stats finales : calculer min/avg/max
- Ajouter options (-?, -v)

## Fonction utiles
- getpid
- getuid
- getaddrinfo
- gettimeofday
- inet_ntop
- inet_pton
- exit
- signal
- alarm
- setsockopt
- recvmsg
- sendto
- socket

## Structure
src/
    main.c
    socket.c
    icmp.c
    checksum.c
    time.c
    parse.c
include/
    ft_ping.h
Makefile
README.md
