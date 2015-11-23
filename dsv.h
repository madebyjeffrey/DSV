//
// Created by Jeffrey Drake on 2015-11-22.
//

#ifndef DSV_DSV_H
#define DSV_DSV_H

#include <string>
#include <vector>

namespace dsv {
    bool is_quote(char input);
    bool is_comma(char input);
    bool is_cr(char input);
    bool is_lf(char input);
    bool is_other(char input);


    template<typename It>
    class accumulator {
    public:
        int line;
        int col;
        It start, finish;
        bool error;
        std::string error_string;
        char c;

        std::string accumulation_buffer;
        std::vector<std::string> line_buffer;
        std::vector<std::vector<std::string>> fields_and_records;

    public:
        accumulator(It start, It finish)
                : line(1),
                  col(1),
                  start(start),
                  finish(finish),
                  error(false),
                  error_string(""),
                  accumulation_buffer(""),
                  line_buffer(),
                  fields_and_records()
        {
        }

        void emit_field() {
            line_buffer.push_back(accumulation_buffer);
            accumulation_buffer = "";
        }
        void emit_record() {
//            emit_field();
            fields_and_records.push_back(line_buffer);
            line_buffer.clear();
        }

        bool has_fields_buffered() {
            return line_buffer.size() != 0;
        }

        void accumulate() {
            accumulation_buffer += c;
        }

        bool has_next() const {
            return start != finish && !error;
        }

        char next() {
            if (error) throw "Error state";

            c = *start;
            ++start;

            if (c == '\n') {
                col = 1;
                line++;
            } else {
                col++;
            }

            return c;
        }

        void set_error(std::string const &err) {
            error = true;
            error_string = err;
        }

        std::string get_error() const {
            std::stringstream ss;

            ss << "Error line " << line << " col " << col << " : " << error_string;

            return ss.str();
        }

        bool has_error() const {
            return error;
        }

    };


    template<typename It>
    auto process_csv(It start, It finish) -> std::vector<std::vector<std::string>> {
        int state = 0;

        auto acc = accumulator<It>(start, finish);

        while (acc.has_next()) {
            char input = acc.next();
//        std::cout << "Input " << input << " on state " << state << std::endl;
            switch (state) {
                case 0:
                    if (is_quote(input)) {
                        state = 1;
                    } else if (is_comma(input) ) {
                        state = 0;
                        acc.emit_field();
                    } else if (is_cr(input)) {
                        state = 3;
                    } else if (is_lf(input)) {
                        state = 0;
                        acc.emit_field();
                        acc.emit_record();
                    } else if (is_other(input)) {
                        state = 4;
                        acc.accumulate();
                    }
                    break;
                case 1:
                    if (is_quote(input)) {
                        state = 2;
                    } else {
                        state = 1;
                        acc.accumulate();
                    }
                    break;

                case 2:
                    if (is_quote(input)) {
                        state = 1;
                        acc.accumulate();
                    } else if (is_comma(input) ) {
                        state = 0;
                        acc.emit_field();
                    } else if (is_cr(input)) {
                        state = 3;
                    } else if (is_lf(input)) {
                        state = 0;
                        acc.emit_field();
                        acc.emit_record();
                    } else if (is_other(input)) {
                        acc.set_error("Parse error, invalid in state 2");
                    }
                    break;
                case 3:
                    if (is_lf(input)) {
                        state = 0;
                        acc.emit_field();
                        acc.emit_record();
                    } else {
                        acc.set_error("Parse error, invalid in state 3");
                    }
                    break;
                case 4:
                    if (is_quote(input)) {
                        acc.set_error("Parse error, quote invalid in state 4");
                    } else if (is_comma(input) ) {
                        state = 0;
                        acc.emit_field();
                    } else if (is_cr(input)) {
                        state = 3;
                    } else if (is_lf(input)) {
                        state = 0;
                        acc.emit_field();
                        acc.emit_record();
                    } else if (is_other(input)) {
                        state = 4;
                        acc.accumulate();
                    }
                    break;

            }
        }

        // special handling for EOF
        if ((state == 4 || state == 0) && acc.has_fields_buffered()) {
            acc.emit_field();
            acc.emit_record();
            state = 0;
        }

        if (acc.has_error() || state != 0) {
            std::cout << acc.get_error() << std::endl;
            std::cout << "Finishing state " << state << std::endl;
            throw "error";
        }

        return acc.fields_and_records;
    }
}
#endif //DSV_DSV_H
