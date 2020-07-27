%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokens.h"

/* error messages */
char *token_err_msg = "Unknown Token: line %d";


/* add your variable/function declarations here */
int line_number = 1;
int id_counter = 1;
char name_of_id[20];

%}

%option never-interactive 
	/*supress unnecessary warning*/

 /* lex comments: cannot start with the leftmost location of a line */
 /* add your regular definitions here */
/*Starting character sequence for multiline comment*/ 
start \! 
/*Ending character sequence for multiline comment*/ 
end  [\n]

%%

\+		{return(PLUS);}
\-		{return(MINUS);}
\*		{return(MULTIPLY);}
\/		{return(DIVIDE);}
\=		{return(ASSIGNMENT);}
\==		{return(EQUALITY);}
\<		{return(LESSTHAN);}
\>		{return(GREATERTHAN);}
\<=		{return(LESSTHANOREQUALS);}
\>=		{return(GREATERTHANOREQUALS);}
\<>		{return(NOTEQUALS);}
\(		{return(LEFTB);}
\)		{return(RIGHTB);}
\:		{return(COLON);}
\,		{return(COMMA);}
\def	{return(DEF);}
\enddef	{return(ENDDEF);}
\if		{return(IF);}
\endif	{return(ENDIF);}
\else	{return(ELSE);}
\while	{return(WHILE);}
\endwhile	{return(ENDWHILE);}
\print		{return(PRINT);}
\input		{return(INPUT);}
"true"		{return(TRUE);}
"false"		{return(FALSE);}
"return"		{return(RETURN);}
[a-zA-Z_][a-zA-Z0-9_]*	{strcpy(name_of_id, yytext);id_counter++; return(IDENTIFIER);}
[0-9]*[0-9]+			{return(NUMBER);}
[\"][a-zA-Z0-9_]+[\"]	{return(STRING);}
{start}.* ;
\t		{;}
" "		{;}
\n		{line_number++;}
.	return(TOKEN);  /*default behavior*/

%%



