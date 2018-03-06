#include "session.h"

#define PORT 8800

void IPv4_session::connect()
{
	socket.create();

	Socket_address addr;
	addr.initialize(AF_INET, INADDR_ANY, PORT);

    socket.connect(addr.serveraddr);
}

bool IPv4_session::listens()
{
	fd_set on_read = socket.set_on_read();
	if(FD_ISSET(socket.get(), &on_read)) {
		return true;
	}
	return false;
}

std::string IPv4_session::tells(std::string buffer, std::string &name)
{
	fd_set on_read = socket.set_on_read();
	if(FD_ISSET(STDIN_FILENO, &on_read)) {
		std::string input("");
		getline(std::cin, input);
		if (buffer == "Please, enter your name:\n") {
			name = input; 
			input = name + " joined us!";
		} else {
			input = name + ": " + input;
		}
		input.push_back('\n');
		std::cout << UP << ERASE_LINE;
		return input;
	}
	return "Error";
}

void IPv4_session::open() 
{
	socket.create();
	socket.set_options(SO_REUSEADDR, 1);
	
	Socket_address addr;
	addr.initialize(AF_INET, INADDR_ANY, PORT);

	socket.bind(addr.serveraddr);

	socket.listen();
	
	Timeline tl;
	tl.initialize(3, 0);
	
	socket.set_options(SO_RCVTIMEO, tl.tv);
	epfd.create();
	epfd.ctl(socket.get(), EPOLLIN);
}

void IPv4_session::sendToAll(std::string buffer)
{
	for(int i = 0; i < events; ++i) {
        if(epfd.get_events()[i].events & EPOLLOUT) {
			socket.send(epfd.get_events()[i].data.fd, buffer.c_str(), buffer.length() + 1);
        }
    }
}

void IPv4_session::send(int socket_, const char* buffer, size_t length)
{
	socket.send(socket_, buffer, length + 1);
}

std::string IPv4_session::recv(int socket_)
{
	return socket.recv(socket_);
}

void IPv4_session::close_server()
{
	::close(socket.get());
	::close(epfd.get());
}

void IPv4_session::close_client()
{
	::close(socket.get());
}

int IPv4_session::accept()
{
	int accept_socket = socket.accept();
	epfd.ctl(accept_socket, EPOLLIN | EPOLLOUT);
	return accept_socket;
}
void IPv4_session::wait() 
{
	events = epfd.handle_events();	
}
