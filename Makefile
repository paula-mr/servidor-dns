all:
	g++ -Wall -c hosts.cpp
	g++ -Wall servidor.cpp hosts.o -o servidor

clean:
	rm hosts.o servidor