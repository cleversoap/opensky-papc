#ifndef PAP_NODES_PPRETURNSTATEMENT_HPP_
#define PAP_NODES_PPRETURNSTATEMENT_HPP_

#include "pp_statement.hpp"
#include "pp_expression.hpp"

class PPReturnStatement : public PPStatement
{
    public:
        PPExpression &expression;

        PPReturnStatement(PPExpression &expression)
        : expression(expression)
        {}
};

#endif // PAP_NODES_PPRETURNSTATEMENT_HPP_
