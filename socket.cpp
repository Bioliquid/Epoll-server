#include "socket.h"


void IPv4_socket::create()
{
	std::cout << std::string(25, '-') << std::endl;
	socket = ::socket(AF_INET, SOCK_STREAM, 0);
	if(socket == -1) {
		perror("socket() error");
	} else {
		std::cout << "Socket initialization\n";
	}
}

fd_set IPv4_socket::set_on_read()
{
	fd_set set_on_read;		
    FD_ZERO(&set_on_read);
    FD_SET(socket, &set_on_read);
	FD_SET(STDIN_FILENO, &set_on_read);

    int max = std::max(socket, STDIN_FILENO);

    if(select(max + 1, &set_on_read, NULL, NULL, NULL) == -1) {
        perror("select() error");
    }
	return set_on_read;
}

void IPv4_socket::set_options(int optname, int optval)
{
	if(::setsockopt(socket, SOL_SOCKET, optname, &optval, sizeof optval) == -1) {
		perror("setsockopt() error");
	} else {
		std::cout << "Setting up options\n";
	}
}

void IPv4_socket::set_options(int optname, struct timeval tv)
{
	if(::setsockopt(socket, SOL_SOCKET, optname, (char *)&tv, sizeof(struct timeval))) {
		perror("setsockopt() error");
	} else {
		std::cout << "Setting up options\n";
	}
}

void IPv4_socket::bind(struct sockaddr_in addr)
{
	if(::bind(socket, (struct sockaddr *)&addr, sizeof(sockaddr)) == -1) {
		perror("bind error()");
	} else {
		std::cout << "Binding socket\n";
	}
}

void IPv4_socket::listen()
{
	if(::listen(socket, SOMAXCONN) == -1) {
		perror("listen error()");
	} else {
		std::cout << "Listening socket\n";
	}
}

void IPv4_socket::connect(struct sockaddr_in addr)
{
	if(::connect(socket, (struct sockaddr *)&addr, sizeof(sockaddr)) == -1) {
        perror("connect() error");
    } else {
		std::cout << "Connecting socket\n";
	}
	std::cout << std::string(25, '-') << std::endl;
}

std::string IPv4_socket::recv(int socket_)
{
	char buffer[BUFFER_LENGTH];
	std::string buf = "";
	struct timeval recv_timeout;
	recv_timeout.tv_sec = 1;
	recv_timeout.tv_usec = 0;
	::setsockopt(socket_, SOL_SOCKET, SO_RCVTIMEO, (char *)&recv_timeout, sizeof(struct timeval));
	int recv_res = ::recv(socket_, buffer, BUFFER_LENGTH, 0);	
	if(recv_res == -1) {
		perror("recv() error");
		close(socket_);
	} else if (recv_res == 0 && errno != EAGAIN) {
		shutdown(socket_, SHUT_RDWR);
        close(socket_);
        std::cout << "Connection terminated" << std::endl;
		std::cout << std::string(25, '-') << std::endl;
		return "Error";
	}
	for(int i = 0; i < strlen(buffer); ++i) {
		buf += buffer[i];
	}
	return buf;
}

void IPv4_socket::send(int sock_, const char* buffer, size_t length)
{
	if(::send(sock_, buffer, length, MSG_NOSIGNAL) == -1) {
		perror("send() error");
	}
}

int IPv4_socket::accept()
{
	int socket_ = ::accept(socket, NULL, NULL);
    if(socket_ == -1) {
        perror("accept() error");
    } else {
		std::cout << "Accepting socket\n";
	}
	return socket_;
}

void Socket_address::initialize(short sin_family, unsigned long addr, unsigned short port)
{
	serveraddr.sin_family = sin_family;
	serveraddr.sin_addr.s_addr = addr;
	serveraddr.sin_port = htons(port);
	memset(&(serveraddr.sin_zero), '\0', 8);
}

void Timeline::initialize(int seconds, int mseconds)
{
	tv.tv_sec = seconds;
	tv.tv_usec = mseconds;
}
