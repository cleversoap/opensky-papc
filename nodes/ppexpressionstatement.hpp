#include "ppstatement.hpp"
#include "ppexpression.hpp"

class PPExpressionStatement : public PPStatement
{
    public:
        PPExpression &expression;
        
        PPExpressionStatement(PPExpression &expression)
        : expression(expression)
        {}
};
