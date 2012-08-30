#include <vector>

#include "ppnode.h"

class PPExpression : public PPNode
{
    typedef std::vector<PPExpression*> ExpressionList;
};
