#include <gtest/gtest.h>
#include "address.h"
#include "destination.h"

TEST(AddressTest, create_typical)
{
    Address adr("Olsztyn", "10-555", "Baltycka", "4");
    ASSERT_EQ(adr.str(), "Baltycka 4\n10-555 Olsztyn");
}

TEST(AddressTest, create_with_additional_info)
{
    Address adr("Olsztyn", "10-555", "Baltycka", "4", "Klatka H6");
    ASSERT_EQ(adr.str(), "Baltycka 4\n10-555 Olsztyn\nAI: Klatka H6");
}

TEST(TableTest, create_typical)
{
    Table tbl(Table::Position(3, 5, 0), 4);
    ASSERT_EQ(tbl.position.x, 3);
    ASSERT_EQ(tbl.position.y, 5);
    ASSERT_EQ(tbl.position.level, 0);
    ASSERT_EQ(tbl.seats, 4);
    ASSERT_EQ(tbl.occupied, false);
}

TEST(TableTest, occupy)
{
    Table tbl(Table::Position(3, 5, 0), 4);
    ASSERT_EQ(tbl.occupied, false);
    tbl.occupied = true;
    ASSERT_EQ(tbl.occupied, true);
}

TEST(RemoteTest, typical)
{
    Address adr("Olsztyn", "10-555", "Baltycka", "4", "Klatka H6");
    Remote remote(adr);
    ASSERT_EQ(remote.address.city, "Olsztyn");
}

TEST(DestinationTest, cast_table)
{
    Table tbl(Table::Position(3, 5, 0), 4);
    Destination &dst = tbl;
    ASSERT_EQ(typeid(dst), typeid(tbl));
    ASSERT_EQ(dynamic_cast<Table&>(dst).position.x, 3);
}

TEST(DestinationTest, cast_remote)
{
    Remote remote(Address("Olsztyn", "10-555", "Baltycka", "4", "Klatka H6"));
    Destination &dst = remote;
    ASSERT_EQ(typeid(dst), typeid(remote));
    ASSERT_EQ(dynamic_cast<Remote&>(dst).address.postalCode, "10-555");
}