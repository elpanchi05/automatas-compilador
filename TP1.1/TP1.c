#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

enum ESTADOS{                                                                           // Asignar nombres a los estados del autómata
    INICIO = 0,
    CONSTANTE_OCTAL1,
    CONSTANTE_OCTAL2,
    CONSTANTE_HEXADECIMAL1,
    CONSTANTE_HEXADECIMAL2,
    CONSTANTE_DECIMAL,
    DESCONOCIDO                                                                         // DESCONOCIDO actúa como estado de rechazo
};

int cantidadElementos(FILE * );
void lectura_archivo(FILE* arch, int , char []);
void reconocer(char* valor, FILE* archSalida);
void separarPorComasYReconocer (char [], FILE* salida);

int main(){
    FILE *texto_entrada = fopen("entrada.txt","r");
    FILE *texto_salida = fopen ("salida.txt", "w");    
    int cantidad_elementos = 0;

    if((texto_entrada = fopen("entrada.txt","r")) == NULL){                             // ¿El archivo esta vacio?
        printf("Error en la apertura del archivo.");
    }

    cantidad_elementos = cantidadElementos(texto_entrada);

    char* vector_palabras = (char*) calloc(cantidad_elementos + 1, sizeof(char));       // Memoria pedida para la ejecucion del programa.

    lectura_archivo(texto_entrada, cantidad_elementos, vector_palabras);                // PASO LOS DATOS DEL TEXTO A UN ARRAY DE CHAR

    separarPorComasYReconocer(vector_palabras, texto_salida);                           // PASO EL ARRAY CON LAS PALABRAS A RECONOCER
    free(vector_palabras);
    fclose (texto_entrada);                                                             // Libero espacio de memoria 
    fclose (texto_salida);
    return 0;
}

// DEVUELVE CANTIDAD DE ELEMENTOS DE MI ARCHIVO
int cantidadElementos(FILE * arch){                                                     
    fseek(arch, 0, SEEK_END);
    int tamano = ftell(arch);
    fseek(arch, 0, SEEK_SET);

    return tamano/sizeof(char); 
}

//LEE ARCHIVO Y GUARDA SU CONTENIDO EN UN VECTOR DE CHAR.
void lectura_archivo(FILE* arch, int cantidad_elementos, char* vector){             
    fread(vector, sizeof(char), cantidad_elementos, arch);                             //LECTURA DEL ARCHIVO, GUARDO ELEMENTOS DE ENTRADA EN EL VECTOR.
}

//SEPARA CADA ELEMENTO POR COMA, EVALUA CON EL AUTOMATA Y LO GUARDA JUNTO A SU TIPO EN EL ARCH SALIDA.
void separarPorComasYReconocer (char vector[], FILE* salida){ 
    char* str = NULL;
    const char* sentinela = ",";
    str = strtok(vector, sentinela);                           // strtok separa el contenido de un vector en palabras 
    while (str != NULL){                                       // usando el caracter ',' como sentinela. Cada vez que encuentra
        reconocer(str, salida);                                // una ',' envía a reconocer la cadena que estaba detrás de ese caracter
        str = strtok(NULL, sentinela);
    }
} 

//EVALUA ELEMENTO EN EL AUTOMATA Y LO GUARDA EN EL ARCHIVO SALIDA.
void reconocer(char* valor, FILE* archSalida){
    int estado = INICIO, i = 0;
    while(1){
        switch(estado){
            case INICIO:
                if(valor[i] == '0')                                                     // ¿El primer caracter es un 0?
                    estado = CONSTANTE_OCTAL1;                                          
                else if(isdigit(valor[i]))                                              // isdigit evalua si es un caracter numerico.
                    estado = CONSTANTE_DECIMAL;               
                else
                    estado = DESCONOCIDO;                                               // Si es un primer caracter no numerico es no reconocido.
                i++;                    
                break;
            
            case CONSTANTE_OCTAL1:
                if(valor[i] == '\0'){                                                   // ¿FIN (caracter vacio)? 
                    fprintf(archSalida, "%-20s\tOCTAL\n", valor);
                    return;
                }
                else if(valor[i] == 'x' || valor[i] == 'X')                             // ¿LE SIGUE UNA X? ES HEXADECIMAL
                    estado = CONSTANTE_HEXADECIMAL1;
                else if(isdigit(valor[i]) && valor[i] - '0' < 8)                        // ¿EL CHAR NUMERAL ES MENOR QUE 8?
                    estado = CONSTANTE_OCTAL2;
                else
                    estado = DESCONOCIDO;
                i++;
                break;
            
            case CONSTANTE_OCTAL2:
                if(valor[i] == '\0'){                                                  // ¿FIN? 
                    fprintf(archSalida, "%-20s\tOCTAL\n", valor);
                    return;
                }
                else if(isdigit(valor[i]) && valor[i] - '0' < 8)
                    estado = CONSTANTE_OCTAL2;
                else
                    estado = DESCONOCIDO;
                i++;
                break;

            case CONSTANTE_HEXADECIMAL1:
                if(isxdigit(valor[i]))
                    estado = CONSTANTE_HEXADECIMAL2;
                else
                    estado = DESCONOCIDO;
                i++;
                break;
            
            case CONSTANTE_HEXADECIMAL2:
                if(valor[i] == '\0'){
                    fprintf(archSalida, "%-20s\tHEXADECIMAL\n", valor);               // ¿FIN? 
                    return;
                }
                else if(isxdigit(valor[i]))
                    estado = CONSTANTE_HEXADECIMAL2;
                else
                    estado = DESCONOCIDO;
                i++;
                break;

            case CONSTANTE_DECIMAL:
                if(valor[i] == '\0'){
                    fprintf(archSalida, "%-20s\tDECIMAL\n", valor);                 // ¿FIN? 
                    return;
                }
                else if(isdigit(valor[i]))
                    estado = CONSTANTE_DECIMAL;
                else
                    estado = DESCONOCIDO;
                i++;
                break;

            case DESCONOCIDO:                                                       // La cadena no es reconocida por el automata.
                fprintf(archSalida, "%-20s\tNO RECONOCIDA\n", valor);              
                return;
        }
    }
}