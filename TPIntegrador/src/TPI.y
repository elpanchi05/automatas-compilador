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

// VARIABLES GLOBALES AUXILIARES
char* descripcionSentencia;
nodoVariable* listaIDS     = NULL;
nodoParametro* parametros  = NULL;
int cantidad_parametros    = 0;

// TABLA DE SIMBOLOS
nodoErrorLexico*     lista_errores_lexicos = NULL;
nodoErrorSemantico*  lista_errores_semanticos = NULL;
nodoVariable*        lista_Variables = NULL;
nodoSentencia*       lista_sentencias = NULL;
nodoFuncion*         lista_Funciones = NULL;

%}

%union {
   struct mytruct{
        int tipo, entero;
        float real;
        char* cadena;
        char caracter;
   } mystruct;
}

%token <mystruct> NUM_ENTERO
%token <mystruct> NUM_REAL
%token <mystruct> CHAR
%token <mystruct> ERROR_LEXICO ID LIT_CADENA TIPO_DATO IF DEFAULT ELSE WHILE DO SWITCH BREAK CASE FOR GOTO CONTINUE RETURN IGUALDAD ASIGNACION_INCREMENTO AND OR DISTINTO MAYOR_IGUAL MENOR_IGUAL INCREMENTO DECREMENTO 

%type <mystruct> expPrimaria

%left '+' '-'
%left '*' '/'
%left '^'
%left '(' ')'

%%

input:                  /* vacio */
                        | input line
;

line:                   ERROR_LEXICO   { insertarErrorLexico(&lista_errores_lexicos, $<mystruct.cadena>1, yylineno);}
                        | sentencia 
                        | error        { printf("Error en linea %d.\n", yylineno);}
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
                        | expRelacional opRelacional expAditiva { 
                           
                           if( $<mystruct.tipo>1 == 262 && $<mystruct.tipo>3 == 262 ){             // Caso donde alguno de los dos sea una variable, checkea en TS su tipo.
                              char* primerTipo  = obtenerTipoVariable(&lista_Variables, $<mystruct.cadena>1);
                              char* segundoTipo = obtenerTipoVariable(&lista_Variables, $<mystruct.cadena>3);
                              
                              // TODO: no funciona para casos de var-const. 
                              // AVISO: el goto es usado para que no salgan multiples errores para una misma linea.

                              if( strcmp("",primerTipo)==0 || strcmp("",segundoTipo)==0 ){         // Alguno de ellos no esta en la TS.
                                 insertarErrorSemantico(&lista_errores_semanticos, "Variable no declarada.\t\t\t", yylineno);
                                 goto jump;
                              }                              
                              if( controlDeTiposVar(primerTipo, segundoTipo) == 1 ){               // Checkea que ambos posean el mismo tipo.
                                 insertarErrorSemantico(&lista_errores_semanticos, "Error de tipos.\t\t\t\t", yylineno);
                                 goto jump;
                              }
                           }
                           if( controlDeTiposNum($<mystruct.tipo>1, $<mystruct.tipo>3)==1 ){
                              insertarErrorSemantico(&lista_errores_semanticos, "Error de tipos.\t\t\t\t", yylineno);
                           }
                           jump: 
                        }
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
                        | expUnaria INCREMENTO
                        | expUnaria DECREMENTO
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
                        | sentencia_invocacion  
                        | sentencia_expresion   
                        | sentencia_compuesta   { insertarSentencia(&lista_sentencias, "Compuesta", "-", yylineno); }
                        | sentencia_seleccion   { insertarSentencia(&lista_sentencias, "Seleccion", descripcionSentencia, yylineno);}
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

sentencia_seleccion:    IF '(' expCondicional ')' sentencia                   {descripcionSentencia = strdup("if");}
                        | IF '(' expCondicional ')' sentencia ELSE sentencia  {descripcionSentencia = strdup("if else");}
                        | SWITCH '(' expCondicional ')' sentencia             {descripcionSentencia = strdup("switch");}
;

sentencia_iteracion:    WHILE '(' expCondicional ')' sentencia                               {descripcionSentencia = strdup("while");}
                        | DO sentencia WHILE '(' expCondicional ')' ';'                      {descripcionSentencia = strdup("do while");}
                        | FOR '(' declaracion ';' expCondicional ';' expUnaria ')' sentencia {descripcionSentencia = strdup("for");}
;

