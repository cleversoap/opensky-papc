#ifndef PAP_NODES_PPFUNCTIONDECLARATION_HPP_
#define PAP_NODES_PPFUNCTIONDECLARATION_HPP_

#include "pp_statement.hpp"
#include "pp_identifier.hpp"
#include "pp_variable_declaration.hpp"
#include "pp_block.hpp"

class PPFunctionDeclaration : public PPStatement
{
    public:
        const PPIdentifier &type;
        const PPIdentifier &id;
        PPVariableDeclaration::VariableList arguments;
        PPBlock &block;

        PPFunctionDeclaration(const PPIdentifier &type, const PPIdentifier &id, const PPVariableDeclaration::VariableList &arguments, PPBlock &block)
        : type(type), id(id), arguments(arguments), block(block)
        {}
}

#endif // PAP_NODES_PPFUNCTIONDECLARATION_HPP_