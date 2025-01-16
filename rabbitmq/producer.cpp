#include <iostream>
#include <SimpleAmqpClient/SimpleAmqpClient.h>

int main() {
    try {
        // Create a connection to RabbitMQ
        AmqpClient::Channel::ptr_t channel = AmqpClient::Channel::Create("localhost");

        // Declare a queue for the message
        std::string queue_name = "test_queue";
        channel->DeclareQueue(queue_name, false, true, false, false);

        // Create a message
        std::string message = "Hello RabbitMQ from C++!";

        // Publish the message to the queue
        channel->BasicPublish("", queue_name, AmqpClient::BasicMessage::Create(message));

        std::cout << "Message sent: " << message << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
