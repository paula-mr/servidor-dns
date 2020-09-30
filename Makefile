all:
	g++ -Wall -c hosts.cpp
	g++ -Wall -c links.cpp
	g++ -Wall -c communication-udp.cpp
	g++ -Wall -c thread.cpp
	g++ -Wall servidor-dns.cpp hosts.o links.o thread.o communication-udp.o -lpthread -o servidor_dns

clean:
	rm hosts.o communication-udp.o thread.o links.o servidor-dns