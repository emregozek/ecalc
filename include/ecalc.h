#pragma once

#include <string>
#include <iosfwd>
#include <stack>
#include <queue>

namespace ecalc {

class calculate {
    public:
        explicit calculate(std::string str);
        void print() const;
        double operator()() const;
        friend std::ostream& operator<<(std::ostream& os, const calculate& c);
    private:
        double subexpression() const;
        std::string m_input_str;
};

}