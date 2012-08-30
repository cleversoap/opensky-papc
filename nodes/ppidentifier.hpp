#include <string>

#include "ppexpression.h"


class PPIdentifier : public PPExpression
{
    public:
        
        std::string name;

        PPIdentifier(const std::string &name)
        : name(name)
        {}
};
