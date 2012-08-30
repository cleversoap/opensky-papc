#ifndef PAP_NODES_PPEXPRESSIONSTATEMENT_HPP_
#define PAP_NODES_PPEXPRESSIONSTATEMENT_HPP_

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

#endif // PAP_NODES_PPEXPRESSIONSTATEMENT_HPP_