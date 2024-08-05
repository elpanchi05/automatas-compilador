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
        printf("Error: %s \t linea: %d\n", aux->error, aux->linea);
        aux = aux->siguiente;
    }
}

void insertarErrorSemantico(nodoErrorSemantico** lista, char* error, int nro_linea){
    nodoErrorSemantico* nuevo= (nodoErrorSemantico*) malloc(sizeof(nodoErrorSemantico));
    nodoErrorSemantico* aux = *lista;
    nuevo->descripcionError = strdup(error);
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
void mostrarErroresSemanticos(nodoErrorSemantico** lista){
    nodoErrorSemantico* aux = *lista;
    // Caso particular.
    if(aux == NULL){printf("\n********\t\tNO SE ENCONTRARON ERRORES SEMANTICOS\t\t********\n\n"); return;}

    // Impresion en consola de listado.
    printf("\n********\t\tLISTADO ERRORES SEMANTICOS\t\t********\n\n");
    while(aux!=NULL){
        printf("%s \t linea: %d\n", aux->descripcionError, aux->linea);
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
    // Caso particular.     
    if(aux == NULL){printf("\n********\t\tNO SE ENCONTRARON VARIABLES\t\t********\n\n"); return;}
    
    // Impresion en consola de listado.
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
    // Caso particular.
    if(aux == NULL){printf("\n********\t\tNO SE ENCONTRARON SENTENCIAS \t\t********\n\n"); return;}

    // Impresion en consola de listado.
    printf("\n********\t\tLISTADO SENTENCIAS\t\t********\n\n");

    while(aux!=NULL){
        printf("Tipo de sentencia: %s\t - Descripcion: %s\t - Linea: %d \n", aux->tipoSentencia, aux->descripcionSentencia, aux->linea);
        aux=aux->siguiente;
    }
}

void insertarFuncion(nodoFuncion** lista, char* nombre, char* tipo, int cantidad_parametros, nodoParametro* lista_parametros, int nro_linea){
    nodoFuncion* actual = *lista;
    nodoFuncion* nuevo = (nodoFuncion*) malloc (sizeof(nodoFuncion));
    nuevo->tipo = strdup(tipo);
    nuevo->ID = strdup(nombre);
    nuevo->cantidad_parametros = cantidad_parametros;
    nuevo->parametros = lista_parametros;
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
    // Caso particular.     
    if(aux == NULL){printf("\n********\t\tNO SE ENCONTRARON FUNCIONES\t\t********\n\n"); return;}
    
    // Impresion en consola de listado.
     printf("\n********\t\tLISTADO FUNCIONES\t\t********\n\n");

    while(aux!=NULL){
        printf("ID: %s\t - Tipo que Retorna: %s\t - Cantidad de Parametros: %d\t - Linea: %d\t - Tipo de Parametros: ", aux->ID, aux->tipo, aux->cantidad_parametros, aux->linea);
        mostrarParametros(&aux->parametros);
        printf("\n");
        aux=aux->siguiente;
    }
}

void insertarParametro(nodoParametro** lista, char* parametro){
    nodoParametro* actual = *lista;
    nodoParametro* nuevo = (nodoParametro*) malloc (sizeof(nodoParametro));
    nuevo->tipo = strdup(parametro);

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
void mostrarParametros(nodoParametro** lista){
    nodoParametro* aux= *lista;
    printf("%s", aux->tipo);
    aux=aux->siguiente;
    while(aux!=NULL){
        printf(", %s", aux->tipo);
        aux=aux->siguiente;
    }

}    

// RUTINAS SEMANTICAS

void rutinaInvocacion(nodoFuncion** lista, nodoParametro** invocacion, nodoErrorSemantico** errores, char* nombre, int cant_parametros, int linea){
    nodoFuncion* aux = *lista;

    // ¿ID de la funcion esta en TS?
    while(aux!=NULL && strcmp(nombre, aux->ID)!=0) aux = aux->siguiente;
    if(aux == NULL){
        insertarErrorSemantico(errores, "La funcion no esta declarada.\t\t", linea);
        return ;
    } 

    // Si está, ¿Posee la misma cantidad de parametros?
    if(aux->cantidad_parametros != cant_parametros) {
        insertarErrorSemantico(errores, "No posee la misma cantidad de parametros.", linea);
        return ;
    }

    //TODO: checkear que las listas sean identicas en lo que a tipo de dato se refiere.
    nodoParametro* aux_list= aux->parametros;           //lista de parametros de la lista.
    nodoParametro* aux_inv = *invocacion;               //lista de parametros de invocacion.

    while (strcmp(aux_list->tipo, aux_inv->tipo) == 0){
        aux_list = aux_list->siguiente;
        aux_inv = aux_inv->siguiente;
        if(aux_inv==NULL) return;   // En caso de que se termine la lista. 
                                    // Esto se daria unicamente si las listas posees los mismos datos.
    }

    if(aux_inv != NULL && strcmp(aux_list->tipo, aux_inv->tipo) != 0) {
        insertarErrorSemantico(errores, "Error de tipos de parametros.\t\t", linea);
        return ;
    }
}

int chequeoDobleDeclaracion(nodoVariable** lista, char* identificador){
    nodoVariable* aux = *lista;

    while(aux != NULL && (strcmp(identificador, aux->nombre)!=0)){
        aux = aux->siguiente;
    }
    if(aux){
        return 1;       // Ya existe la variable
    } else {
        return 0;       // No existe la variable
    }
}

int controlDeTiposNum(int tipo1, int tipo2){
    if(tipo1 == tipo2){
        return 0;       // No hay error de tipos
    }else{
        return 1;       // Hay error de tipos
    }
}

char* obtenerTipoVariable(nodoVariable** lista, char* identificador){
    nodoVariable* aux = *lista;
    while(aux != NULL && (strcmp(identificador, aux->nombre)!=0)){
        aux = aux->siguiente;
    }
    if(aux){
        return aux->tipo;
    } else {
        return "";       // No existe la variable
    }
}

int controlDeTiposVar(char* tipo1, char* tipo2){
    if(strcmp(tipo1,tipo2)==0){
        return 0;       // No hay error de tipos
    }else{
        return 1;       // Hay error de tipos
    }
}
