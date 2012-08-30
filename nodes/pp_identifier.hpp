#ifndef PAP_NODES_PPIDENTIFIER_HPP_
#define PAP_NODES_PPIDENTIFIER_HPP_

#include <string>

#include "pp_expression.h"

class PPIdentifier : public PPExpression
{
    public:
        
        std::string name;

        PPIdentifier(const std::string &name)
        : name(name)
        {}
};

#endif // PAP_NODES_PPIDENTIFIER_HPP_