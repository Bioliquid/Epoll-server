#include "epoll.h"

void Epoll::create()
{
	std::cout << std::string(25, '-') << std::endl;
	epfd = epoll_create(MAX_EVENTS);
	if(epfd == -1)  {
		perror("epoll_create() error");
	} else {
		std::cout << "Epoll initialization\n";
	}
}

void Epoll::ctl(int sock_, uint32_t events)
{	
	struct epoll_event socket_event;
    socket_event.data.fd = sock_;
    socket_event.events = events;
    if(epoll_ctl(epfd, EPOLL_CTL_ADD, sock_, &socket_event) == -1) {
        perror("epoll_ctl() error");
    } else {
		std::cout << "Controlling epoll\n";
	}
	if(events & EPOLLOUT) std::cout << "Connection accepted\n";
	std::cout << std::string(25, '-') << std::endl;
}

int Epoll::handle_events()
{
	memset(&events_, 0, sizeof(events_));
	int events = epoll_wait(epfd, events_, MAX_EVENTS, -1);
    if(events == -1) {
        perror("epoll_wait() error");
    }
	return events;
}
