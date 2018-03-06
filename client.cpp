#include "session.h"

int main() {
	std::string name("");
    IPv4_session session;
	session.connect();
	
	for(;;) {
		std::string buffer;
		if (session.listens()) {
			buffer = session.recv(session.get_socket());
			std::cout << buffer;
		}
		std::string input = session.tells(buffer, name);
		if (input != "Error") {
			session.send(session.get_socket(), input.c_str(), input.length());
		}
	}  
	session.close_client();
    return 0;
}
