#include "fix_utils.h"

using namespace FIX;

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
