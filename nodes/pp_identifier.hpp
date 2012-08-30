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
