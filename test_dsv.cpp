#include <iostream>
#include <sstream>
#include <iterator>

#include "gtest/gtest.h"

#include "dsv.h"

using namespace std;

TEST(DSVTestSize, SingleLineWithLF) {
    string csv = "1,2\n";

    vector<vector<string>> result;
    ASSERT_NO_THROW({
                        result = dsv::process_csv(begin(csv), end(csv));
                    });

    size_t y = result.size();
    ASSERT_EQ(y, 1);

    size_t x = result[0].size();
    ASSERT_EQ(x, 2);
}

TEST(DSVTestSize, SingleLineNoTerminator) {
    string csv = "1,2";

    vector<vector<string>> result;
    ASSERT_NO_THROW({
                        result = dsv::process_csv(begin(csv), end(csv));
                    });

    size_t y = result.size();
    ASSERT_EQ(y, 1);

    size_t x = result[0].size();
    ASSERT_EQ(x, 2);
}

TEST(DSVTestSize, SingleLineNoTerminator2) {
    string csv = ",";

    vector<vector<string>> result;
    ASSERT_NO_THROW({
                        result = dsv::process_csv(begin(csv), end(csv));
                    });


    size_t y = result.size();
    ASSERT_EQ(y, 1);

    size_t x = result[0].size();
    ASSERT_EQ(x, 2);
}

TEST(DSVTestSize, SingleLineCRLF) {
    string csv = ",\r\n";

    vector<vector<string>> result;
    ASSERT_NO_THROW({
                        result = dsv::process_csv(begin(csv), end(csv));
                    });

    size_t y = result.size();
    ASSERT_EQ(y, 1);

    size_t x = result[0].size();
    ASSERT_EQ(x, 2);
}

TEST(DSVTestSize, TwoLines2LF) {
    string csv = ",\n,\n";

    vector<vector<string>> result;
    ASSERT_NO_THROW({
                        result = dsv::process_csv(begin(csv), end(csv));
                    });

    size_t y = result.size();
    ASSERT_EQ(y, 2);

    size_t x = result[0].size();
    ASSERT_EQ(x, 2);
}


TEST(DSVTestSize, TwoLines1LF) {
    string csv = ",\n,";

    vector<vector<string>> result;
    ASSERT_NO_THROW({
                        result = dsv::process_csv(begin(csv), end(csv));
                    });

    size_t y = result.size();
    ASSERT_EQ(y, 2);

    size_t x = result[0].size();
    ASSERT_EQ(x, 2);
}

TEST(DSVTestSize, TwoLines1LF1CRLF) {
    string csv = ",\n,\r\n";

    vector<vector<string>> result;
    ASSERT_NO_THROW({
                        result = dsv::process_csv(begin(csv), end(csv));
                    });

    size_t y = result.size();
    ASSERT_EQ(y, 2);

    size_t x = result[0].size();
    ASSERT_EQ(x, 2);
}

TEST(DSVTestSize, TwoLines2CRLF) {
    string csv = ",\r\n,\r\n";

    vector<vector<string>> result;
    ASSERT_NO_THROW({
                        result = dsv::process_csv(begin(csv), end(csv));
                    });

    size_t y = result.size();
    ASSERT_EQ(y, 2);

    size_t x = result[0].size();
    ASSERT_EQ(x, 2);
}


TEST(DSVTestErrors, FailureState3) {
    string csv = ",\r,\r\n";

    vector<vector<string>> result;
    ASSERT_THROW(dsv::process_csv(begin(csv), end(csv)), string);
}
TEST(DSVTestErrors, FailureState4) {
    string csv = ",f\",";

    vector<vector<string>> result;
    ASSERT_THROW(dsv::process_csv(begin(csv), end(csv)), string);
}

TEST(DSVTestErrors, FailureState2) {
    string csv = ",\"\"g";

    vector<vector<string>> result;
    ASSERT_THROW(dsv::process_csv(begin(csv), end(csv)), string);
}
