#include "ppexpression.hpp"

class PPFloat : public PPExpression
{
    public:
        double value;
        
        PPFloat(double value)
        : value(value)
        {}
};
