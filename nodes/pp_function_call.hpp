#include "pp_expression.hpp"
#include "pp_identifier.hpp"

class PPFunctionCall : public PPExpression
{
    public:
        const PPIdentifier &id;
        PPExpression::ExpressionList arguments;

        PPFunctionCall(const PPIdentifier &id, PPExpression::ExpressionList &arguments)
        : id(id), arguments(arguments)
        {}

        PPFunctionCall(const PPIdentifier &id)
        : id(id)
        {}
};
