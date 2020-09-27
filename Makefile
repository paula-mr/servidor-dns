all:
	g++ -Wall -c hosts.cpp
	g++ -Wall -lpthread -c thread.cpp
	g++ -Wall servidor-dns.cpp hosts.o thread.o -o servidor_dns

clean:
	rm hosts.o thread.o servidor-dns