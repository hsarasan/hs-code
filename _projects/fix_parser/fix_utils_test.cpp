
#include <gtest/gtest.h>
#include <string>
#include <map>
#include "fix_utils.h"

using namespace FIX;

TEST(FIXUtilsTest, ParseValidFIXMessage) {
    std::string fixMessage = "8=FIX.4.4\x01" 
                              "9=109\x01" 
                              "35=D\x01" 
                              "49=BUYER\x01" 
                              "56=SELLER\x01" 
                              "34=1\x01" 
                              "52=20250216-15:30:45.123\x01" 
                              "11=ORD12345\x01" 
                              "55=AAPL\x01" 
                              "54=1\x01" 
                              "38=100\x01" 
                              "40=2\x01" 
                              "44=150.50\x01" 
                              "59=0\x01" 
                              "10=059\x01";
    
    auto parsedFields = parse(fixMessage);
    EXPECT_EQ(parsedFields["8"], "FIX.4.4");
    EXPECT_EQ(parsedFields["9"], "109");
    EXPECT_EQ(parsedFields["35"], "D");
    EXPECT_EQ(parsedFields["49"], "BUYER");
    EXPECT_EQ(parsedFields["56"], "SELLER");
    EXPECT_EQ(parsedFields["11"], "ORD12345");
    EXPECT_EQ(parsedFields["55"], "AAPL");
    EXPECT_EQ(parsedFields["54"], "1");
    EXPECT_EQ(parsedFields["38"], "100");
    EXPECT_EQ(parsedFields["40"], "2");
    EXPECT_EQ(parsedFields["44"], "150.50");
    EXPECT_EQ(parsedFields["10"], "059");
}

TEST(FIXUtilsTest, GenerateFIXMessage) {
    std::map<int, std::string> fixMap = {
        {35, "D"},
        {49, "BUYER"},
        {56, "SELLER"},
        {34, "1"},
        {52, "20250216-15:30:45.123"},
        {11, "ORD12345"},
        {55, "AAPL"},
        {54, "1"},
        {38, "100"},
        {40, "2"},
        {44, "150.50"}
    };

    std::string generatedMessage = generateFIXMessage(fixMap);
    auto parsedFields = parse(generatedMessage);
    
    EXPECT_EQ(parsedFields["35"], "D");
    EXPECT_EQ(parsedFields["49"], "BUYER");
    EXPECT_EQ(parsedFields["56"], "SELLER");
    EXPECT_EQ(parsedFields["11"], "ORD12345");
    EXPECT_EQ(parsedFields["55"], "AAPL");
    EXPECT_EQ(parsedFields["54"], "1");
    EXPECT_EQ(parsedFields["38"], "100");
    EXPECT_EQ(parsedFields["40"], "2");
    EXPECT_EQ(parsedFields["44"], "150.50");
    EXPECT_TRUE(parsedFields.find("8") != parsedFields.end()); // Ensure BeginString exists
    EXPECT_TRUE(parsedFields.find("9") != parsedFields.end()); // Ensure BodyLength exists
    EXPECT_TRUE(parsedFields.find("10") != parsedFields.end()); // Ensure Checksum exists
}
