#include "ppexpression.hpp"

class PPBinaryOperator : public PPExpression
{
    public:
        int op; // TODO: See if this can be changed to an enum as I'm pretty sure this is still tied to LLVM
        PPExpression &lhs;
        PPExpression &rhs;

        PPBinaryOperator(PPExpression &lhs, int op, PPExpression &rhs)
        : lhs(lhs), rhs(rhs), op(op)
        {}
};
