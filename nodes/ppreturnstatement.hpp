#include "ppstatement.hpp"
#include "ppexpression.hpp"

class PPReturnStatement : public NStatement
{
    public:
        PPExpression &expression;

        PPReturnStatement(PPExpression &expression)
        : expression(expression)
        {}
};
