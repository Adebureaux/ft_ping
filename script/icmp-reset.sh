#!/bin/bash

IFACE="enp0s3"

sudo tc qdisc del dev $IFACE root 2>/dev/null

echo "ICMP back to normal."
