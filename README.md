# Commandes utiles
### Affiche les echanges ICMP
```sudo tshark -V -Y 'icmp'```
### Ignore les pings
```sudo iptables -A INPUT -p icmp --icmp-type echo-request -j DROP```
### Ne recoit jamais le retour de ping
```sudo iptables -A OUTPUT -p icmp -j DROP```
### Perte de paquets
```sudo tc qdisc add dev enp0s3 root netem loss 30%```
### Ajoute de la latence
```sudo tc qdisc add dev enp0s3 root netem delay 200ms```
### Reset traffic control
```sudo tc qdisc del dev enp0s3 root```

### Todo
- Envoyer 1 paquet
- Recevoir 1 réponse
- Ajouter RTT
- Ajouter boucle infinie
- Gérer CTRL+C
- Ajouter stats finales
- Ajouter options (-?, -v)

### Fonction utiles
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