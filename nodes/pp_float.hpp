#ifndef PAP_NODES_PPFLOAT_HPP_
#define PAP_NODES_PPFLOAT_HPP_

#include "pp_expression.hpp"

class PPFloat : public PPExpression
{
    public:
        double value;
        
        PPFloat(double value)
        : value(value)
        {}
};

#endif // PAP_NODES_PPFLOAT_HPP_