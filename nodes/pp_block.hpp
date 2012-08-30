#include "pp_expression.hpp"
#include "pp_statement.hpp"

class PPBlock : public PPExpression
{
    public:
        PPStatement::StatementList statements;
        
        PPBlock()
        {}
};
