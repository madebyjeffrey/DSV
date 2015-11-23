//
// Created by Jeffrey Drake on 2015-11-22.
//

#include <sstream>
#include <iostream>

#include "dsv.h"

namespace dsv {
    bool is_quote(char input) {
        return input == '"';
    }

    bool is_comma(char input) {
        return input == ',';
    }

    bool is_cr(char input) {
        return input == '\r';
    }

    bool is_lf(char input) {
        return input == '\n';
    }

    bool is_other(char input) {
        return !is_quote(input) && !is_comma(input) && input >= 32 && input <= 127;
    }

}