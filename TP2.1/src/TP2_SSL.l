%option noyywrap
%option yylineno
%{
#include <stdio.h>
#include <string.h>
#include "funciones.h"

int acum=0;
nodo_Id_litCadena* lista_LitCadena = NULL;
nodo_Id_litCadena* lista_Identificadores = NULL;
NoReconocidos* lista_NoReconocidos = NULL;
ConstanteDecimal *listaDecimal = NULL;
ConstanteHexa *listaHexa = NULL;
ConstanteOctal *listaOctal = NULL;
ConstanteReal *listaReal = NULL;
ConstanteCaracter *listaCaracter = NULL;
Comentarios* listaComentariosDeUnaLinea = NULL;
Comentarios* listaComentariosDeMultiplesLineas = NULL;
NodoPalabrasRes* listaPalabrasReservadas = NULL;
nodoOperadores * listaOperadores = NULL;

%}

DIGITO_DECIMAL [0-9]
DIGITO_OCTAL [0-7]
DIGITO_HEXADECIMAL [a-fA-F0-9]
LETRA [a-zA-Z]

%%

[1-9]{DIGITO_DECIMAL}* {insertarDecimal(&listaDecimal, yytext);}
0{DIGITO_OCTAL}* {insertarOctal(&listaOctal, yytext);}
0[xX]{DIGITO_HEXADECIMAL}+ {insertarHexa(&listaHexa, yytext);}
\'[^\n']\' {insertarCaracter(&listaCaracter, yytext);}
\"[^\n"]*\" {lista_LitCadena = insertar_unico(yytext, lista_LitCadena, criterioLiteralesCadena);}
(char|float|void|int|struct|double|register|enum|union)  {InsertarPalabrasReservadas(&listaPalabrasReservadas,yytext);}
(if|else|while|do|switch|break|case|for|goto|continue|return)  {InsertarPalabrasReservadas(&listaPalabrasReservadas,yytext);}
(static|long|short|unsigned|signed|volatile|const|typedef|sizeof|default|_Packed|auto|extern)  {InsertarPalabrasReservadas(&listaPalabrasReservadas,yytext);}
({LETRA}|[_])({LETRA}|{DIGITO_DECIMAL}|[_])* {lista_Identificadores = insertar_unico(yytext, lista_Identificadores, criterioIdentificadores);}
[/]{2}(.)* {InsertarComent(&listaComentariosDeUnaLinea, yytext);}
[/][*](.|\n)*[*][/] {InsertarComent(&listaComentariosDeMultiplesLineas, yytext);}
"["|"]"|"("|")"|"{"|"}"|"."|"&"|"*"|"+"|"-"|"!"|"/"|"%"|"<"|">"|\||\=|"?"|":"|";"|","|"#" {InsertarListaOp(&listaOperadores,yytext);}
" ";
"\t";
"\n";
. {insertarNoReconocidos(&lista_NoReconocidos,yytext,yylineno);}

%%

int main(){
    yyin = fopen("entrada.txt", "r");
    yyout = fopen("salida.txt", "w");	
    yylex();
    printf("ERROR, NO LOGRAMOS DETECTAR PORQUE MOTIVO PASA ESTO. SE PRESENTA EN LA MAYORIA DE PRUEBAS QUE HICIMOS: \t%s\n",listaComentariosDeMultiplesLineas->Coment);

    BorrarComentarios(&listaComentariosDeMultiplesLineas);
    return 0;
}
