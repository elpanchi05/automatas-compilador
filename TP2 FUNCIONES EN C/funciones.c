#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>       // Para mantisa y parte entera
#include <stdlib.h>     // Para strol

typedef struct NodoPalabrasRes{
    char *token;
    struct NodoPalabrasRes *sig;
}NodoPalabrasRes;

typedef struct nodo_identificadores {
    char *identificador;
    struct nodo_identificadores* sig;

}nodo_identificadores;

typedef struct nodoOperadores{
    char dato[5];
    int contador;
    struct nodoOperadores* siguiente;
}nodoOperadores;

typedef struct nodo_Id_litCadena {
    char *identificador;
    struct nodo_Id_litCadena* sig;
}nodo_Id_litCadena;

typedef struct NoReconocidos {
    char Cadena[100];
    int Linea;
    struct NoReconocidos *nxt;
}NoReconocidos;

typedef struct ConstanteOctal {
    int octal;
    struct ConstanteOctal *nxt;
}ConstanteOctal;

typedef struct ConstanteHexa {
    int hexa;
    struct ConstanteHexa *nxt;
}ConstanteHexa;

typedef struct ConstanteReal {
    double real;
    struct ConstanteReal *nxt;
}ConstanteReal;

typedef struct ConstanteDecimal {
    int decimal;
    struct ConstanteDecimal *nxt;
}ConstanteDecimal;

typedef struct ConstanteCaracter {
    char caracter;
    struct ConstanteCaracter *nxt;
}ConstanteCaracter;

typedef struct Comentarios{
    char *Coment;
    struct Comentarios *sig;
}Comentarios;

///////////////////////////////////// LITERALES CADENA ////////////////////////////////////////////////

nodo_Id_litCadena* insertar_unico(char* literalCadena, nodo_Id_litCadena* lista, int (criterio)(char*, char*)){
    nodo_Id_litCadena** aux = &lista;
	while (*aux != NULL && criterio(literalCadena, (*aux)->identificador) > 0)
		aux = &((*aux)->sig);
	if(*aux == NULL || criterio(literalCadena, (*aux)->identificador) < 0) {
		nodo_Id_litCadena* nuevo = (nodo_Id_litCadena*)calloc(sizeof(nodo_Id_litCadena),1); //Genero nodo
		nuevo->identificador = literalCadena; // y guardo el valor
		//Ahora lo inserto en su lugar
		nuevo->sig = *aux;
		*aux = nuevo;		
	}
    return lista;
}	

int criterioLiteralesCadena(char* L1, char* L2){
    if(strcmp(L1, L2) != 0)
    {
      if(strlen(L1) > strlen(L2))
        return 1;
      else
        return -1;
    }  
  return 0;
}

void mostrarLiterales(nodo_Id_litCadena* lista){
    while(lista != NULL){
    printf("literal: %s  longitud: %d\n", lista->identificador, strlen(lista->identificador));
    lista = lista ->sig;
    }
}

void escriboLiteralesCadena(nodo_Id_litCadena* lista){
    // Hago lo que pedía la consigna y lo meto en un txt

    FILE *archiv;
    archiv = fopen("Principal.txt", "a");
    fprintf(archiv, "\n LITERALES CADENA:\n");

    while(lista != NULL){
    fprintf(archiv, "literal: %s  longitud: %d\n", lista->identificador, strlen(lista->identificador));
    lista = lista ->sig;
    }
    fclose(archiv);        
}

///////////////////////////////////// IDENTIFICADORES ////////////////////////////////////////////////

nodo_identificadores* pop(nodo_identificadores* lista){
	if (lista == NULL) {
		printf("Error: pop en pila vacia\n");
		return NULL;		
	}
	nodo_identificadores* aux_elim = lista;
	lista = lista->sig;
	free(aux_elim);
	return lista;
}

int criterioIdentificadores(char* id1, char* id2){
  return strcmp (id1, id2);
}

nodo_identificadores* insertar(char* id, nodo_identificadores* lista, int (criterio)(char*, char*))
{
	nodo_identificadores* nuevo =calloc(sizeof(nodo_identificadores),1);
	nuevo->identificador = id;

	if (lista == NULL || criterio(nuevo->identificador, lista->identificador) < 0) {
		/* si no hay datos, o el quiero insertar es anterior
		   al que está en primer lugar */
		nuevo->sig = lista;
		lista = nuevo;
	} else {
		nodo_identificadores* p = lista;
		/* en tanto haya un siguiente y el que quiero insertar sea
		   posterior a ese siguiente: avanzo
		   NOTA: >= es para que ante un igual queden
		   en "orden cronologico" (podría dejar solo >) */
		while (p->sig != NULL && criterio(nuevo->identificador, p->sig->identificador) >= 0)
			p = p->sig;
		nuevo->sig = p->sig;
		p->sig = nuevo;
	}
  return lista;
}

