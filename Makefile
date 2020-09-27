all:
	g++ -Wall -c hosts.cpp
	g++ -Wall servidor-dns.cpp hosts.o -o servidor-dns

clean:
	rm hosts.o servidor-dns