#ifndef PAP_NODES_PPSTATEMENT_HPP_
#define PAP_NODES_PPSTATEMENT_HPP_

#include <vector>

#include "pp_node.h"

class PPStatement : public PPNode
{
    typedef std::vector<PPStatement*> StatementList;
};

#endif // PAP_NODES_PPSTATEMENT_HPP_