#include "session.h"

int main()
{
    IPv4_session session;
	session.open();
	for(;;) {
		session.wait();
		for(int i = 0; i < session.events; ++i) {
			int cur_sock = session.get_cur_fd(i);
			if(cur_sock == session.get_socket()) {
				int socket_ = session.accept();				
				const char *welcome = "Please, enter your name:\n";
				session.send(socket_, welcome, strlen(welcome));
			} else {
				if(session.get_cur_event(i) & EPOLLIN) {
					std::string buffer = session.recv(cur_sock);
                    if (buffer != "Error") {
						session.sendToAll(buffer);
                    }
                }
			}
		}
	}
	session.close_server();
    return 0;
}
