#include "funciones.h"

void insertarErrorLexico(nodoErrorLexico** lista ,char* error, int nro_linea){
    nodoErrorLexico* nuevo= (nodoErrorLexico*) malloc(sizeof(nodoErrorLexico));
    nodoErrorLexico* aux = *lista;
    nuevo->error = strdup(error);
    nuevo->linea = nro_linea;
    nuevo->siguiente = NULL;
    
    if(*lista==NULL){
        nuevo->siguiente = *lista;
        *lista = nuevo;
    }
    else{
    while(aux->siguiente!=NULL){
        aux = aux->siguiente;
    }
    aux->siguiente = nuevo;
    }
}
void mostrarErroresLexicos(nodoErrorLexico** lista){
    nodoErrorLexico* aux = *lista;
    // Caso particular.
    if(aux == NULL){printf("\n********\t\tNO SE ENCONTRARON ERRORES LEXICOS\t\t********\n\n"); return;}

    // Impresion en consola de listado.
    printf("\n********\t\tLISTADO ERRORES LEXICOS\t\t********\n\n");
    while(aux!=NULL){
        printf("Error: \"%s\" \t linea: %d\n", aux->error, aux->linea);
        aux = aux->siguiente;
    }
}

void insertarVariable(nodoVariable** lista, char* nombre, char* tipo, int nro_linea){
    nodoVariable* nuevo= (nodoVariable*) malloc(sizeof(nodoVariable));
    nodoVariable* aux = *lista;

    nuevo->nombre = strdup(nombre);
    nuevo->tipo = strdup(tipo);
    nuevo->linea = nro_linea;
    nuevo->siguiente = NULL;    


    if(*lista==NULL){
        nuevo->siguiente = *lista;
        *lista = nuevo;
    }
    else{
    while(aux->siguiente!=NULL){
        aux = aux->siguiente;
    }
    aux->siguiente = nuevo;
    }    
}
void mostrarVariables(nodoVariable** lista){
    nodoVariable* aux = *lista;
    printf("\n********\t\tLISTADO VARIABLES\t\t********\n\n");

    while(aux!=NULL){
        printf("Identificador: \"%s\"\tTipo: \"%s\"\tLinea: %d\n", aux->nombre, aux->tipo, aux->linea);
        aux = aux->siguiente;
    }
}

void insertarSentencia(nodoSentencia** lista, char* tipo, char* descripcion, int nro_linea){
    nodoSentencia* actual = *lista;
    nodoSentencia* nuevo = (nodoSentencia*) malloc (sizeof(nodoSentencia));
    nuevo->tipoSentencia = strdup(tipo);
    nuevo->descripcionSentencia = strdup(descripcion);
    nuevo->linea= nro_linea;

    if(*lista==NULL){
        nuevo->siguiente = *lista;
        *lista = nuevo;
    }
    else{
        while(actual->siguiente!=NULL){
                actual=actual->siguiente;
            }
        nuevo->siguiente = actual->siguiente;
        actual->siguiente = nuevo;
    }
}
void mostrarSentencias(nodoSentencia** lista){
    nodoSentencia* aux= *lista;
    printf("\n********\t\tLISTADO SENTENCIAS\t\t********\n\n");

    while(aux!=NULL){
        printf("Tipo de sentencia: %s\t - Descripcion: %s\t - Linea: %d \n", aux->tipoSentencia, aux->descripcionSentencia, aux->linea);
        aux=aux->siguiente;
    }
}

void insertarFuncion(nodoFuncion** lista, char* nombre, char* tipo, int nro_linea){
    nodoFuncion* actual = *lista;
    nodoFuncion* nuevo = (nodoFuncion*) malloc (sizeof(nodoFuncion));
    nuevo->tipo = strdup(tipo);
    nuevo->ID = strdup(nombre);
    nuevo->linea= nro_linea;

    if(*lista==NULL){
        nuevo->siguiente = *lista;
        *lista = nuevo;
    }
    else{
        while(actual->siguiente!=NULL){
                actual=actual->siguiente;
            }
        nuevo->siguiente = actual->siguiente;
        actual->siguiente = nuevo;
    }
}
void mostrarFunciones(nodoFuncion** lista){
    nodoFuncion* aux= *lista;
    printf("\n********\t\tLISTADO FUNCIONES\t\t********\n\n");

    while(aux!=NULL){
        printf("ID: %s\t - Tipo que Retorna: %s\t - Linea: %d \n", aux->ID, aux->tipo, aux->linea);
        aux=aux->siguiente;
    }
}