void mostrar(nodo_identificadores* lista){
    FILE *archiv;
    archiv = fopen("Principal.txt", "a");   
   
   while(lista != NULL){
      int cantIds = 0;
      char* idAnterior = lista->identificador;
      while(lista != NULL && strcmp(idAnterior, lista->identificador) == 0){
        cantIds++;
        lista = lista ->sig;
      }
      fprintf(archiv, "Cantidad de %s encontrados: %d\n", idAnterior, cantIds);
   } 
   fclose(archiv);
}

nodo_identificadores* vaciar(nodo_identificadores* lista){
  while(lista != NULL){
    lista = pop(lista);
  }
  return lista;
}

///////////////////////////////////// CONSTANTES ////////////////////////////////////////////////

void insertarOctal(ConstanteOctal **listaOctal, char *octalchar){
    
    ConstanteOctal *nuevoOctal = malloc(sizeof(ConstanteOctal));

    nuevoOctal->octal = strtol(octalchar, NULL, 8);   // Toma una cadena de caracteres, 
                                                      // un puntero opcional para almacenar y la base de la constante
    
    nuevoOctal->nxt = *listaOctal;
    *listaOctal = nuevoOctal;

}

void insertarDecimal(ConstanteDecimal **listaDecimal, char *decichar){
    
    ConstanteDecimal *nuevoDecimal = malloc(sizeof(ConstanteDecimal));

    nuevoDecimal->decimal = atoi(decichar);
    
    nuevoDecimal->nxt = *listaDecimal;
    *listaDecimal = nuevoDecimal;

}

void insertarHexa(ConstanteHexa **listaHexa, char *hexachar){
    
    ConstanteHexa *nuevoHexa = malloc(sizeof(ConstanteHexa));

    nuevoHexa->hexa = strtol(hexachar, NULL, 16);
    
    nuevoHexa->nxt = *listaHexa;
    *listaHexa = nuevoHexa;

}

void insertarReal(ConstanteReal **listaReal, char *realchar){
    
    ConstanteReal *nuevoReal = malloc(sizeof(ConstanteReal));

    nuevoReal->real = atof(realchar);
    
    nuevoReal->nxt = *listaReal;
    *listaReal = nuevoReal;

}

void insertarCaracter (ConstanteCaracter **listaCaracter, char *cadenachar){

    ConstanteCaracter *nuevochar = malloc(sizeof(ConstanteCaracter));

    nuevochar->caracter = cadenachar[1]; // cadenachar es una cadena de caracter con la forma "'c'/0", por lo que la segunda
                                         // posición del vector guarda el caracter que buscamos


    // hay que insertar al final de la lista, para tener una lista por orden de aparición
    ConstanteCaracter *auxiliarC = *listaCaracter;

    while(auxiliarC && auxiliarC->nxt){
        auxiliarC = auxiliarC->nxt;
    }
    if(auxiliarC){
        nuevochar->nxt = NULL;
        auxiliarC->nxt = nuevochar;
    } else {
        nuevochar->nxt = NULL;
        *listaCaracter = nuevochar;
    }

}

