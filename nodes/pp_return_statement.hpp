#include "pp_statement.hpp"
#include "pp_expression.hpp"

class PPReturnStatement : public NStatement
{
    public:
        PPExpression &expression;

        PPReturnStatement(PPExpression &expression)
        : expression(expression)
        {}
};
