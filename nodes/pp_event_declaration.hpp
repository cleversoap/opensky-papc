#ifndef PAP_NODES_PPEVENTDECLARATION_HPP_
#define PAP_NODES_PPEVENTDECLARATION_HPP_

#include "pp_function_declaration.hpp"
#include "pp_variable_declaration.hpp"
#include "pp_identifier.hpp"
#include "pp_block.hpp"

class PPEventDeclaration : public PPFunctionDeclaration
{
    public:
        PPEventDeclaration(const PPIdentifier &id, const PPVariableDeclaration::VariableList &arguments, PPBlock &block)
        : PPFunctionDeclaration(*(new PPIdentifier("void")), id, arguments, block)
        {}
};

#endif // PAP_NODES_PPEVENTDECLARATION_HPP_