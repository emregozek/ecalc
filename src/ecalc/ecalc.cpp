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

using p_operand = std::pair<std::size_t, double>;
using p_operator = std::pair<std::size_t, char>;
using p_expr_def = std::pair<std::vector<p_operand>, std::vector<p_operator>>;
using p_expr = std::pair<std::size_t, p_expr_def>;

std::priority_queue<calculate::pq_pair> calculate::subexpression(const std::string& str) const {
    using namespace std;
    priority_queue<pq_pair> result;
    stack<p_expr> expr_st;
    // each expression
    // start:size_t
    // operator(s)<operator, index> : pair<string, size_t>
    // operand(s)<operand, index> : pair<double, size_t>
    // (2 + ( 3 - 1 ) + 4 )
    size_t i {};
    auto str_it {str.cbegin()};
    while (str_it != str.cend()) {
        char c = *str_it;
        if (c == '(') {
            p_expr_def expr_def;
            expr_st.push(make_pair(i, expr_def));
        } else if (c == ')') {
            // 5 + (2 + ( 3 - 1 ) + 4 + ( 6 + 7 ) ) - 2
            p_expr cur_expr = expr_st.top();
            double cur_expr_result = cur_expr.second.first.front().second;
            std::size_t j {1};
            for (const auto& sc : cur_expr.second.second) {
                switch (sc.second) {
                    case '+':
                        cur_expr_result += cur_expr.second.first[j++].second;
                        break;
                    case '-':
                        cur_expr_result -= cur_expr.second.first[j++].second;
                        break;
                    case '*':
                        cur_expr_result *= cur_expr.second.first[j++].second;
                        break;
                    case '/':
                        cur_expr_result /= cur_expr.second.first[j++].second;
                        break;
                    default:
                        break;
                }
            }
            expr_st.pop();
            if (!expr_st.empty()) {
                expr_st.top().second.first.push_back(make_pair(cur_expr.first, cur_expr_result));
            }
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            expr_st.top().second.second.push_back(make_pair(i, c));
        } else {
            if (auto idx = str.find_first_not_of("0123456789", i); idx != std::string::npos) {
                auto operand = std::stod({str.substr(i, idx)});
                expr_st.top().second.first.push_back(make_pair(i, operand));
                str_it = str.cbegin() + static_cast<long>(idx);
            }
        }
        ++str_it;
    }

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


// int main(int argc, char *argv[]) {
//     if (argc != 2) {
//         std::cout << "Please provide your expression in \"<expression>\" form\n";
//         return 0;
//     }
//     auto f = ecalc::calculate{argv[1]};
//     std::cout << f() << "\n";
// }