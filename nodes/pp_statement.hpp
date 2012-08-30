#ifndef PAP_NODES_PPSTATEMENT_HPP_
#define PAP_NODES_PPSTATEMENT_HPP_

#include <vector>

#include "pp_node.hpp"

class PPStatement : public PPNode
{
    public:
        typedef std::vector<PPStatement*> StatementList;
};

#endif // PAP_NODES_PPSTATEMENT_HPP_
