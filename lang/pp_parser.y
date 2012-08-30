%{
    #include <string>

    #include "pp_node.hpp"
    #include "pp_expression.hpp"
    #include "pp_statement.hpp"
    #include "pp_expression_statement.hpp"
	#include "pp_block.hpp"
    #include "pp_identifier.hpp"
    #include "pp_assignment.hpp"
    #include "pp_variable_declaration.hpp"
    #include "pp_function_declaration.hpp"
    #include "pp_function_call.hpp"
    #include "pp_event_declaration.hpp"
    #include "pp_return_statement.hpp"
    #include "pp_integer.hpp"
    #include "pp_float.hpp"

	PPBlock* programBlock; // The top level root node of our final AST
	
	extern int yylex();
	void yyerror(const char* s) { std::cerr << "ERROR:\t" << s << std::endl; }
%}

// Represents the many different ways we can access our data
%union {
	PPNode* node;
	PPBlock* block;
    PPExpression* expr;
	PPStatement* stmt;
	PPIdentifier* ident;
    PPVariableDeclaration* var_decl;
    PPVariableDeclaration::VariableList* varvec;
    PPExpression::ExpressionList* exprvec;
	std::string* string;
	int token;
}

// Define our terminal symbols (tokens). This should match our tokens.l lex file.
// We also define the node type they represent.
%token <string> TIDENTIFIER TINTEGER TDOUBLE
%token <token> TFUNCTION TENDFUNCTION
%token <token> TEVENT TENDEVENT
%token <token> TRETURN
%token <token> TCEQ TCNE TCLT TCLE TCGT TCGE TEQUAL
%token <token> TLPAREN TRPAREN TLBRACE TRBRACE TCOMMA TDOT
%token <token> TPLUS TMINUS TMUL TDIV

// Define the type of node our nonterminal symbols represent. The types refer to the
// %union declaration above. Ex: when we can an ident (defined by union type ident) we
// are really calling an (NIdentifier*). It makes the compiler happy.
%type <ident> ident
%type <expr> numeric expr
%type <varvec> func_decl_args
%type <exprvec> call_args
%type <block> program stmts block
%type <stmt> stmt var_decl func_decl
%type <token> comparison

// Operator precedence for mathematical operators
%left TPLUS TMINUS
%left TMUL TDIV

%start program

%%

program : stmts { programBlock = $1; }
	    ;

stmts : stmt { $$ = new PPBlock(); $$->statements.push_back($<stmt>1); }
      | stmts stmt { $1->statements.push_back($<stmt>2); }
      ;

stmt : var_decl | func_decl
     | expr { $$ = new PPExpressionStatement(*$1); }
     | TRETURN expr { $$ = new PPReturnStatement(*$2); }
     ;

block   : TRPAREN stmts TENDFUNCTION { $$ = $2 }
        | TRPAREN TENDFUNCTION { $$ = new PPBlock(); }
        | TRPAREN stmts TENDEVENT { $$ = $2 }
        | TRPAREN TENDEVENT { $$ = new PPBlock(); }
        ;

var_decl    : ident ident { $$ = new PPVariableDeclaration(*$1, *$2); }
	        | ident ident TEQUAL expr { $$ = new PPVariableDeclaration(*$1, *$2, $4); }
            ;

func_decl   : ident TFUNCTION ident TLPAREN func_decl_args block
		        { $$ = new PPFunctionDeclaration(*$1, *$3, *$5, *$6); delete $5; }
            | TFUNCTION ident TLPAREN func_decl_args block
                { $$ = new PPFunctionDeclaration(*(new PPIdentifier("void")), *$2, *$4, *$5); delete $4; }
            | TEVENT ident TLPAREN func_decl_args block
                { $$ = new PPEventDeclaration(*$2, *$4, *$5); delete $4; }
	        ;

func_decl_args : /*blank*/ { $$ = new PPVariableDeclaration::VariableList(); }
	       | var_decl { $$ = new PPVariableDeclaration::VariableList(); $$->push_back($<var_decl>1); }
	       | func_decl_args TCOMMA var_decl { $1->push_back($<var_decl>3); }
	       ;

ident : TIDENTIFIER { $$ = new PPIdentifier(*$1); delete $1; }
      ;

numeric : TINTEGER { $$ = new PPInteger(atol($1->c_str())); delete $1; }
	    | TDOUBLE { $$ = new PPFloat(atof($1->c_str())); delete $1; }
	    ;

expr : ident TEQUAL expr { $$ = new PPAssignment(*$<ident>1, *$3); }
     | ident TLPAREN call_args TRPAREN { $$ = new PPFunctionCall(*$1, *$3); delete $3; }
     | ident { $<ident>$ = $1; }
     | numeric
     | expr comparison expr { $$ = new PPBinaryOperator(*$1, $2, *$3); }
     | TLPAREN expr TRPAREN { $$ = $2; }
     ;

call_args : /*blank*/ { $$ = new PPExpression::ExpressionList(); }
	  | expr { $$ = new PPExpression::ExpressionList(); $$->push_back($1); }
	  | call_args TCOMMA expr { $1->push_back($3); }
	  ;

comparison : TCEQ | TCNE | TCLT | TCLE | TCGT | TCGE 
	   | TPLUS | TMINUS | TMUL | TDIV
	   ;

%%
