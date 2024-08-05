%{
#include <stdio.h>
#include <string.h>
#include "funciones.c"

FILE* yyin;
int yylineno;

int yylex();
int yywrap(){
	return(1);
}
void yyerror (char const *s) {
   // printf ("%s\n", s); 
   // Borramos el mensaje de "syntax error".
}

char* descripcionSentencia;
nodoVariable* listaIDS = NULL;

nodoErrorLexico* lista_errores_lexicos = NULL;
nodoVariable* lista_Variables = NULL;
nodoSentencia* lista_sentencias = NULL;
nodoFuncion* lista_Funciones = NULL;

%}

%union {
   struct mytruct
   {
        int tipo;
        int entero;
        float real;
        char* cadena;
        char caracter;
   } mystruct;

}

%token <mystruct> NUM_ENTERO
%token <mystruct> NUM_REAL
%token <mystruct> CHAR
%token <mystruct> ERROR_LEXICO OTROS ID LIT_CADENA TIPO_DATO IF DEFAULT ELSE WHILE DO SWITCH BREAK CASE FOR GOTO CONTINUE RETURN IGUALDAD ASIGNACION_INCREMENTO AND OR DISTINTO MAYOR_IGUAL MENOR_IGUAL INCREMENTO DECREMENTO 

%left '+' '-'
%left '*' '/'
%left '^'
%left '(' ')'

%%

input:                  /* vacio */
                        | input line
;

line:                   ERROR_LEXICO { insertarErrorLexico(&lista_errores_lexicos, $<mystruct.cadena>1, yylineno);}
                        | sentencia 
                        | error { printf("Error en linea %d.\n", yylineno);}
;

/* EXPRESIONES */

expresion :             expAsignacion
                        | expresion ',' expAsignacion
;

expAsignacion :         expCondicional
                        | ID opAsignacion expOr
;

expCondicional :        expOr
                        | expOr '?' expresion ':' expCondicional
;

opAsignacion :          '=' | ASIGNACION_INCREMENTO 
;

expOr :                 expAnd
                        | expOr OR expAnd
;

expAnd :                expIgualdad
                        | expAnd AND expIgualdad
;

expIgualdad :           expRelacional
                        | expIgualdad IGUALDAD expRelacional
                        | expIgualdad DISTINTO expRelacional
;

expRelacional :         expAditiva
                        | expRelacional opRelacional expAditiva
;

opRelacional :          '>' | '<' | MAYOR_IGUAL | MENOR_IGUAL
;

expAditiva :            expMultiplicativa 
                        | expAditiva '+' expMultiplicativa
                        | expAditiva '-' expMultiplicativa
;

expMultiplicativa :     expUnaria
                        | expMultiplicativa '/' expUnaria
                        | expMultiplicativa '*' expUnaria
                        | expMultiplicativa '%' expUnaria
;

expUnaria :             expPrimaria
                        | INCREMENTO expUnaria
                        | DECREMENTO expUnaria
;

expPrimaria :           ID
                        | NUM_ENTERO
                        | NUM_REAL
                        | LIT_CADENA
                        | CHAR
                        | '(' expresion ')'
;

/* SENTENCIAS */

sentencia:              declaracion 
                        | sentencia_expresion 
                        | sentencia_compuesta 
                        | sentencia_seleccion   { insertarSentencia(&lista_sentencias,"Seleccion", descripcionSentencia, yylineno);}
                        | sentencia_iteracion   { insertarSentencia(&lista_sentencias, "Iteracion", descripcionSentencia, yylineno);}
                        | sentencia_etiquetada  { insertarSentencia(&lista_sentencias, "Etiquetado", descripcionSentencia, yylineno);}
                        | sentencia_de_salto    { insertarSentencia(&lista_sentencias, "Salto", descripcionSentencia, yylineno);}
                        | sentencia ';' sentencia
;

sentencia_expresion:    expresion ';' 
                        | ';'
;

sentencia_compuesta:    '{' '}'
                        | '{' lista_de_declaraciones  '}'
                        | '{' lista_de_sentencias '}'
                        | '{' lista_de_declaraciones lista_de_sentencias '}'
;

sentencia_seleccion:    IF '(' expCondicional ')' sentencia {descripcionSentencia = strdup("if");}
                        | IF '(' expCondicional ')' sentencia ELSE sentencia {descripcionSentencia = strdup("if else");}
                        | SWITCH '(' expCondicional ')' sentencia {descripcionSentencia = strdup("switch");}
;

sentencia_iteracion:    WHILE '(' expCondicional ')' sentencia {descripcionSentencia = strdup("while");}
                        | DO sentencia WHILE '(' expCondicional ')' ';' {descripcionSentencia = strdup("do while");}
                        | FOR '(' declaracion ';' expCondicional ';' expUnaria ')' sentencia {descripcionSentencia = strdup("for");}
;

sentencia_etiquetada:   CASE expCondicional ':' sentencia {descripcionSentencia = strdup("case");}
                        | DEFAULT ':' sentencia {descripcionSentencia = strdup("default");}
                        | ID ':' sentencia {descripcionSentencia = strdup("id");}
; 

sentencia_de_salto:     CONTINUE ';' {descripcionSentencia = strdup("continue");}
                        | BREAK ';' {descripcionSentencia = strdup("break");}
                        | RETURN expresion ';' {descripcionSentencia = strdup("return");}
                        | GOTO ID ';' {descripcionSentencia = strdup("goto");}
;

lista_de_sentencias:    sentencia
                        | lista_de_sentencias sentencia
;

/* DECLARACIONES */

declaracion:            TIPO_DATO listaIdentificadores ';' {
                              while(listaIDS != NULL){ // union de ambas listas
                                 insertarVariable(&lista_Variables,listaIDS->nombre,$<mystruct.cadena>1, listaIDS->linea);
                                 listaIDS = listaIDS->siguiente;
                              }
                           }
                        | TIPO_DATO ID '(' listaParametros ')' ';'                  { insertarFuncion(&lista_Funciones, $<mystruct.cadena>2, $<mystruct.cadena>1, yylineno); }
                        | TIPO_DATO ID '(' listaParametros ')' sentencia_compuesta  { insertarFuncion(&lista_Funciones, $<mystruct.cadena>2, $<mystruct.cadena>1, yylineno); }
;

listaIdentificadores:   identificador
                        | identificador ',' listaIdentificadores
;

identificador:          ID                   {insertarVariable(&listaIDS, $<mystruct.cadena>1, "-", yylineno);}
                        | ID '=' expAditiva  {insertarVariable(&listaIDS, $<mystruct.cadena>1, "-", yylineno);}
;

listaParametros:        parametro
                        | parametro ',' listaParametros
;

parametro:              /* Caso particular en el cual no posee argumentos.*/
                        |TIPO_DATO ID
;

lista_de_declaraciones: declaracion
                        | lista_de_declaraciones declaracion
;

%%

int main(){
   yyin = fopen("ArchivoFuente.c","r");
   // Presentacion listado de errores sintacticos
   printf("********\t\tLISTADO ERRORES SINTACTICOS\t\t********\n\n");  
   yyparse();
   fclose(yyin);

   // INFORME
   mostrarErroresLexicos(&lista_errores_lexicos);
   mostrarVariables(&lista_Variables);
   mostrarSentencias(&lista_sentencias);
   mostrarFunciones(&lista_Funciones);

   return 0;
}