This directory contains some sample zeromq programs that could be used to be built from

THese are the packages I needed

libzmq
cppzmq
libsodium

Step 1

Get libsodium

git clone https://github.com/jedisct1/libsodium
cd libsodium
make && make check
make install

libzmq was built with the following instructions

git clone https://github.com/zeromq/libzmq
cd libzqmq
cmake .. -DWITH_TLS=ON  -DWITH_LIBSODIUM=ON -DWITH_LIBSODIUM_STATIC=ON -DENABLE_CURVE=ON
make install
ldconfig

git clone https://github.com/zeromq/cppzmq
cd cppzmq
cmake ..
make 
make install

Ensure the path /usr/local/lib contains the zmq and sodium libraries


############################################################################

server_with_tls and client_with_tls communicae over TLS

You can verify that it is indeed encrypted using tcpdum
sudo tcpdump -i any port 5555 -X

Or change one of the keys at the client and see it doesnt get through











