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
        using size_t_pair = std::pair<std::size_t, std::size_t>;
        using pq_pair = std::pair<int, size_t_pair>;
        std::priority_queue<pq_pair> subexpression(const std::string& str) const;
        std::string m_input_str;
};

}