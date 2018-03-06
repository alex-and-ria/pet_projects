Sniffer writen in C for Linux.
	
It saves IP addresses and number of packets received from each IP for particular interface (default interface is wlan0, but
you may set it through command line interface (./cli1)). This data persistent through reboots as it saved in files like 
"log%interface_name%.txt".

There are 2 executables: ./snfr_d -- service and ./cli1 command line interface. Service may be started separately and than
may be used command line interface for interraction or may be startted ./cli1, which starts service if it is not started
already.

If you want restart service:
	
1. search for "./snfr_d \*" command in "ps aux" output
2. kill this process ("sudo kill %PID%")
3. clean files and rebuild executables ("sudo make distclean && make")
4. now you can restart service "sudo ./snfr_d" (as here sockets are used, executables should be started with root 
    privileges)

Time complexity for setting new record is O(N\*log(N)); for searching existing record is O(log(N)).
	
Command line interface (./cli1) supports commands:
	
1. start (packets are sniffed from now)
2. stop (packets are not sniffed)
3. show [ip] count (prints number of packets received from ip address)
4. select iface [iface] (selects interface for sniffing (eth0, wlan0, ethN, ...)
5. stat [iface] (shows all collected statistics for particular interface, if iface omitted -- for all interfaces).
6. --help (shows this usage information).

If you have questions or ideas for improvement this project, don't hesitate and mail me (alex.and.riaqqq@gmail.com).
