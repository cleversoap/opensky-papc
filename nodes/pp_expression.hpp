#include <vector>

#include "pp_node.h"

class PPExpression : public PPNode
{
    typedef std::vector<PPExpression*> ExpressionList;
};
