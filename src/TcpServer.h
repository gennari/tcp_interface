#ifndef __TCPSERVER_H__
#define __TCPSERVER_H__

#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <stdlib.h>
#include <pthread.h>
#include <string>
#include <cstring>

#ifdef WIN32
	#include <winsock2.h>
	#include <io.h>
#else
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <unistd.h>
	#include <netdb.h>
#endif


class TcpConnection
{
protected:
	pthread_t thr;
	bool running;

public:
	unsigned int clientSocket;
	struct sockaddr_in clientAddress;
	char host[80];
	uint16_t port;

	TcpConnection();
	virtual ~TcpConnection();
	void start();
	void stop();
	bool send(const void* buffer, int len);
	bool send(const char* buffer);
        bool send(std::string buffer_str) { return send(buffer_str.c_str()); }
	int receive(void *buffer, int len);
	int getline(char *buffer, int len);

	virtual void _run()=0;
};


class TcpServer
{
public:
	char name[128];
public:
	TcpServer();
	virtual ~TcpServer();
	bool open(int p);
	void close();
	void start();
	void stop();
	void _run();
	int countConnections(); // how many active connections
	TcpConnection *getFirstConnection();
	TcpConnection *getConnection(int k); // May be null if the client disconnected
	int maxClientIndex() { return nclient; } // MAX index of a client
	virtual TcpConnection *newConnection()=0;

	bool connected;

private:
	int listenSocket, listenPort;
	bool running;
	pthread_t thr;
	struct sockaddr_in serverAddress;
	struct sockaddr_in clientAddress;
	TcpConnection *connection[10];
	int nclient;

    struct hostent *server;
};

#endif
