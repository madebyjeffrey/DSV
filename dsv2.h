
#include <iterator>
#include <string>
#include <algorithm>
#include <locale>
#include <stdexcept>
#include <functional>

namespace dsv {



    template<typename It>
    class DSV {
        char delimeter_;
        It first_, last_;
        bool end_of_record_;

        // skip whitespace (isblank)
        void skip_ws() {
            while (first_ != last_ && isblank(*first_)) {
                ++first_;
            }
        }


        // reads until next delimeter, newline, or end of input
        // will ignore delimeters and newlines in quotes
        // ignores any escaped quotes
        std::string extract_field() {
            bool quote = false;
            std::string contents;

            skip_ws();

            if (first_ != last_) {
                if (*first_ == '"') { // find next quote
                    ++first_;
                    while (first_ != last_ && *first_ != '"') {
                        contents.push_back(*first_);
                        ++first_;
                    }
                    // find delimeter
                    while (first_ != last_ && *first_ != delimeter_ && *first_ != '\n') {
                        ++first_;
                    }
                } else {
                    // find delimeter
                    while (first_ != last_ && *first_ != delimeter_ && *first_ != '\n') {
                        contents.push_back(*first_);
                        ++first_;
                    }
                }
            }

            return contents;
        }

    public:
        DSV(It first, It last, char delimeter = ',')
                : first_(first), last_(last), delimeter_(delimeter), end_of_record_(false) {
        }

        bool has_next_field() {
            return !end_of_record_;
        }

        bool has_next_record() {
            return (first_ != last_);
        }

        void next_record() {
            end_of_record_ = false;
        }

        std::string next_field() {
            if (end_of_record_) {
                throw std::invalid_argument("End of record");
            }

            auto contents = extract_field();

            if (first_ == last_) {
                end_of_record_ = true;
            } else {
                if (*first_ == delimeter_) {
                    ++first_;
                } else if (*first_ == '\n') {
                    ++first_;
                    end_of_record_ = true;
                }
            }

            return contents;
        }


    };

    template<typename It>
    auto make_parser(It first, It last, char delimeter = ',') -> DSV<It> {
        return DSV<It>(first, last, delimeter);
    }
}