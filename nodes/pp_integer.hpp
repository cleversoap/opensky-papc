#ifndef PAP_NODES_PPINTEGER_HPP_
#define PAP_NODES_PPINTEGER_HPP_

#include "pp_expression.hpp"

class PPInteger : public PPExpression
{
    public:
        
        long long value;

        PPInteger(long long value)
        : value(value)
        {}
};

#endif // PAP_NODES_PPINTEGER_HPP_
