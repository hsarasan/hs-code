#include <iostream>
#include <fstream>
#include "message.pb.h"

int main() {
    // Initialize Protobuf library
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    // Create and populate the message
    example::Message message;
    message.set_id(1);
    message.set_content("Hello, Protobuf!");

    // Serialize to a binary file
    std::ofstream output("message.bin", std::ios::binary);
    if (!message.SerializeToOstream(&output)) {
        std::cerr << "Failed to write the message." << std::endl;
        return 1;
    }
    std::cout << "Message serialized to 'message.bin' successfully." << std::endl;

    // Cleanup
    google::protobuf::ShutdownProtobufLibrary();

    return 0;
}
