#ifndef PAP_NODES_PPASSIGNMENT_HPP_
#define PAP_NODES_PPASSIGNMENT_HPP_

#include "pp_expression.hpp"
#include "pp_identifier.hpp"

class PPAssignment : public PPExpression
{
    public:
        PPIdentifier &lhs;
        PPExpression &rhs;

        PPAssignment(PPIdentifier &lhs, PPExpression &rhs)
        : lhs(lhs), rhs(rhs)
        {}
};

#endif // PAP_NODES_PPASSIGNMENT_HPP_