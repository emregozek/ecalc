#include <iostream>
#include <string>
#include "ecalc.h"
#include <stack>
#include <algorithm>
#include <queue>
#include <iterator>

namespace ecalc {

calculate::calculate(std::string str) : m_input_str{std::move(str)} {}

std::ostream& operator<<(std::ostream& os, const calculate& c) {
    return os << "[" << c.m_input_str << "]";
}

using p_operand = std::pair<std::size_t, double>;
using p_operator = std::pair<std::size_t, char>;
using p_expr_def = std::pair<std::vector<p_operand>, std::vector<p_operator>>;
using p_expr = std::pair<std::size_t, p_expr_def>;

double calculate::subexpression() const {
    std::stack<p_expr> expr_st;
    double result{};
    // each expression
    // start:size_t
    // operator(s)<operator, index> : pair<string, size_t>
    // operand(s)<operand, index> : pair<double, size_t>
    // (2 + ( 3 - 1 ) + 4 )
    auto str_it {m_input_str.cbegin()};
    while (str_it != m_input_str.cend()) {
        char c = *str_it;
        if (c == '(') {
            p_expr_def expr_def;
            expr_st.push(make_pair(std::distance(m_input_str.cbegin(), str_it), expr_def));
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
                expr_st.top().second.first.emplace_back(std::make_pair(cur_expr.first, cur_expr_result));
            } else {
                result = cur_expr_result;
            }
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            expr_st.top().second.second.emplace_back(std::make_pair(std::distance(m_input_str.cbegin(), str_it), c));
        } else {
            if (auto idx = m_input_str.find_first_not_of("0123456789", static_cast<std::size_t>(std::distance(m_input_str.cbegin(), str_it))); idx != std::string::npos) {
                auto operand = std::stod({m_input_str.substr(static_cast<std::size_t>(std::distance(m_input_str.cbegin(), str_it)), idx)});
                expr_st.top().second.first.emplace_back(std::make_pair(std::distance(m_input_str.cbegin(), str_it), operand));
                str_it = m_input_str.cbegin() + static_cast<long>(idx);
            }
        }
        std::advance(str_it, 1);
    }

    return result;
}

double calculate::operator()() const {
    return subexpression();
}
}