void BorrarLaListaC(ConstanteCaracter **lista){
    ConstanteCaracter *anterior;
    ConstanteCaracter *auxiliar;

    while (lista){

        anterior = NULL;
        auxiliar = *lista;
        
        while (auxiliar && auxiliar->nxt){
            anterior = auxiliar;
            auxiliar = auxiliar->nxt;
        }

        if (auxiliar){
            free(auxiliar);
            if (anterior)
                anterior->nxt = NULL;
            else
                lista = NULL;
        }
    }
    
}
void BorrarLaListaH(ConstanteHexa **lista){
    ConstanteHexa *anterior;
    ConstanteHexa *auxiliar;

    while (lista){

        anterior = NULL;
        auxiliar = *lista;
        
        while (auxiliar && auxiliar->nxt){
            anterior = auxiliar;
            auxiliar = auxiliar->nxt;
        }

        if (auxiliar){
            free(auxiliar);
            if (anterior)
                anterior->nxt = NULL;
            else
                lista = NULL;
        }
    }
   
}
void BorrarLaListaD(ConstanteDecimal **lista){

    ConstanteDecimal *anterior;
    ConstanteDecimal *auxiliar;

    while (lista){

        anterior = NULL;
        auxiliar = *lista;
        
        while (auxiliar && auxiliar->nxt){
            anterior = auxiliar;
            auxiliar = auxiliar->nxt;
        }

        if (auxiliar){
            free(auxiliar);
            if (anterior)
                anterior->nxt = NULL;
            else
                lista = NULL;
        }
    }
   
}
void BorrarLaListaR(ConstanteReal **lista){
    ConstanteReal *anterior;
    ConstanteReal *auxiliar;

    while (lista){

        anterior = NULL;
        auxiliar = *lista;
        
        while (auxiliar && auxiliar->nxt){
            anterior = auxiliar;
            auxiliar = auxiliar->nxt;
        }

        if (auxiliar){
            free(auxiliar);
            if (anterior)
                anterior->nxt = NULL;
            else
                lista = NULL;
        }
    }
    
}
void BorrarLaListaO(ConstanteOctal **lista){
    ConstanteOctal *anterior;
    ConstanteOctal *auxiliar;

    while (lista){

        anterior = NULL;
        auxiliar = *lista;
        
        while (auxiliar && auxiliar->nxt){
            anterior = auxiliar;
            auxiliar = auxiliar->nxt;
        }

        if (auxiliar){
            free(auxiliar);
            if (anterior)
                anterior->nxt = NULL;
            else
                lista = NULL;
        }
    }
    
}

void escribirConstantes (ConstanteOctal *listaOctal, ConstanteHexa *listaHexa, ConstanteReal *listaReal, ConstanteDecimal *listaDecimal, ConstanteCaracter *listaChar){

    ConstanteDecimal *auxiliarD = listaDecimal;
    ConstanteHexa *auxiliarH = listaHexa;
    ConstanteOctal *auxiliarO = listaOctal;
    ConstanteReal *auxiliarR = listaReal;
    ConstanteCaracter *auxiliarC = listaChar;
    int contadorchar = 0;
    int sumaDecimales = 0;
    double parteDecimal, parteEntera;

    FILE *archiv;
    archiv = fopen("Principal.txt", "wt");

    fprintf(archiv, "CONSTANTES NUMÉRICAS:\n");
    
    fprintf(archiv, "\nConstantes octales:\n");
    while (auxiliarO){
        fprintf(archiv, " - Valor octal %o, es %d en decimal\n", auxiliarO->octal, auxiliarO->octal);
        auxiliarO = auxiliarO->nxt;
    }

    fprintf(archiv, "\nConstantes hexadecimales:\n");
    while (auxiliarH){
        fprintf(archiv, " - Valor hexadecimal %x, es %d en decimal\n", auxiliarH->hexa, auxiliarH->hexa);
        auxiliarH = auxiliarH->nxt;
    }

    fprintf(archiv, "\nConstantes decimales:\n");
    while (auxiliarD){
        fprintf(archiv, " - %d \n", auxiliarD->decimal);
        sumaDecimales = sumaDecimales + auxiliarD->decimal;
        auxiliarD = auxiliarD->nxt;
    }
    if((auxiliarD == NULL)&&(sumaDecimales != 0)){
        fprintf(archiv, "Suma de todos los valores decimales: %d\n", sumaDecimales);
    }
    
    fprintf(archiv, "\nConstantes reales:\n");
    while (auxiliarR){
        parteDecimal = modf(auxiliarR->real, &parteEntera);  // devuelve el valor de la parte decimal y pone la parte entera en el segundo argumento que le pasemos
        fprintf(archiv, " - Número real %f, parte entera %f y mantisa %f\n", auxiliarR->real, parteEntera, parteDecimal);
        auxiliarR = auxiliarR->nxt;
    }

    fprintf(archiv, "\nCONSTANTES CARACTER POR ORDEN DE APARICIÓN:\n");
    while (auxiliarC){
        contadorchar += 1;
        fprintf(archiv, "%d) %c \n", contadorchar, auxiliarC->caracter);
        auxiliarC = auxiliarC->nxt;
    }
    
    fclose(archiv);
    
    

}


//////////////////////////////////// NO RECONOCIDOS /////////////////////////////////////////////

void insertarNoReconocidos(NoReconocidos  **nodoAnterior, char cadenaErronea[], int lineaError){  

    // Toma lista ya establecida y agrega un nodo con la nueva cadena no reconocida

    NoReconocidos *nuevaCadena = malloc (sizeof(NoReconocidos)); 
    
    strcpy(nuevaCadena->Cadena , cadenaErronea);    // le asigno la cadena errónea al nuevo nodo
    nuevaCadena->Linea = lineaError;                // le asigno la linea donde se encontró el error

    nuevaCadena->nxt = *nodoAnterior;
    *nodoAnterior = nuevaCadena;

    

}

