%{
	#include "node.h"
	NBlock* programBlock; // The top level root node of our final AST
	
	extern int yylex();
	void yyerror(const char* s) { std::cerr << "ERROR:\t" << s << std::endl; }
%}

// Represents the many different ways we can access our data
%union {
	Node* node;
	NBlock* block;
	NExpression* expr;
	NStatement* stmt;
	NIdentifier* ident;
	NVariableDeclaration* var_decl;
	std::vector<NVariableDeclaration*>* varvec;
	std::vector<NExpression*>* exprvec;
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

stmts : stmt { $$ = new NBlock(); $$->statements.push_back($<stmt>1); }
      | stmts stmt { $1->statements.push_back($<stmt>2); }
      ;

stmt : var_decl | func_decl
     | expr { $$ = new NExpressionStatement(*$1); }
     | TRETURN expr { $$ = new NReturn(*$2); }
     ;

block   : TRPAREN stmts TENDFUNCTION { $$ = $2 }
        | TRPAREN TENDFUNCTION { $$ = new NBlock(); }
        | TRPAREN stmts TENDEVENT { $$ = $2 }
        | TRPAREN TENDEVENT { $$ = new NBlock(); }
        ;

var_decl    : ident ident { $$ = new NVariableDeclaration(*$1, *$2); }
	        | ident ident TEQUAL expr { $$ = new NVariableDeclaration(*$1, *$2, $4); }
            ;

func_decl   : ident TFUNCTION ident TLPAREN func_decl_args block
		        { $$ = new NFunctionDeclaration(*$1, *$3, *$5, *$6); delete $5; }
            | TFUNCTION ident TLPAREN func_decl_args block
                { $$ = new NFunctionDeclaration(*(new NIdentifier("void")), *$2, *$4, *$5); delete $4; }
            | TEVENT ident TLPAREN func_decl_args block
                { $$ = new NEventDeclaration(*$2, *$4, *$5); delete $4; }
	        ;

func_decl_args : /*blank*/ { $$ = new VariableList(); }
	       | var_decl { $$ = new VariableList(); $$->push_back($<var_decl>1); }
	       | func_decl_args TCOMMA var_decl { $1->push_back($<var_decl>3); }
	       ;

ident : TIDENTIFIER { $$ = new NIdentifier(*$1); delete $1; }
      ;

numeric : TINTEGER { $$ = new NInteger(atol($1->c_str())); delete $1; }
	    | TDOUBLE { $$ = new NDouble(atof($1->c_str())); delete $1; }
	    ;

expr : ident TEQUAL expr { $$ = new NAssignment(*$<ident>1, *$3); }
     | ident TLPAREN call_args TRPAREN { $$ = new NMethodCall(*$1, *$3); delete $3; }
     | ident { $<ident>$ = $1; }
     | numeric
     | expr comparison expr { $$ = new NBinaryOperator(*$1, $2, *$3); }
     | TLPAREN expr TRPAREN { $$ = $2; }
     ;

call_args : /*blank*/ { $$ = new ExpressionList(); }
	  | expr { $$ = new ExpressionList(); $$->push_back($1); }
	  | call_args TCOMMA expr { $1->push_back($3); }
	  ;

comparison : TCEQ | TCNE | TCLT | TCLE | TCGT | TCGE 
	   | TPLUS | TMINUS | TMUL | TDIV
	   ;

%%
