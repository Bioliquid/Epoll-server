all:
	g++ server.cpp session.cpp epoll.cpp socket.cpp -o server
	g++ client.cpp session.cpp epoll.cpp socket.cpp -o client

clean:
	rm server client

