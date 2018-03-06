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
#include "socket.h"
#include "epoll.h"

class IPv4_session 
{
private:
	IPv4_socket socket;
	Epoll epfd;
public:
	int events;

	bool listens();
	std::string tells(std::string buffer, std::string &name);
	void open();
	void close_server();
	void close_client();
	void sendToAll(std::string buffer);
	int accept();
	void connect();
	void wait();
	void send(int sock_, const char* buf, size_t length);
	std::string recv(int socket_);

	int get_cur_fd(int i) const { return epfd.get_events()[i].data.fd; };
	int get_cur_event(int i) const { return epfd.get_events()[i].events; };
	int get_socket() const { return socket.get(); };
};