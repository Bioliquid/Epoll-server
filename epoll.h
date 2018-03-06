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

class Epoll
{
private:
	int epfd;
	struct epoll_event events_[MAX_EVENTS];

public:
	void create();
	void ctl(int sock_, uint32_t events);
	int handle_events();
	struct epoll_event* get_events() const { return events_; };
	int get() const { return epfd; };
};