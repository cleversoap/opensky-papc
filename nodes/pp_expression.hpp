#ifndef PAP_NODES_PPEXPRESSION_HPP_
#define PAP_NODES_PPEXPRESSION_HPP_

#include <vector>

#include "pp_node.hpp"

class PPExpression : public PPNode
{
    public:
        typedef std::vector<PPExpression*> ExpressionList;
};

#endif