void BorrarLaLista(NoReconocidos **lista){
    NoReconocidos *anterior;
    NoReconocidos *auxiliar;

    while (lista){

        anterior = NULL;
        auxiliar = *lista;
        
        while (auxiliar && auxiliar->nxt){
            anterior = auxiliar;
            auxiliar = auxiliar->nxt;
        }

        if (auxiliar){
            free(auxiliar);
            if (anterior)
                anterior->nxt = NULL;
            else
                lista = NULL;
        }
    }
    
}

void escriboArchivoNoReconocidos(NoReconocidos *Error){
    // Hago lo que pedía la consigna y lo meto en un txt

    FILE *archiv;
    archiv = fopen("Principal.txt", "a");
    fprintf(archiv ,"\nNO RECONOCIDOS:\n");
    while(Error){
        fprintf(archiv, "Cadena no reconocida: %s \n", Error->Cadena);
        fprintf(archiv, "Linea donde se encuentra: %d \n", Error->Linea);
        fprintf(archiv, "\n");
        Error = Error->nxt;
    }
    fclose(archiv);
    

}

//////////////////////////////////// COMENTARIOS /////////////////////////////////////////////

void InsertarComent(Comentarios **Lista, char *string){
         
    Comentarios *nuevo_nodo, *tmp;
    nuevo_nodo = (Comentarios *) malloc(sizeof(Comentarios)); 
    nuevo_nodo->Coment = string;
    nuevo_nodo->sig = NULL;
    
        if(*Lista == NULL){
            *Lista = nuevo_nodo;
        }else{
            tmp = *Lista;
            while (tmp->sig != NULL){
                tmp = tmp->sig;
            }
            tmp->sig = nuevo_nodo;
        }
}

void escribirComentarios(Comentarios *Lista){
    FILE *a = fopen("Principal.txt","a");
    fprintf(a ,"\nCOMENTARIOS:\n");
    while(Lista){
        fprintf(a,"El comentario : %s\n",Lista->Coment);
        Lista = Lista->sig;
    }
    fclose(a);    
}

void BorrarComentarios(Comentarios **lista){
    Comentarios *anterior;
    Comentarios *auxiliar;

    while (lista){

        anterior = NULL;
        auxiliar = *lista;
        
        while (auxiliar && auxiliar->sig){
            anterior = auxiliar;
            auxiliar = auxiliar->sig;
        }

        if (auxiliar){
            free(auxiliar);
            if (anterior)
                anterior->sig = NULL;
            else
                lista = NULL;
        }
    }    
}

/////////////////////////////////// OPERADORES Y PUNTUACION //////////////////////////////////

void InsertarListaOp (nodoOperadores **lista, char* token) {
    nodoOperadores *aux = *lista;
    
    while( aux != NULL ){
        if(strcmp(token, aux -> dato) == 0){    //dato y token son iguales
            aux->contador+=1;

            return;                 //matcheo el token,  sale d la funcion
        }
        aux = aux->siguiente;
    }
    // el token no esta ene la lista, inicializco el contador
    nodoOperadores * nuevoNodo;
    nuevoNodo = (nodoOperadores*)malloc(sizeof(nodoOperadores));
    strcpy(nuevoNodo -> dato, token);
    nuevoNodo -> contador = 1;
    nuevoNodo -> siguiente = *lista;

    *lista=nuevoNodo;
}

void escriboArchivoOP(nodoOperadores *nodo){
    
    FILE *archiv;
    archiv = fopen("Principal.txt", "a");
    fprintf(archiv, "\nOPERADORES Y SIGNOS DE PUNTUACION:\n");

    while(nodo){
        fprintf(archiv, "Operador:%s ", nodo -> dato);
        fprintf(archiv, "Cantidad de veces que aparece:%d \n", nodo -> contador);
        
        nodo = nodo->siguiente;
    }
    fclose(archiv);    

}

////////////////////////////////// PALABRAS RESERVADAS ////////////////////////////////////////

void InsertarPalabrasReservadas(NodoPalabrasRes **Lista, char *string){
         
    NodoPalabrasRes *nuevo_nodo, *tmp;
    nuevo_nodo = (NodoPalabrasRes *) malloc(sizeof(NodoPalabrasRes)); 
    nuevo_nodo->token = string;
    nuevo_nodo->sig = NULL;
    
        if(*Lista == NULL){
            *Lista = nuevo_nodo;
        }else{
            tmp = *Lista;
            while (tmp->sig != NULL){
                tmp = tmp->sig;
            }
            tmp->sig = nuevo_nodo;
        }
}

