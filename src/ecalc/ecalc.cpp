#include <iostream>
#include <string>
#include "ecalc.h"
#include <stack>
#include <algorithm>
#include <queue>
#include <iterator>

namespace ecalc {

calculate::calculate(std::string str) : m_input_str{str} {}

std::ostream& operator<<(std::ostream& os, const calculate& c) {
    return os << "[" << c.m_input_str << "]";
}

std::priority_queue<calculate::pq_pair> calculate::subexpression(const std::string& str) const {
    using namespace std;
    priority_queue<pq_pair> result;
    stack<size_t> left_prnth;
    size_t i {};
    for_each(str.begin(), str.end(),
        [&left_prnth, &result, &i] (const char& c) {
            if (c == '(') {
                left_prnth.push(i);
            } else if (c == ')') {
                result.push(make_pair(left_prnth.size(), make_pair(left_prnth.top(), i)));
                left_prnth.pop();
            }
            ++i;
        }
    );
    return result;
}

double calculate::operator()() const {
    auto expr_bound {subexpression(m_input_str)};

    while (expr_bound.size() > 0) {
        const auto pq_pair = expr_bound.top();
        expr_bound.pop();
        std::cout << "depth: " << pq_pair.first << " expression: " << std::string{next(m_input_str.cbegin(), static_cast<long>(pq_pair.second.first)), next(m_input_str.begin(), static_cast<long>((pq_pair.second.second + 1)))} << "\n";
    }
    return 1.0;
}
}


int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "Please provide your expression in \"<expression>\" form\n";
        return 0;
    }
    auto f = ecalc::calculate{argv[1]};
    std::cout << f() << "\n";
}