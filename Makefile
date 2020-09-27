all:
	g++ -Wall -c hosts.cpp
	g++ -Wall -c links.cpp
	g++ -Wall -c communication-udp.cpp
	g++ -Wall -lpthread -c thread.cpp 
	g++ -Wall servidor-dns.cpp hosts.o links.o thread.o communication-udp.o -o servidor_dns

clean:
	rm hosts.o communication-udp.o thread.o servidor-dns