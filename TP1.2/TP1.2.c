#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

enum {
    INICIO = 0,                     //q0
    CONSTANTE_OCTAL1,               //q1
    CONSTANTE_DECIMAL,              //q2
    CONSTANTE_HEXADECIMAL1,         //q3
    CONSTANTE_HEXADECIMAL2,         //q4
    CONSTANTE_OCTAL2,               //q5
    DESCONOCIDO                     //q6
};

//--------------------------- Matriz de Estados ---------------------------//

int matrizEstados[7][6] = { 
    {CONSTANTE_OCTAL1, CONSTANTE_DECIMAL, CONSTANTE_DECIMAL, DESCONOCIDO, DESCONOCIDO, DESCONOCIDO},
    {CONSTANTE_OCTAL2, CONSTANTE_OCTAL2, DESCONOCIDO, DESCONOCIDO, CONSTANTE_HEXADECIMAL1, DESCONOCIDO},
    {CONSTANTE_DECIMAL, CONSTANTE_DECIMAL, CONSTANTE_DECIMAL, DESCONOCIDO, DESCONOCIDO, DESCONOCIDO},
    {CONSTANTE_HEXADECIMAL2, CONSTANTE_HEXADECIMAL2, CONSTANTE_HEXADECIMAL2, CONSTANTE_HEXADECIMAL2, DESCONOCIDO, DESCONOCIDO},
    {CONSTANTE_HEXADECIMAL2, CONSTANTE_HEXADECIMAL2, CONSTANTE_HEXADECIMAL2, CONSTANTE_HEXADECIMAL2, DESCONOCIDO, DESCONOCIDO},
    {CONSTANTE_OCTAL2, CONSTANTE_OCTAL2, DESCONOCIDO, DESCONOCIDO, DESCONOCIDO, DESCONOCIDO},
    {DESCONOCIDO, DESCONOCIDO, DESCONOCIDO, DESCONOCIDO, DESCONOCIDO, DESCONOCIDO}
};

//-----------------------------------------------------------------------//

int transiciones(char , int );
void mostrarEstado(int , FILE* );    

int main (){
    FILE* texto_entrada= fopen("entrada.txt", "r");
    FILE* texto_salida= fopen("salida.txt", "w"); 
    int Estado = INICIO;                                             // Siempre inicializa en Inicial.
    if((texto_entrada = fopen("entrada.txt","r")) == NULL){          // ¿El archivo esta vacio?
        printf("Error en la apertura del archivo.");
    }

    //          LOGICA DE LECTURA

    char a = getc(texto_entrada);

    while(!feof(texto_entrada)){
        if(ispunct(a) == 0 && a != '\0'){           // verifica que no sea un signo de puntuación
            Estado = transiciones(a , Estado);      // envio a comprobar la palabra
            fprintf(texto_salida, "%c", a);
        }
        else{
            mostrarEstado(Estado, texto_salida);    // Muestra el resultado de la palabra leída
            Estado = INICIO;                        // y vuelve a inicializar Estado como Inicio para la siguiente palabra
        }
        a = getc(texto_entrada);
    }
    mostrarEstado(Estado, texto_salida);

    fclose (texto_entrada);                                                             // Libero espacio de memoria 
    fclose (texto_salida);
    return 0;
}

int transiciones(char caracter, int Estado){

    if(caracter == '0')                     return matrizEstados[Estado][0];
    
    if(caracter >= '1' && caracter <= '7')  return matrizEstados[Estado][1];
    
    if(caracter == '8' || caracter == '9')  return matrizEstados[Estado][2];
    
    if(isxdigit(caracter))                  return matrizEstados[Estado][3];   // isxdigit comprueba que sea un caracter Hexadecimal válido

    if(caracter == 'x' || caracter == 'X')  return matrizEstados[Estado][4];

    /*En caso de Rechazo*/                  return matrizEstados[Estado][5];
    }


void mostrarEstado(int estado, FILE* texto_salida){

    switch (estado)      // Con los estados finales posibles
    {
    case CONSTANTE_OCTAL1:
        fprintf(texto_salida, "\t%20s\n","OCTAL");  
        // octal 
        break;
    case CONSTANTE_DECIMAL:
        fprintf(texto_salida, "\t%20s\n","DECIMAL");    
        // decimal
        break;
    case CONSTANTE_HEXADECIMAL2:
        fprintf(texto_salida,"\t%20s\n","HEXADECIMAL");    
        // hexa
        break;

    case CONSTANTE_OCTAL2:
        fprintf(texto_salida, "\t%20s\n", "OCTAL");    
        // octal
        break;
    case CONSTANTE_HEXADECIMAL1:
    case INICIO:
    case DESCONOCIDO:
        fprintf(texto_salida, "\t%20s\n", "DESCONOCIDO");    
        // rechazo
        break;
    }
}
