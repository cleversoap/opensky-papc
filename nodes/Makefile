CFLAGS += -c -fPIC

all: assignment binary_operator block event_declaration expression expression_statement float function_call function_declaration identifier integer node return_statement statement variable_declaration

clean:
	rm -rf *.gch *.o

assignment: expression identifier
	${CC} ${CFLAGS} pp_assignment.hpp -o pp_assignment.o

binary_operator: expression
	${CC} ${CFLAGS} pp_binary_operator.hpp -o pp_binary_operator.o

block: expression statement
	${CC} ${CFLAGS} pp_block.hpp -o pp_block.o

event_declaration: function_declaration variable_declaration identifier block
	${CC} ${CFLAGS} pp_event_declaration.hpp -o pp_event_declaration.o

expression: node
	${CC} ${CFLAGS} pp_expression.hpp -o pp_expression.o

expression_statement: expression statement
	${CC} ${CFLAGS} pp_expression_statement.hpp -o pp_expression_statement.o

float: expression
	${CC} ${CFLAGS} pp_float.hpp -o pp_float.o

function_call: expression identifier
	${CC} ${CFLAGS} pp_function_call.hpp -o pp_function_call.o

function_declaration: statement identifier variable_declaration block
	${CC} ${CFLAGS} pp_function_declaration.hpp -o pp_function_declaration.o

identifier: expression
	${CC} ${CFLAGS} pp_identifier.hpp -o pp_identifier.o

integer: expression
	${CC} ${CFLAGS} pp_integer.hpp -o pp_integer.o

node:
	${CC} ${CFLAGS} pp_node.hpp -o pp_node.o

return_statement: statement expression
	${CC} ${CFLAGS} pp_return_statement.hpp -o pp_return_statement.o

statement: node
	${CC} ${CFLAGS} pp_statement.hpp -o pp_statement.o

variable_declaration: statement expression identifier
	${CC} ${CFLAGS} pp_variable_declaration.hpp -o pp_variable_declaration.o