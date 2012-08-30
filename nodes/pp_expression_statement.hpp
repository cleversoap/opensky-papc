#include "pp_statement.hpp"
#include "pp_expression.hpp"

class PPExpressionStatement : public PPStatement
{
    public:
        PPExpression &expression;
        
        PPExpressionStatement(PPExpression &expression)
        : expression(expression)
        {}
};
