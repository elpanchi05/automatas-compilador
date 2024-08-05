#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// DECLARACION DE STRUCTS

typedef struct nodoErrorLexico{
    char* error;
    int linea;
    struct nodoErrorLexico* siguiente;
}nodoErrorLexico;

typedef struct nodoErrorSemantico{
    char* descripcionError;
    int linea;
    struct nodoErrorSemantico* siguiente;
}nodoErrorSemantico;

typedef struct nodoVariable{
    char *nombre, *tipo, *valor_Cadena;
    int linea;
    struct nodoVariable* siguiente;
}nodoVariable;

typedef struct nodoSentencia {
    char *tipoSentencia, *descripcionSentencia;
    int linea;
    struct nodoSentencia* siguiente;
}nodoSentencia;

typedef struct nodoFuncion{
    char* ID, *tipo;
    int linea, cantidad_parametros;
    struct nodoParametro* parametros;
    struct nodoFuncion* siguiente;
}nodoFuncion;

typedef struct nodoParametro{
    char* tipo;
    struct nodoParametro* siguiente;    
}nodoParametro;

// DECLARACIONES DE FUNCIONES 

void insertarErrorLexico(nodoErrorLexico** ,char * ,int);
void mostrarErroresLexicos(nodoErrorLexico**);

void insertarErrorSemantico(nodoErrorSemantico** , char*, int);
void mostrarErroresSemanticos(nodoErrorSemantico** );

void insertarVariable(nodoVariable** , char* , char* , int);
void mostrarVariables(nodoVariable** );

void insertarSentencia(nodoSentencia** , char*, char*, int);
void mostrarSentencias(nodoSentencia**);

void insertarFuncion(nodoFuncion**, char*, char*, int, nodoParametro*, int);
void mostrarFunciones(nodoFuncion** );

void insertarParametro(nodoParametro**, char*);
void mostrarParametros(nodoParametro** );

void rutinaInvocacion(nodoFuncion** , nodoParametro** ,nodoErrorSemantico** , char*, int, int);
int chequeoDobleDeclaracion(nodoVariable** , char*);
int controlDeTiposNum(int , int);
char* obtenerTipoVariable(nodoVariable** , char*);
int controlDeTiposVar(char* , char*);