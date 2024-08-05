%option noyywrap
%option yylineno
%{
#include <stdio.h>
#include <string.h>
#include "TP4.tab.h"

%}

DIGITO_DECIMAL [0-9]
DIGITO_OCTAL [0-7]
DIGITO_HEXADECIMAL [a-fA-F0-9]
LETRA [a-zA-Z] 
OPERADOR "["|"]"|"("|")"|"{"|"}"|"."|"&"|"*"|"+"|"-"|"!"|"/"|"%"|"<"|">"|\||\=|"?"|":"|";"|","|"#"
PALABRA_RESERVADA_TIPODATO char|float|void|int|struct|double|register|enum|union
PALABRA_RESERVADA_OTROS static|long|short|unsigned|signed|volatile|const|typedef|_Packed|auto|extern|sizeof

%%
if       { return IF; }
else     { return ELSE; }
while    { return WHILE; }
do       { return DO; }
switch   { return SWITCH; }
break    { return BREAK; }
case     { return CASE; }
for      { return FOR; }
goto     { return GOTO; }
continue { return CONTINUE; }
return   { return RETURN; }
default  { return DEFAULT; }

"==" { return IGUALDAD; }
"+=" { return ASIGNACION_INCREMENTO; }
"&&" { return AND; }
"||" { return OR; }
"!=" { return DISTINTO; }
">=" { return MAYOR_IGUAL; }
"<=" { return MENOR_IGUAL; }
"++" { return INCREMENTO; }
"--" { return DECREMENTO; }

[1-9]{DIGITO_DECIMAL}*          { yylval.mystruct.entero = atoi(yytext); return NUM_ENTERO; } /* Decimal */ 
0{DIGITO_OCTAL}*                { yylval.mystruct.entero = atoi(yytext); return NUM_ENTERO; } /* Octal */ 
0[xX]{DIGITO_HEXADECIMAL}+      { yylval.mystruct.entero = atoi(yytext); return NUM_ENTERO; } /* Hexadecimal */

\'[^\n']\'                      { return CHAR; } /* Caracter */
\"[^\n"]*\"                     { yylval.mystruct.cadena = strdup(yytext); return LIT_CADENA; }             /* literal Cadena*/

{PALABRA_RESERVADA_TIPODATO}    { yylval.mystruct.cadena = strdup(yytext); return TIPO_DATO;}               /* Palabra Reservada de TIPO */
{PALABRA_RESERVADA_OTROS}       { yylval.mystruct.cadena = strdup(yytext); return OTROS;}       /* Palabra Reservada OTROS */

({LETRA}|[_])({LETRA}|{DIGITO_DECIMAL}|[_])* { yylval.mystruct.cadena = strdup(yytext); return ID;}         /* Identificador */

[/]{2}.*$ {;}                       /* Comentario de linea */
[/][*](.|\n)*[*][/] {;}             /* Comentario de Multiples Lineas */

{OPERADOR} { return yytext[0]; }    /* Operadores */

"\n"|" " {;}                        /* Saltos de linea y espacios */

. { yylval.mystruct.cadena = strdup(yytext); return ERROR_LEXICO; }

%%







