#include <iostream>
#include <string>
#include "ecalc.h"
#include <stack>
#include <cmath>
#include <algorithm>
#include <queue>
#include <iterator>

namespace ecalc {

calculate::calculate(std::string str) : m_input_str{std::move(str)} {
    // std::cout << "unsanitized input string: " << m_input_str << "\n";
    // m_input_str.erase(std::remove_if(m_input_str.begin(), m_input_str.end(), isspace), m_input_str.end());
    if (m_input_str[0] != '(') {
        m_input_str.insert(m_input_str.begin(), '(');
        m_input_str.insert(m_input_str.end(), ')');
    }
    std::cout << "sanitized input string: " << m_input_str << "\n";
}

std::ostream& operator<<(std::ostream& os, const calculate& c) {
    return os << "[" << c.m_input_str << "]";
}

double calculate::operator()() const {
    std::stack<expr> expr_st;
    double result{};
    auto str_it {m_input_str.cbegin()};
    while (str_it != m_input_str.cend()) {
        char c = *str_it;
        if (c == '(') {
            std::vector<operand_def> operand_vec;
            std::priority_queue<operator_def> operator_pq;
            std::size_t idx {static_cast<std::size_t>(str_it - m_input_str.begin())};
            expr cur_expr {idx, operand_vec, operator_pq};
            expr_st.push(cur_expr);
        } else if (c == ')') {
            auto cur_expr {expr_st.top()};
            auto cur_operand_vec {expr_st.top().operand_vec};
            auto cur_operator_pq {expr_st.top().operator_pq};
            double cur_expr_result{};
            while (!cur_operator_pq.empty()) {
                auto operator_def {cur_operator_pq.top()};
                auto right_operand_iter = std::find_if(cur_operand_vec.begin(), cur_operand_vec.end(), [&operator_def](const operand_def& operand){
                    return operand.idx >= operator_def.idx;
                });
                auto left_operand_iter {std::prev(right_operand_iter)};
                std::cout << left_operand_iter->val;
                switch (operator_def.type) {
                    case calculate::operator_type::add:
                        std::cout << " + ";
                        left_operand_iter->val += right_operand_iter->val;
                        break;
                    case calculate::operator_type::substract:
                        std::cout << " - ";
                        left_operand_iter->val -= right_operand_iter->val;
                        break;
                    case calculate::operator_type::multiply:
                        std::cout << " * ";
                        left_operand_iter->val *= right_operand_iter->val;
                        break;
                    case calculate::operator_type::divide:
                        std::cout << " / ";
                        if (right_operand_iter->val == 0) {
                            std::cout << right_operand_iter->val << " = " << std::numeric_limits<double>::max() << "\n";
                            return std::numeric_limits<double>::max();
                        }
                        left_operand_iter->val /= right_operand_iter->val;
                        break;
                    case calculate::operator_type::expo:
                        std::cout << " ^ ";
                        left_operand_iter->val = std::pow(left_operand_iter->val, right_operand_iter->val);
                        break;                    
                    default:
                        break;
                }
                std::cout << right_operand_iter->val << " = " << left_operand_iter->val << "\n";
                cur_operand_vec.erase(right_operand_iter);
                cur_operator_pq.pop();
                if (cur_operator_pq.empty()) {
                    cur_expr_result = left_operand_iter->val;
                }
            }
            expr_st.pop();
            if (!expr_st.empty()) {
                expr_st.top().operand_vec.push_back(operand_def{cur_expr.idx, cur_expr_result});
            } else {
                result = cur_expr_result;
            }
        } else if (std::string op_list {"+-*/^"}; std::string::npos != op_list.find(c)) {
            operator_type type = c == '+' ? operator_type::add : c == '-' ? operator_type::substract : c == '*' ? operator_type::multiply :  c == '/' ? operator_type::divide : c == '^' ? operator_type::expo : operator_type::add;
            int prio = type == operator_type::expo ? 3 : type == operator_type::multiply || type == operator_type::divide ? 2 : 1;
            expr_st.top().operator_pq.emplace(prio, static_cast<std::size_t>(str_it - m_input_str.begin()), type);
        } else if (std::string tmp_str {"1234567890."}; std::string::npos != tmp_str.find(c)) {
            if (auto idx = m_input_str.find_first_not_of("0123456789.", static_cast<std::size_t>(std::distance(m_input_str.cbegin(), str_it))); idx != std::string::npos) {
                auto operand_val = std::stod({m_input_str.substr(static_cast<std::size_t>(std::distance(m_input_str.cbegin(), str_it)), idx)});
                expr_st.top().operand_vec.push_back(operand_def{static_cast<std::size_t>(str_it - m_input_str.begin()), operand_val});
                str_it = m_input_str.cbegin() + static_cast<long>(idx) - 1;
            }
        }
        std::advance(str_it, 1);
    }
    return result;
}

}

