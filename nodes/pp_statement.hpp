#include <vector>

#include "pp_node.h"

class PPStatement : public PPNode
{
    typedef std::vector<PPStatement*> StatementList;
};
