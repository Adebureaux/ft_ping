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
- Ajouter options (-?, -v, -f, -ttl)
