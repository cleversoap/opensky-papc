#ifndef PAP_NODES_PPEXPRESSION_HPP_
#define PAP_NODES_PPEXPRESSION_HPP_

#include <vector>

#include "pp_node.h"

class PPExpression : public PPNode
{
    typedef std::vector<PPExpression*> ExpressionList;
};

#endif