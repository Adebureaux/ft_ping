#!/bin/bash

IFACE=${IFACE:-"enp0s3"}
LOSS=${LOSS:-"30"}
DELAY=${DELAY:-"100ms"}
JITTER=${JITTER:-"20ms"}

sudo tc qdisc del dev $IFACE root 2>/dev/null
sudo iptables -t mangle -F OUTPUT

sudo iptables -t mangle -A OUTPUT -p icmp --icmp-type echo-request -j MARK --set-mark 1
sudo iptables -t mangle -A OUTPUT -p icmp --icmp-type echo-reply -j MARK --set-mark 1

sudo tc qdisc add dev $IFACE root handle 1: prio

sudo tc qdisc add dev $IFACE parent 1:3 handle 30: netem loss ${LOSS}% delay ${DELAY} ${JITTER} limit 1000

sudo tc filter add dev $IFACE parent 1:0 protocol ip prio 3 handle 1 fw flowid 1:3

echo "ICMP network emulation active."
