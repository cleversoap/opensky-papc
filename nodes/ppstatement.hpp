#include <vector>

#include "ppnode.h"

class PPStatement : public PPNode
{
    typedef std::vector<PPStatement*> StatementList;
};
