```markdown
# Common Network Commands in Linux

## 1. ifconfig
`ifconfig` (interface configurator) command is used to initialize an interface, assign IP Address to the interface, and enable or disable the interface on demand. With this command, you can view the IP Address and Hardware/MAC address assigned to the interface and also the MTU (Maximum Transmission Unit) size.

## 2. PING Command
`PING` (Packet INternet Groper) command is the best way to test connectivity between two nodes, whether it is a Local Area Network (LAN) or Wide Area Network (WAN). Ping uses ICMP (Internet Control Message Protocol) to communicate with other devices. You can ping the hostname or IP address using the command below:
```sh
ping 4.2.2.2
# OR
ping www.tecmint.com
```

## 3. TRACEROUTE Command
`Traceroute` is a network troubleshooting utility that shows the number of hops taken to reach the destination and also determines the path packets travel. Below we are tracing the route to a global DNS server IP Address and are able to reach the destination, also showing the path the packet is traveling.
```sh
traceroute 4.2.2.2
```

## 4. NETSTAT Command
`Netstat` (Network Statistic) command displays connection info, routing table information, etc. To display routing table information, use the option `-r`.
```sh
netstat -r
```

## 5. DIG Command
`Dig` (domain information groper) queries DNS-related information like A Record, CNAME, MX Record, etc. This command is mainly used to troubleshoot DNS-related queries.
```sh
dig www.tecmint.com
# <<>> DiG 9.8.2rc1-RedHat-9.8.2-0.10.rc1.el6 <<>> www.tecmint.com
```

## 6. NSLOOKUP Command
`nslookup` command is also used to find out DNS-related queries. The following example shows the A Record (IP Address) of tecmint.com.
```sh
nslookup www.tecmint.com
```

## 7. ROUTE Command
`route` command shows and manipulates the IP routing table. To see the default routing table in Linux, type the following command:
```sh
route
```

## 8. HOST Command
`host` command is used to find name to IP or IP to name in IPv4 or IPv6 and also to query DNS records.
```sh
host www.google.com
```

## 9. ARP Command
`ARP` (Address Resolution Protocol) is useful to view/add the contents of the kernel’s ARP tables. To see the default table, use the command:
```sh
arp -e
```

## 10. ETHTOOL Command
`ethtool` is a replacement for `mii-tool`. It is used to view and set the speed and duplex of your Network Interface Card (NIC). You can set duplex permanently in `/etc/sysconfig/network-scripts/ifcfg-eth0` with the `ETHTOOL_OPTS` variable.
```sh
ethtool eth0
```

## 11. IWCONFIG Command
`iwconfig` command in Linux is used to configure a wireless network interface. You can see and set the basic Wi-Fi details like SSID, channel, and encryption. Refer to the man page of `iwconfig` to know more.
```sh
iwconfig [interface]
```

## 12. HOSTNAME Command
`hostname` is used to identify in a network. Execute the `hostname` command to see the hostname of your box. You can set the hostname permanently in `/etc/sysconfig/network`. You need to reboot the box once a proper hostname is set.
```sh
hostname
```

## 13. WHOIS Command
The `whois` command displays information about a website's record. You may get all the information about a website regarding its registration and owner's information.
```sh
whois <websiteName>
# Example:
whois google.com
```
```
