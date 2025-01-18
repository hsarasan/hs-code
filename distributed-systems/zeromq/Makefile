
all:
	g++ -std=c++17 server.cpp -o server -lzmq
	g++ -std=c++17 client.cpp -o client -lzmq
	g++ -std=c++17 server_with_tls.cpp -o server_tls -lzmq
	g++ -std=c++17 client_with_tls.cpp -o client_tls -lzmq


clean:
	rm -f client server client_tls server_tls
	
