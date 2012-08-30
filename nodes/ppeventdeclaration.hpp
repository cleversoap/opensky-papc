#include "ppfunctiondeclaration.hpp"
#include "ppvariabledeclaration.hpp"
#include "ppidentifier.hpp"
#include "ppblock.hpp"

class PPEventDeclaration : public PPFunctionDeclaration
{
    public:
        PPEventDeclaration(const PPIdentifier &id, const PPVariableDeclaration::VariableList &arguments, PPBlock &block)
        : PPFunctionDeclaration(*(new PPIdentifier("void")), id, arguments, block)
        {}
};
