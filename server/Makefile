all: simplechat_server 

CC=g++
CFLAGS=-g

simplechat_server:Tcplib.cpp TcpServer.cpp CLogFile.cpp Client.hpp Forward.hpp Business.cpp main.cpp
	$(CC) -o simplechat_server Tcplib.cpp TcpServer.cpp CLogFile.cpp Client.hpp Forward.hpp Business.cpp main.cpp $(CFLAGS)

clean:
	rm -rf *.o
	rm -rf simplechat_server
