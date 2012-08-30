#ifndef PAP_NODES_PPVARIABLEDECLARATION_HPP_
#define PAP_NODES_PPVARIABLEDECLARATION_HPP_

#include <vector>

#include "pp_statement.hpp"
#include "pp_expression.hpp"
#include "pp_identifier.hpp"

class PPVariableDeclaration : public PPStatement
{
    public:
        typedef std::vector<PPVariableDeclaration*> VariableList;
    
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

#endif // PAP_NODES_PPVARIABLEDECLARATION_HPP_
