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
printbool { return PrintbTk; }
foreach { return ForEachTK; }
while { return WhileTk; }
if      { return IfTk; }
else    { return ElseTk; }
printstring { return PrintStrTk; }
[0-9]+ { yylval.numv = atoi(yytext); return NumTk; }
"=="   { return EqualTk;}
"!="   { return NeEqualTk;}
"<="   { return LessEqualTk; }
">="   { return GreaterEqualTk; }
"++" { return IncTk; }
"--" { return DecTk; }
[a-zA-Z_][a-zA-Z0-9]* { yylval.var = new string(yytext); return VarTk;}
\"[a-zA-Z_][a-z0-9A-Z ]*\" { yylval.s = new std::string(yytext); return StrTk; }
[()%=+<>;{}/*-] { return *yytext; }
[ \t] { }

. {
      std::cerr << "Lexical error: " << *yytext << std::endl;
      exit(EXIT_FAILURE);
  }


%%
