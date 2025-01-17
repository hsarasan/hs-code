#include <iostream>
#include <fstream>
#include "message.pb.h"

int main() {
    // Initialize Protobuf library
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    // Deserialize the message
    example::Message message;
    std::ifstream input("message.bin", std::ios::binary);
    if (!message.ParseFromIstream(&input)) {
        std::cerr << "Failed to read the message." << std::endl;
        return 1;
    }

    // Print the deserialized message
    std::cout << "Message received:" << std::endl;
    std::cout << "ID: " << message.id() << std::endl;
    std::cout << "Content: " << message.content() << std::endl;

    // Cleanup
    google::protobuf::ShutdownProtobufLibrary();

    return 0;
}

