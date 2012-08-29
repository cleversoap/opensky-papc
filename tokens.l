%{
#include <string.h>
#include "node.h"
#include "parser.hpp"
#define SAVE_TOKEN yylval.string = new std::string(yytext, yyleng)
#define TOKEN(t) (yylval.token = t)
extern "C" int yywrap() { }
%}

%%

[ \t\n]			        ;
"return"                return TOKEN(TRETURN);
"Event"                 return TOKEN(TEVENT);
"endEvent"              return TOKEN(TENDEVENT);
"Function"              return TOKEN(TFUNCTION);
"endFunction"           return TOKEN(TENDFUNCTION);
[a-zA-Z_][a-zA-Z0-9_]*	SAVE_TOKEN; return TIDENTIFIER;
[0-9]+\.[0-9]*		    SAVE_TOKEN; return TDOUBLE;
[0-9]+			        SAVE_TOKEN; return TINTEGER;
"="			            return TOKEN(TEQUAL);
"=="			        return TOKEN(TCEQ);
"!="			        return TOKEN(TCNE);
"<"			            return TOKEN(TCLT);
"<="			        return TOKEN(TCLE);
">"			            return TOKEN(TCGT);
">="			        return TOKEN(TCGE);
"("			            return TOKEN(TLPAREN);
")"			            return TOKEN(TRPAREN);
"{"			            return TOKEN(TLBRACE);
"}"			            return TOKEN(TRBRACE);
"."			            return TOKEN(TDOT);
","			            return TOKEN(TCOMMA);
"+"			            return TOKEN(TPLUS);
"-"			            return TOKEN(TMINUS);
"*"			            return TOKEN(TMUL);
"/"			            return TOKEN(TDIV);
.			            std::cerr << "Unknown token!" << std::endl; yyterminate();

%%
