bogdan@bogdanbuilds:~$ ip link show
1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN mode DEFAULT group default qlen 1000
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
2: enp129s0: <NO-CARRIER,BROADCAST,MULTICAST,UP> mtu 1500 qdisc mq state DOWN mode DEFAULT group default qlen 1000
    link/ether c8:53:09:ae:ca:47 brd ff:ff:ff:ff:ff:ff
3: wlp130s0f0: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc noqueue state UP mode DORMANT group default qlen 1000
    link/ether 24:eb:16:9d:d4:79 brd ff:ff:ff:ff:ff:ff
4: docker0: <NO-CARRIER,BROADCAST,MULTICAST,UP> mtu 1500 qdisc noqueue state DOWN mode DEFAULT group default 
    link/ether de:b7:11:e7:1c:ed brd ff:ff:ff:ff:ff:ff


ip link show -> Mac adresses
ip addr -> Adressele IP

inet - ipv4, inet6 - ipv6

bogdan@bogdanbuilds:~$ ip addr show
1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN group default qlen 1000
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
    inet 127.0.0.1/8 scope host lo
       valid_lft forever preferred_lft forever
    inet6 ::1/128 scope host noprefixroute 
       valid_lft forever preferred_lft forever
2: enp129s0: <NO-CARRIER,BROADCAST,MULTICAST,UP> mtu 1500 qdisc mq state DOWN group default qlen 1000
    link/ether c8:53:09:ae:ca:47 brd ff:ff:ff:ff:ff:ff
3: wlp130s0f0: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc noqueue state UP group default qlen 1000
    link/ether 24:eb:16:9d:d4:79 brd ff:ff:ff:ff:ff:ff
    inet 172.20.10.2/28 brd 172.20.10.15 scope global dynamic noprefixroute wlp130s0f0
       valid_lft 2853sec preferred_lft 2853sec
    inet6 fe80::47a1:82e3:ac6f:435c/64 scope link noprefixroute 
       valid_lft forever preferred_lft forever
4: docker0: <NO-CARRIER,BROADCAST,MULTICAST,UP> mtu 1500 qdisc noqueue state DOWN group default 
    link/ether de:b7:11:e7:1c:ed brd ff:ff:ff:ff:ff:ff
    inet 172.17.0.1/16 brd 172.17.255.255 scope global docker0
       valid_lft forever preferred_lft forever
bogdan@bogdanbuilds:~$ 



192 - home

0.0.0.0 - for hosting

127 - loopback (Localhost)




bogdan@bogdanbuilds:~$ ip link show
1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN mode DEFAULT group default qlen 1000
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
2: enp129s0: <NO-CARRIER,BROADCAST,MULTICAST,UP> mtu 1500 qdisc mq state DOWN mode DEFAULT group default qlen 1000
    link/ether c8:53:09:ae:ca:47 brd ff:ff:ff:ff:ff:ff
3: wlp130s0f0: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc noqueue state UP mode DORMANT group default qlen 1000
    link/ether 24:eb:16:9d:d4:79 brd ff:ff:ff:ff:ff:ff
4: docker0: <NO-CARRIER,BROADCAST,MULTICAST,UP> mtu 1500 qdisc noqueue state DOWN mode DEFAULT group default 
    link/ether de:b7:11:e7:1c:ed brd ff:ff:ff:ff:ff:ff
bogdan@bogdanbuilds:~$ ip addr show
1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN group default qlen 1000
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
    inet 127.0.0.1/8 scope host lo
       valid_lft forever preferred_lft forever
    inet6 ::1/128 scope host noprefixroute 
       valid_lft forever preferred_lft forever
2: enp129s0: <NO-CARRIER,BROADCAST,MULTICAST,UP> mtu 1500 qdisc mq state DOWN group default qlen 1000
    link/ether c8:53:09:ae:ca:47 brd ff:ff:ff:ff:ff:ff
3: wlp130s0f0: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc noqueue state UP group default qlen 1000
    link/ether 24:eb:16:9d:d4:79 brd ff:ff:ff:ff:ff:ff
    inet 172.20.10.2/28 brd 172.20.10.15 scope global dynamic noprefixroute wlp130s0f0
       valid_lft 2853sec preferred_lft 2853sec
    inet6 fe80::47a1:82e3:ac6f:435c/64 scope link noprefixroute 
       valid_lft forever preferred_lft forever
4: docker0: <NO-CARRIER,BROADCAST,MULTICAST,UP> mtu 1500 qdisc noqueue state DOWN group default 
    link/ether de:b7:11:e7:1c:ed brd ff:ff:ff:ff:ff:ff
    inet 172.17.0.1/16 brd 172.17.255.255 scope global docker0
       valid_lft forever preferred_lft forever
