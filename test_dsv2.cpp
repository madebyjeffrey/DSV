//
// Created by Jeffrey Drake on 2015-11-28.
//
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <iostream>
#include <sstream>
#include <iterator>

#include "dsv2.h"

using namespace std;
using namespace dsv;

TEST_CASE("Test size of CSV with various line endings") {
    SECTION("Two field with line feed") {
        string csv = "1,2\n";

        auto dsv = make_parser(begin(csv), end(csv));

        int i = 0;
        while (dsv.has_next_field()) {
            dsv.next_field();
            ++i;
        }

        REQUIRE(i == 2);
        REQUIRE_FALSE(dsv.has_next_field());
        REQUIRE_FALSE(dsv.has_next_record());
    }

    SECTION("Single Line No Terminator") {
        string csv = "1,2";

        auto dsv = make_parser(begin(csv), end(csv));

        int i = 0;
        while (dsv.has_next_field()) {
            dsv.next_field();
            ++i;
        }

        REQUIRE(i == 2);
        REQUIRE_FALSE(dsv.has_next_field());
        REQUIRE_FALSE(dsv.has_next_record());
    }

    SECTION("Single Line No Terminator, Simple") {
        string csv = ",";

        auto dsv = make_parser(begin(csv), end(csv));

        int i = 0;
        while (dsv.has_next_field()) {
            dsv.next_field();
            ++i;
        }

        REQUIRE(i == 2);
        REQUIRE_FALSE(dsv.has_next_field());
        REQUIRE_FALSE(dsv.has_next_record());
    }

    SECTION("Single Line, CR LF") {
        string csv = ",\r\n";

        auto dsv = make_parser(begin(csv), end(csv));

        int i = 0;
        while (dsv.has_next_field()) {
            dsv.next_field();
            ++i;
        }

        REQUIRE(i==2);
        REQUIRE_FALSE(dsv.has_next_field());
        REQUIRE_FALSE(dsv.has_next_record());
    }

    SECTION("Two Line two line feeds") {
        string csv = ",\n,\n";

        auto dsv = make_parser(begin(csv), end(csv));

        int i = 0;
        while (dsv.has_next_field()) {
            dsv.next_field();
            ++i;
        }

        REQUIRE(i == 2);
        REQUIRE_FALSE(dsv.has_next_field());
        REQUIRE(dsv.has_next_record());

        dsv.next_record();

        int j = 0;
        while (dsv.has_next_field()) {
            dsv.next_field();
            ++j;
        }

        REQUIRE(j == 2);
        REQUIRE_FALSE(dsv.has_next_field());
        REQUIRE_FALSE(dsv.has_next_record());
    }

    SECTION("Two lines and a single line feed") {
        string csv = ",\n,";

        auto dsv = make_parser(begin(csv), end(csv));

        int i = 0;
        while (dsv.has_next_field()) {
            dsv.next_field();
            ++i;
        }

        REQUIRE(i == 2);
        REQUIRE_FALSE(dsv.has_next_field());
        REQUIRE(dsv.has_next_record());

        dsv.next_record();

        int j = 0;
        while (dsv.has_next_field()) {
            dsv.next_field();
            ++j;
        }

        REQUIRE(j == 2);
        REQUIRE_FALSE(dsv.has_next_field());
        REQUIRE_FALSE(dsv.has_next_record());
    }

    SECTION("Two lines with line feed on first, and cr lf on second") {
        string csv = ",\n,\r\n";

        auto dsv = make_parser(begin(csv), end(csv));

        int i = 0;
        while (dsv.has_next_field()) {
            dsv.next_field();
            ++i;
        }

        REQUIRE(i == 2);
        REQUIRE_FALSE(dsv.has_next_field());
        REQUIRE(dsv.has_next_record());

        dsv.next_record();

        int j = 0;
        while (dsv.has_next_field()) {
            dsv.next_field();
            ++j;
        }

        REQUIRE(j == 2);
        REQUIRE_FALSE(dsv.has_next_field());
        REQUIRE_FALSE(dsv.has_next_record());
    }

    SECTION("Two lines each with cr lf") {
        string csv = ",\r\n,\r\n";

        auto dsv = make_parser(begin(csv), end(csv));

        int i = 0;
        while (dsv.has_next_field()) {
            dsv.next_field();
            ++i;
        }

        REQUIRE(i == 2);
        REQUIRE_FALSE(dsv.has_next_field());
        REQUIRE(dsv.has_next_record());

        dsv.next_record();

        int j = 0;
        while (dsv.has_next_field()) {
            dsv.next_field();
            ++j;
        }

        REQUIRE(j == 2);
        REQUIRE_FALSE(dsv.has_next_field());
        REQUIRE_FALSE(dsv.has_next_record());
    }

    SECTION("Quoted Fields") {
        string csv = "\"hello\",5";

        auto dsv = make_parser(begin(csv), end(csv));

        auto contents = dsv.next_field();

        REQUIRE(contents == "hello");

        auto next_contents = dsv.next_field();

        REQUIRE(next_contents == "5");
    }

/*
    SECTION("Bare CR") {
        string csv = ",\r,\r\n";

        auto dsv = make_parser(begin(csv), end(csv));

        dsv.next_field();
        REQUIRE_THROWS_AS(dsv.next_field(), std::invalid_argument);
    } */
    /*
    TEST(DSVTestErrors, FailureState4) {
        string csv = ",f\",";

        vector<vector<string>> result;
        ASSERT_THROW(dsv::process_csv(begin(csv), end(csv)), string);
    }

    TEST(DSVTestErrors, FailureState2) {
        string csv = ",\"\"g";

        vector<vector<string>> result;
        ASSERT_THROW(dsv::process_csv(begin(csv), end(csv)), string);
    }*/


}

