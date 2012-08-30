#include <vector>

#include "pp_statement.hpp"
#include "pp_expression.hpp"
#include "pp_identifier.hpp"

class PPVariableDeclaration : public PPStatement
{
    typedef std::vector<PPVariableDeclaration*> VariableList;
    
    public:
        const PPIdentifier &type;
        PPIdentifier &id;
        PPExpression* assignmentExpression;

        PPVariableDeclaration(const PPIdentifier &type, PPIdentifier &id)
        : type(type), id(id)
        {}

        PPVariableDeclaration(const PPIdentifier &type, PPIdentifier &id, PPExpression* assignmentExpression)
        : type(type), id(id), assignmentExpression(assignmentExpression)
        {}
};