bogdan@bogdanbuilds:~$ ip addr show
1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN group default qlen 1000
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
    inet 127.0.0.1/8 scope host lo
       valid_lft forever preferred_lft forever
    inet6 ::1/128 scope host noprefixroute 
       valid_lft forever preferred_lft forever
2: enp129s0: <NO-CARRIER,BROADCAST,MULTICAST,UP> mtu 1500 qdisc mq state DOWN group default qlen 1000
    link/ether c8:53:09:ae:ca:47 brd ff:ff:ff:ff:ff:ff
3: wlp130s0f0: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc noqueue state UP group default qlen 1000
    link/ether 24:eb:16:9d:d4:79 brd ff:ff:ff:ff:ff:ff
    inet 172.20.10.2/28 brd 172.20.10.15 scope global dynamic noprefixroute wlp130s0f0
       valid_lft 2050sec preferred_lft 2050sec
    inet6 fe80::47a1:82e3:ac6f:435c/64 scope link noprefixroute 
       valid_lft forever preferred_lft forever
4: docker0: <NO-CARRIER,BROADCAST,MULTICAST,UP> mtu 1500 qdisc noqueue state DOWN group default 
    link/ether de:b7:11:e7:1c:ed brd ff:ff:ff:ff:ff:ff
    inet 172.17.0.1/16 brd 172.17.255.255 scope global docker0
       valid_lft forever preferred_lft forever
bogdan@bogdanbuilds:~$ ip -br addr
lo               UNKNOWN        127.0.0.1/8 ::1/128 
enp129s0         DOWN           
wlp130s0f0       UP             172.20.10.2/28 fe80::47a1:82e3:ac6f:435c/64 
docker0          DOWN           172.17.0.1/16 
bogdan@bogdanbuilds:~$ ip route show
default via 172.20.10.1 dev wlp130s0f0 proto dhcp src 172.20.10.2 metric 600 
172.17.0.0/16 dev docker0 proto kernel scope link src 172.17.0.1 linkdown 
172.20.10.0/28 dev wlp130s0f0 proto kernel scope link src 172.20.10.2 metric 600 
bogdan@bogdanbuilds:~$ ip route get 8.8.8.8
8.8.8.8 via 172.20.10.1 dev wlp130s0f0 src 172.20.10.2 uid 1000 
    cache 
bogdan@bogdanbuilds:~$ ip neigh show
172.20.10.1 dev wlp130s0f0 lladdr 9a:0d:af:ed:e9:64 REACHABLE 
fe80::980d:afff:feed:e964 dev wlp130s0f0 lladdr 9a:0d:af:ed:e9:64 router STALE 
bogdan@bogdanbuilds:~$ ping -c 4 info.uaic.ro
PING info.uaic.ro (85.122.23.162) 56(84) bytes of data.
64 bytes from http-1.info.uaic.ro (85.122.23.162): icmp_seq=1 ttl=53 time=27.6 ms
64 bytes from http-1.info.uaic.ro (85.122.23.162): icmp_seq=2 ttl=53 time=48.9 ms
64 bytes from http-1.info.uaic.ro (85.122.23.162): icmp_seq=3 ttl=53 time=63.4 ms
64 bytes from http-1.info.uaic.ro (85.122.23.162): icmp_seq=4 ttl=53 time=41.2 ms

--- info.uaic.ro ping statistics ---
4 packets transmitted, 4 received, 0% packet loss, time 3004ms
rtt min/avg/max/mdev = 27.595/45.270/63.433/12.963 ms


bogdan@bogdanbuilds:~$ sudo traceroute -I -n 1.1.1.1
traceroute to 1.1.1.1 (1.1.1.1), 30 hops max, 60 byte packets
 1  172.20.10.1  13.014 ms  18.208 ms  20.977 ms
 2  * * *
 3  * * *
 4  * * *
 5  109.166.204.122  66.756 ms  68.707 ms  73.878 ms
 6  * * *
 7  93.113.56.113  52.805 ms * *
 8  162.158.16.15  35.527 ms  35.470 ms  31.976 ms
 9  1.1.1.1  31.921 ms  25.016 ms  24.958 ms
bogdan@bogdanbuilds:~$ 



netstat -> Conexiuni TCP deschise.

Aplicatie web/Custom care sa asculte conexiuni. Porturile le vedem in LISTEN.

Folosind ARP poisoning, se poate implementa *man in the middle* attacks. Acum e destul de obsolete.

CTF - pe networking


Saptamana viitoare - comunicare TCP

