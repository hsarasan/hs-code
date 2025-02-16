#include <iostream>
#include <map>
#include <sstream>
#include <iomanip>

// Define the SOH character (ASCII value 1)
const char SOH = 0x01;

std::map<std::string,std::string> parse(const std::string& message) {
        size_t pos = 0;
        size_t next_pos = 0;
        std::map<std::string,std::string> fields;
        
        while (pos < message.size()) {
            next_pos = message.find('=', pos);  // Find '=' to separate key and value
            if (next_pos == std::string::npos) break;

            std::string key = message.substr(pos, next_pos - pos);  // Extract key
            pos = next_pos + 1;  // Move past the '='
            next_pos = message.find(SOH, pos);  // Find the delimiter '|'
            if (next_pos == std::string::npos) next_pos = message.size();

            std::string value = message.substr(pos, next_pos - pos);  // Extract value
            fields[key] = value;  // Store the key-value pair

            pos = next_pos + 1;  // Move past the delimiter to the next key-value pair
        }
        return fields;
}


// Function to generate a FIX message from a map
std::string generateFIXMessage(const std::map<int, std::string>& fixMap) {
    std::ostringstream fixMessage;

    // Step 1: Build the FIX message body (excluding BodyLength and Checksum)
    std::ostringstream bodyStream;
    for (const auto& pair : fixMap) {
        bodyStream << pair.first << "=" << pair.second << SOH;
    }
    std::string body = bodyStream.str();

    // Step 2: Calculate the BodyLength (number of characters in the body)
    int bodyLength = body.size();
    fixMessage << "8=FIX.4.4" << SOH; // BeginString (required field)
    fixMessage << "9=" << bodyLength << SOH; // BodyLength (required field)

    // Step 3: Append the body to the FIX message
    fixMessage << body;

    // Step 4: Calculate the checksum (sum of all bytes modulo 256)
    std::string messageSoFar = fixMessage.str();
    int checksum = 0;
    for (char ch : messageSoFar) {
        checksum += static_cast<unsigned char>(ch);
    }
    checksum %= 256;

    // Step 5: Append the checksum to the FIX message
    fixMessage << "10=" << std::setw(3) << std::setfill('0') << checksum << SOH;

    return fixMessage.str();
}

void printFixMessage(const std::string& fixMessage) {
    for (char ch : fixMessage) {
        if (ch == SOH) {
            std::cout << "|";
        } else {
            std::cout << ch;
        }
    }
    std::cout<<std::endl;
}
int main() {
    // Example FIX map with key-value pairs
    std::map<int, std::string> fixMap = {
        {35, "D"},             // MsgType (Order Single)
        {49, "CLIENT123"},     // SenderCompID
        {56, "SERVER456"},     // TargetCompID
        {34, "1"},             // MsgSeqNum
        {52, "20231010-12:30:00"}, // SendingTime
        {11, "ORDER12345"},    // ClOrdID
        {55, "AAPL"},          // Symbol
        {54, "1"},             // Side (1 = Buy)
        {38, "100"},           // OrderQty
        {40, "2"},             // OrdType (2 = Limit)
        {44, "150.00"}         // Price
    };

    // Generate the FIX message
    std::string fixMessage = generateFIXMessage(fixMap);

    printFixMessage(fixMessage);

    auto fields=parse(fixMessage);
    for (const auto& [key, value] : fields) {
        std::cout << key << " = " << value << std::endl;
    }


    return 0;
}