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
