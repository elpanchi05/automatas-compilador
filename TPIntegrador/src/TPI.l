%option noyywrap
%option yylineno
%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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

{DIGITO_DECIMAL}+\.{DIGITO_DECIMAL}*([eE](\+|-)?[0-9]+)?    { yylval.mystruct.real = atof(yytext); yylval.mystruct.tipo = 259; return NUM_REAL; }                 /* Reales */
[1-9]{DIGITO_DECIMAL}*          { yylval.mystruct.cadena = strdup("int"); yylval.mystruct.entero = atoi(yytext); yylval.mystruct.tipo = 258; return NUM_ENTERO; } /* Decimal */ 
0{DIGITO_OCTAL}*                { yylval.mystruct.cadena = strdup("int"); yylval.mystruct.entero = atoi(yytext); yylval.mystruct.tipo = 258; return NUM_ENTERO; } /* Octal */ 
0[xX]{DIGITO_HEXADECIMAL}+      { yylval.mystruct.cadena = strdup("int"); yylval.mystruct.entero = atoi(yytext); yylval.mystruct.tipo = 258; return NUM_ENTERO; } /* Hexadecimal */

\'[^\n']\'                      { yylval.mystruct.cadena = strdup("char"); yylval.mystruct.tipo = 260; return CHAR; }   /* Caracter */
\"[^\n"]*\"                     { yylval.mystruct.cadena = strdup(yytext); yylval.mystruct.tipo = 263; return LIT_CADENA; }                         /* literal Cadena*/

{PALABRA_RESERVADA_TIPODATO}    { yylval.mystruct.cadena = strdup(yytext); return TIPO_DATO;}                           /* Palabra Reservada de TIPO */
{PALABRA_RESERVADA_OTROS}       {;}       /* Palabra Reservada OTROS */

({LETRA}|[_])({LETRA}|{DIGITO_DECIMAL}|[_])* { yylval.mystruct.cadena = strdup(yytext); yylval.mystruct.tipo = 262; return ID;}                     /* Identificador */

[/]{2}.*$ {;}                       /* Comentario de linea */
[/][*](.|\n)*[*][/] {;}             /* Comentario de Multiples Lineas */

{OPERADOR} { return yytext[0]; }    /* Operadores */

"\n"|" " {;}                        /* Saltos de linea y espacios */

. { yylval.mystruct.cadena = strdup(yytext); return ERROR_LEXICO; }

%%