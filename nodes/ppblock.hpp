#include "ppexpression.hpp"
#include "ppstatement.hpp"

class PPBlock : public PPExpression
{
    public:
        PPStatement::StatementList statements;
        
        PPBlock()
        {}
};
