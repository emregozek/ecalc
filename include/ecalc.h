#pragma once

#include <string>
#include <iosfwd>
#include <stack>
#include <queue>

namespace ecalc {

class calculate {
    public:
        explicit calculate(std::string str);
        double operator()() const;
        friend std::ostream& operator<<(std::ostream& os, const calculate& c);
    private:
        struct operand_def {
            std::size_t idx;
            double val;
        };
        enum class operator_type {
            add,
            substract,
            multiply,
            divide,
            expo
        };
        
        struct operator_def {
            int prio;
            std::size_t idx;
            operator_type type;
            bool operator<(const operator_def& right) const {
                return prio < right.prio;
            }
            operator_def(int pr, std::size_t id, operator_type ty) : prio{pr}, idx{id}, type{ty} {}
        };

        struct expr {
            std::size_t idx;
            std::vector<operand_def> operand_vec;
            std::priority_queue<operator_def> operator_pq;
        };

        double subexpression() const;
        std::string m_input_str;
};

}