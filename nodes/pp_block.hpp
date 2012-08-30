#ifndef PAP_NODES_PPBLOCK_HPP_
#define PAP_NODES_PPBLOCK_HPP_

#include "pp_expression.hpp"
#include "pp_statement.hpp"

class PPBlock : public PPExpression
{
    public:
        PPStatement::StatementList statements;
        
        PPBlock()
        {}
};

#endif // PAP_NODES_PPBLOCK_HPP_