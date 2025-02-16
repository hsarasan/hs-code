#include <iostream>
#include <unordered_map>
#include <vector>
#include <string_view>
#include <map>
#include <numeric>


namespace FIX_2{

constexpr char SOH = '\x01';

// Zero-copy FIX parser
std::unordered_map<std::string_view, std::string_view> parseFixMessage(std::string_view message) {
    std::unordered_map<std::string_view, std::string_view> fields;
    size_t pos = 0;

    while (pos < message.size()) {
        size_t eq_pos = message.find('=', pos);
        if (eq_pos == std::string_view::npos) break;

        size_t soh_pos = message.find(SOH, eq_pos + 1);
        if (soh_pos == std::string_view::npos) soh_pos = message.size();

        std::string_view key = message.substr(pos, eq_pos - pos);
        std::string_view value = message.substr(eq_pos + 1, soh_pos - eq_pos - 1);

        fields[key] = value;
        pos = soh_pos + 1;
    }
    return fields;
}

// Zero-copy FIX message generator
std::string generateFIXMessage(const std::unordered_map<int, std::string_view>& fixMap) {
    std::vector<char> buffer;
    buffer.reserve(512); // Preallocate memory

    auto append = [&](std::string_view str) {
        buffer.insert(buffer.end(), str.begin(), str.end());
    };

    // Compute BodyLength
    size_t bodyLength = 0;
    for (const auto& [tag, value] : fixMap) {
        bodyLength += std::to_string(tag).size() + 1 + value.size() + 1;
    }

    append("8=FIX.4.4"); buffer.push_back(SOH);
    append("9=" + std::to_string(bodyLength)); buffer.push_back(SOH);

    for (const auto& [tag, value] : fixMap) {
        append(std::to_string(tag)); buffer.push_back('=');
        append(value); buffer.push_back(SOH);
    }

    // Compute checksum
    int checksum = std::accumulate(buffer.begin(), buffer.end(), 0) % 256;
    append("10=" + std::to_string(checksum)); buffer.push_back(SOH);

    return std::string(buffer.begin(), buffer.end());
}

void printFixMessage(std::string_view fixMessage) {
    for (char ch : fixMessage) {
        std::cout << (ch == SOH ? '|' : ch);
    }
    std::cout << std::endl;
}

int main() {
    std::unordered_map<int, std::string_view> fixMap = {
        {35, "D"},
        {49, "CLIENT123"},
        {56, "SERVER456"},
        {34, "1"},
        {52, "20231010-12:30:00"},
        {11, "ORDER12345"},
        {55, "AAPL"},
        {54, "1"},
        {38, "100"},
        {40, "2"},
        {44, "150.00"}
    };

    std::string fixMessage = generateFIXMessage(fixMap);
    printFixMessage(fixMessage);

    auto parsedFields = parseFixMessage(fixMessage);
    for (const auto& [key, value] : parsedFields) {
        std::cout << key << " = " << value << std::endl;
    }

    return 0;
}

} // namespace FIX_2