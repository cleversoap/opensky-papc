#include "ppexpression.h"

class PPInteger : public PPExpression
{
    public:
        
        long long value;

        PPInteger(long long value)
        : value(value)
        {}
};
