
#include <iostream>
#include <thread>
#include <SimpleAmqpClient/SimpleAmqpClient.h>

int main() {
    try {
        // Connect to RabbitMQ server
        AmqpClient::Channel::ptr_t channel = AmqpClient::Channel::Create("localhost");

        // Queue name
        std::string queue_name = "test_queue";

        // Declare the queue (if it doesn't exist already)
        channel->DeclareQueue(queue_name, false, true, false, false);

        std::cout << " [*] Waiting for messages in queue: " << queue_name << std::endl;

        while (true) {
            // Fetch a single message from the queue
            AmqpClient::Envelope::ptr_t envelope = channel->BasicGet(queue_name, true);

            if (envelope) {
                // Process the received message
                std::string message = envelope->Message()->Body();
                std::cout << " [x] Received: " << message << std::endl;
            } else {
                // No message available
                std::cout << " [*] No messages in the queue. Retrying..." << std::endl;
            }

            // Sleep briefly to avoid busy looping
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    } catch (const std::exception& e) {
        // Handle any exceptions
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;

}
