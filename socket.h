#pragma once

#include <iostream>
#include <sys/socket.h>
#include <netdb.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstring>
#include <string>
#include <arpa/inet.h>
#include <errno.h>
#include <cstdio>
#include <sys/epoll.h>

#define MAX_EVENTS 1024
#define BUFFER_LENGTH 1024
#define UP "\x1b[1A"
#define ERASE_LINE "\x1b[2K"

class IPv4_socket
{
private:
	int socket;
public:

    int get() const { return socket; }

	void create();
	void set_options(int optname, int optval);
	void set_options(int optname, struct timeval tv);
	void bind(struct sockaddr_in addr);
	void listen();
	void connect(struct sockaddr_in addr);
    std::string recv(int socket_);
    void send(int sock_, const char* buf, size_t length);
	int accept();
	fd_set set_on_read();
};

struct Socket_address
{
	struct sockaddr_in serveraddr;
	void initialize(short sin_family, unsigned long addr, unsigned short port);
};

struct Timeline
{
	struct timeval tv;
	void initialize(int seconds, int mseconds);
};