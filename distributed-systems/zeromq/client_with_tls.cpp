#include <zmq.hpp>
#include <sodium.h>
#include <string>
#include <iostream>
#include <thread>
#include <chrono>
#include <string>

std::string client_secret_key = "D:)Q[IlAW!ahhC2ac:9*A}h:p?([4%wOTJ%JR%cs";
std::string client_public_key = "Yne@$w-vo<fVvi]a<NY6T1ed:M$fCG*[IaLV{hID";

std::string server_secret_key = "JTKVSB%%)wK0E.X)V>+}o?pNmC{O&4W4b!Ni{Lh6";
std::string server_public_key = "rq:rM>}U?@Lns47E1%kR.o@n%FcmmsL/@{H8]yf7";


int main() {

    try {
        // Create a ZeroMQ context
        zmq::context_t context(1);

        // Create a REQ (request) socket
        zmq::socket_t client_socket(context, zmq::socket_type::req);

        // Set the Curve security keys for the client
        client_socket.set(zmq::sockopt::curve_publickey, client_public_key.c_str());
        client_socket.set(zmq::sockopt::curve_secretkey, client_secret_key.c_str());
        client_socket.set(zmq::sockopt::curve_serverkey, server_public_key.c_str());

        // Connect to the server
        const std::string endpoint = "tcp://127.0.0.1:5555"; // Replace with your server's address and port
        client_socket.connect(endpoint);
        std::cout << "Client connected to " << endpoint << " with Curve security enabled." << std::endl;

        // Send a message to the server
        std::string message = "Hello from the client!";
        zmq::message_t request(message.size());
        memcpy(request.data(), message.data(), message.size());
        client_socket.send(request, zmq::send_flags::none);
        std::cout << "Sent: " << message << std::endl;

        // Wait for a reply from the server
        zmq::message_t reply;
        auto ret=client_socket.recv(reply, zmq::recv_flags::none);

        // Print the received reply
        std::string reply_message(static_cast<char*>(reply.data()), reply.size());
        std::cout << "Received reply: " << reply_message << std::endl;

    } catch (const zmq::error_t& e) {
        std::cerr << "ZeroMQ error: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Standard exception: " << e.what() << std::endl;
    }

    return 0;
}
