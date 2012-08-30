#include "ppstatement.hpp"
#include "ppidentifier.hpp"
#include "ppvariabledeclaration.hpp"
#include "ppblock.hpp"

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
