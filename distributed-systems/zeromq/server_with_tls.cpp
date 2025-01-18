#include <zmq.hpp>
#include <sodium.h>
#include <string>
#include <iostream>
#include <thread>
#include <chrono>
#include <string>


int main() {

    try {
        // Create a ZeroMQ context
        zmq::context_t context(1);

        // Create a REP (reply) socket
        zmq::socket_t server_socket(context, zmq::socket_type::rep);

        std::string client_secret_key = "D:)Q[IlAW!ahhC2ac:9*A}h:p?([4%wOTJ%JR%cs";
        std::string client_public_key = "Yne@$w-vo<fVvi]a<NY6T1ed:M$fCG*[IaLV{hID";

        std::string server_secret_key = "JTKVSB%%)wK0E.X)V>+}o?pNmC{O&4W4b!Ni{Lh6";
        std::string server_public_key = "rq:rM>}U?@Lns47E1%kR.o@n%FcmmsL/@{H8]yf7";

        // Set the Curve security keys for the server
        server_socket.set(zmq::sockopt::curve_server, 1);
        server_socket.set(zmq::sockopt::curve_publickey, server_public_key.c_str());
        server_socket.set(zmq::sockopt::curve_secretkey, server_secret_key.c_str());

        // Bind the server socket to an endpoint
        const std::string endpoint = "tcp://*:5555"; // Listen on all interfaces at port 5555
        server_socket.bind(endpoint);
        std::cout << "Server is listening on " << endpoint << " with Curve security enabled." << std::endl;

        // Server loop
        while (true) {
            zmq::message_t request;

            // Wait for a message from a client
            auto ret=server_socket.recv(request, zmq::recv_flags::none);

            // Print the received message
            std::string received_message(static_cast<char*>(request.data()), request.size());
            std::cout << "Received: " << received_message << std::endl;

            // Prepare a reply
            std::string reply_message = "Message received: " + received_message;
            zmq::message_t reply(reply_message.size());
            memcpy(reply.data(), reply_message.data(), reply_message.size());

            // Send the reply back to the client
            server_socket.send(reply, zmq::send_flags::none);
        }
    } catch (const zmq::error_t& e) {
        std::cerr << "ZeroMQ error: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Standard exception: " << e.what() << std::endl;
    }

    return 0;
}
