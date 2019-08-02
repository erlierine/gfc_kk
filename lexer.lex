%option noyywrap
%option nounput
%option noinput

%{
    #include <iostream>
    #include <string>
    #include "ast.hpp"
    
    #include "parser.tab.hpp"
%}

%%
"if"        return if_token;
"else"      return else_token;
"for"       return for_token;
"printf"    return print_token;
"while"     return while_token;
"++"        return incr_token;
"--"        return decr_token;
"=="        return eq_token;
"!="        return neq_token;
"<="        return lte_token;
">="        return gte_token;
\"([^\"])*\"      {
  std::string tmp(yytext);
  tmp = tmp.substr(1, tmp.size() - 2);
  yylval.s = new std::string(tmp);
  return string_token;
}
[a-zA-Z_][a-zA-Z_0-9]*  {
    yylval.s = new std::string(yytext);
    return id_token;
}
[0-9]+   {
    yylval.d = atof(yytext);
    return num_token;
}
"0x"[a-fA-F0-9]+  {
  sscanf(yytext, "%x", &yylval.d);
  return num_token;
}
[-%+*/(){}\[\],<>=;] return *yytext;
[ \t\n]     {}
.   {
    std::cerr << "Leksicka greska. Neprepoznat karakter '" << *yytext << "'." << std::endl; 
    exit(EXIT_FAILURE);
}
%%