sentencia_etiquetada:   CASE expCondicional ':' sentencia   {descripcionSentencia = strdup("case");}
                        | DEFAULT ':' sentencia             {descripcionSentencia = strdup("default");}
                        | ID ':' sentencia                  {descripcionSentencia = strdup("id");}
;

sentencia_de_salto:     CONTINUE ';'            {descripcionSentencia = strdup("continue");}
                        | BREAK ';'             {descripcionSentencia = strdup("break");}
                        | RETURN expresion ';'  {descripcionSentencia = strdup("return");}
                        | GOTO ID ';'           {descripcionSentencia = strdup("goto");}
;

lista_de_sentencias:    sentencia                        
                        | lista_de_sentencias sentencia  
;

sentencia_invocacion:   ID '(' lista_expPrimaria ')' ';' { 
                           rutinaInvocacion(&lista_Funciones, &parametros, &lista_errores_semanticos, $<mystruct.cadena>1, cantidad_parametros, yylineno);
                           cantidad_parametros = 0; parametros = NULL;  //Reinicio de valores.
                           }
;

lista_expPrimaria:      /* Funcion no posee parametros */        { cantidad_parametros++; insertarParametro(&parametros, "no posee"); }
                        | expPrimaria                            { cantidad_parametros++; insertarParametro(&parametros, $<mystruct.cadena>1); }
                        | expPrimaria ',' lista_expPrimaria      { cantidad_parametros++; insertarParametro(&parametros, $<mystruct.cadena>1); }
;

/* DECLARACIONES */

declaracion:            TIPO_DATO listaIdentificadores ';' {
                              while(listaIDS != NULL){ // union de ambas listas
                                 insertarVariable(&lista_Variables,listaIDS->nombre,$<mystruct.cadena>1, listaIDS->linea);
                                 listaIDS = listaIDS->siguiente;
                              }
                           }
                        | TIPO_DATO ID '(' listaParametros ')' ';'                  { insertarFuncion(&lista_Funciones, $<mystruct.cadena>2, $<mystruct.cadena>1 ,cantidad_parametros, parametros, yylineno); cantidad_parametros = 0; parametros = NULL; }
                        | TIPO_DATO ID '(' listaParametros ')' sentencia_compuesta  { insertarFuncion(&lista_Funciones, $<mystruct.cadena>2, $<mystruct.cadena>1 ,cantidad_parametros, parametros, yylineno); cantidad_parametros = 0; parametros = NULL; }
;

listaIdentificadores:   identificador
                        | identificador ',' listaIdentificadores
;

identificador:          ID                   { if(chequeoDobleDeclaracion(&lista_Variables, $<mystruct.cadena>1) == 1){
                                                   insertarErrorSemantico(&lista_errores_semanticos, "Error de doble declaracion\t\t", yylineno);
                                                } else{
                                                   insertarVariable(&listaIDS, $<mystruct.cadena>1, "-", yylineno); 
                                                }
                                             }
                        | ID '=' expAditiva  { if(chequeoDobleDeclaracion(&lista_Variables, $<mystruct.cadena>1) == 1){
                                                   insertarErrorSemantico(&lista_errores_semanticos, "Error de doble declaracion\t\t", yylineno);
                                                } else{
                                                   insertarVariable(&listaIDS, $<mystruct.cadena>1, "-", yylineno); 
                                                }
                                             }
;

listaParametros:        /* Caso particular en el cual no posee argumentos.*/
                        | parametro                         { insertarParametro(&parametros, $<mystruct.cadena>1); }       
                        | parametro ',' listaParametros     { insertarParametro(&parametros, $<mystruct.cadena>1); }    
;

parametro:              TIPO_DATO ID                        { cantidad_parametros++; $<mystruct.cadena>$= strdup($<mystruct.cadena>1);}             
;

lista_de_declaraciones: declaracion
                        | declaracion lista_de_declaraciones 
;

%%

int main(){
   yyin = fopen("ArchivoFuente.c","r");
   // Presentacion listado de errores sintacticos
   printf("\n********\t\tLISTADO ERRORES SINTACTICOS\t\t********\n\n");  
   yyparse();
   fclose(yyin);

   // INFORME
   mostrarErroresLexicos(&lista_errores_lexicos);
   mostrarErroresSemanticos(&lista_errores_semanticos);
   mostrarVariables(&lista_Variables);
   mostrarSentencias(&lista_sentencias);
   mostrarFunciones(&lista_Funciones);

   return 0;
}