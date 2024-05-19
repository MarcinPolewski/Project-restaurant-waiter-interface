#include <gtest/gtest.h>
#include "address.h"

TEST(AddressTest, create_typical)
{
    Address adr("Olsztyn", "10-555", "Baltycka", "4");
    ASSERT_EQ(adr.getAddress(), "Baltycka 4\n10-555 Olsztyn");
    std::cerr << adr.getAddress();
}

TEST(AddressTest, create_with_additional_info)
{
    Address adr("Olsztyn", "10-555", "Baltycka", "4", "Klatka H6");
    ASSERT_EQ(adr.getAddress(), "Baltycka 4\n10-555 Olsztyn\nAI: Klatka H6");
    std::cerr << adr.getAddress();
}