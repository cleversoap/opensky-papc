#include "ppexpression.hpp"
#include "ppidentifier.hpp"

class PPAssignment : public PPExpression
{
    public:
        PPIdentifier &lhs;
        PPExpression &rhs;

        PPAssignment(PPIdentifier &lhs, PPExpression &rhs)
        : lhs(lhs), rhs(rhs)
        {}
};