void escribirPR(NodoPalabrasRes *Lista){
    
    FILE *archivo;
    archivo = fopen("Principal.txt", "a");
    fprintf(archivo, "\nPALABRAS RESERVADAS:\n");
    while(Lista){
        fprintf(archivo, "Palabra reservada: %s", Lista->token);
        Lista = Lista->sig;
    }
    
    fclose(archivo);
    
   
    
}

///////////////////////////////////////////////////////////////////////////////////////////////
/*********************************************************************************************/
///////////////////////////////////////////////////////////////////////////////////////////////

int main(){

    nodo_identificadores* lista_Deidentificadores = NULL; 
    nodo_Id_litCadena *listaId = NULL;
    nodo_Id_litCadena *listaLitCad = NULL;
    NoReconocidos *listaNoReconocidos = NULL;
    ConstanteCaracter *listaCaracter = NULL;
    ConstanteDecimal *listaDecimal = NULL;
    ConstanteHexa *listaHexa = NULL;
    ConstanteOctal *listaOctal = NULL;
    ConstanteReal *listaReal = NULL;
    Comentarios *listaComent = NULL;
    nodoOperadores *listaOp = NULL;
    NodoPalabrasRes *Lista = NULL;

    listaLitCad = insertar_unico("Hola que tal", listaLitCad, criterioLiteralesCadena);
    listaLitCad = insertar_unico("Buenas tardes", listaLitCad, criterioLiteralesCadena);
    listaLitCad = insertar_unico("Hola que tal", listaLitCad, criterioLiteralesCadena);
    listaLitCad = insertar_unico("Chau", listaLitCad, criterioLiteralesCadena);

    InsertarComent(&listaComent, "// Comentario de una linea");
    InsertarComent(&listaComent, "// Otro coment");
    InsertarComent(&listaComent, "// ");
    InsertarComent(&listaComent, "/* Comentario de varias lineas \n hola \n hola*/");
    InsertarComent(&listaComent, "/*\n buenas \n*/");
    
    InsertarPalabrasReservadas(&Lista,"main\n");
    InsertarPalabrasReservadas(&Lista,"int\n");
    InsertarPalabrasReservadas(&Lista,"float\n");
    InsertarPalabrasReservadas(&Lista,"double\n");
    InsertarPalabrasReservadas(&Lista,"double\n");

    insertarNoReconocidos(&listaNoReconocidos, "buenas tardess" , 123);
    insertarNoReconocidos(&listaNoReconocidos, "[c]='" , 83);
    insertarNoReconocidos(&listaNoReconocidos, "--//" , 90);
    insertarNoReconocidos(&listaNoReconocidos, "344##44" , 125);

    InsertarListaOp(&listaOp,"*");
    InsertarListaOp(&listaOp,"*");
    InsertarListaOp(&listaOp,"/");

    insertarDecimal(&listaDecimal, "65");
    insertarHexa(&listaHexa, "0xaa3");
    insertarReal(&listaReal, "23.056");
    insertarReal(&listaReal, "34.98");
    insertarDecimal(&listaDecimal, "566");
    insertarOctal(&listaOctal, "017");
    insertarDecimal(&listaDecimal, "789");
    insertarReal(&listaReal, ".073");
    insertarHexa(&listaHexa, "0x53b");
    insertarOctal(&listaOctal, "0");
    insertarOctal(&listaOctal, "065");
    insertarDecimal(&listaDecimal, "15");
    insertarReal(&listaReal, "42.0");
    insertarCaracter(&listaCaracter, "'H'");
    insertarCaracter(&listaCaracter, "'O'");
    insertarCaracter(&listaCaracter, "'l'");
    insertarCaracter(&listaCaracter, "'a'");

    lista_Deidentificadores = insertar("hola", lista_Deidentificadores, criterioIdentificadores);
    lista_Deidentificadores = insertar("buenDia", lista_Deidentificadores, criterioIdentificadores);
    lista_Deidentificadores = insertar("chau", lista_Deidentificadores, criterioIdentificadores);
    lista_Deidentificadores = insertar("buenDia", lista_Deidentificadores, criterioIdentificadores);

    
    escribirConstantes(listaOctal,listaHexa,listaReal,listaDecimal,listaCaracter); 
    escriboLiteralesCadena(listaLitCad);   
    escribirPR(Lista);
    escriboArchivoOP(listaOp);
    escribirComentarios(listaComent);
    escriboArchivoNoReconocidos(listaNoReconocidos);
    mostrar(lista_Deidentificadores);

    lista_Deidentificadores = vaciar(lista_Deidentificadores);

    return 0;
}
