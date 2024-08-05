#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// DECLARACION DE STRUCTS

typedef struct nodoErrorLexico{
    char* error;
    int linea;
    struct nodoErrorLexico* siguiente;
}nodoErrorLexico;

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
    int linea;
    struct nodoFuncion* siguiente;
}nodoFuncion;

// DECLARACIONES DE FUNCIONES 

void insertarErrorLexico(nodoErrorLexico** ,char * ,int);
void mostrarErroresLexicos(nodoErrorLexico**);

void insertarVariable(nodoVariable** , char* , char* , int);
void mostrarVariables(nodoVariable** );

void insertarSentencia(nodoSentencia** , char*, char*, int);
void mostrarSentencias(nodoSentencia**);

void insertarFuncion(nodoFuncion**, char*, char*, int);
void mostrarFunciones(nodoFuncion** );
