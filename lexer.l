%option noyywrap

%{
      #include <iostream>
      #include <string>
    //  #include "ast.hpp"
      #include "cond.hpp"
      #include "parser.tab.hpp"
      
      
      
      
      
%}




%%

print { return PrintTk;}
var   { return VarTk; }
printbool { return PrintbTk; }
foreach { return ForEachTK; }
while { return WhileTk; }
if      { return IfTk; }
else    { return ElseTk; }
printstring { return PrintStrTk; }
[0-9]+ { yylval.numv = atoi(yytext); return NumTk; }
"!="   { return NeEqualTk;}
"<="   { return LessEqualTk; }
">="   { return GreaterEqualTk; }
"++" { return IncTk; }
"--" { return DecTk; }
[a-zA-Z_][a-zA-Z0-9]* { yylval.var = new string(yytext); return NameTk;}
\"[a-zA-Z_][a-z0-9A-Z ]*\" { yylval.s = new std::string(yytext); return StrTk; }
[()%=+<>;{}/*-] { return *yytext; }
"=="   { return EqualTk;}
[ \t] { }

. {
      std::cerr << "Lexical error: " << *yytext << std::endl;
      exit(EXIT_FAILURE);
  }


%%
