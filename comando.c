#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tad.h"
#include "comando.h"




char actCmd[25]=""; //Esta variable almacena la cadena del comando actual para buscarlo luego en 'comandos'
char actParam[25]=""; //Esta variable almacena el nombre del parametro actual para buscarlo luego en 'obligados' o 'optativos' de su respectivo comando
int lastToken=-1; //Indice que indica el tipo del ultimo token capturado (funcion real desconocida por ahora)
int lastCmd=-1; //Indice que establece el comando que se va a ejectura mediante el metodo 'ejecutarComando(indice)


char *comandos[5]={"mkdisk", "rmdisk", "fdisk", "mount",
                    "umount"};


/***
typedef struct crearDisco {//COMANDO 0
    int _size;

    char  path [100];
    char name [100];
    char *obligados;
    int parametros;


} mkdisk;**/

mkdisk nuevo={0,"", "", {"tamanio", "path", "nombre"}, 3};

/**
    char path [100];
    char *obligados
    int parametros;*/


rmdisk borrar={"",{"path"},1};

/**
typedef struct particiones{ //COMANDO 2
    int tamanio;
    char unit; // 'B', 'K' , 'M'
    char path[100];
    char type; // 'P' , 'E', 'L'
    char fit;//'B' , 'F', 'W'
    char name[100];
    char del; //T es fast, U es full
    int add;
    char *obligados; //,{"tamanio","path","nombre", }
    char *opcionales;//= {"add", "del","type", "fit"}
    int parametros;  // si encontramos add o delete le restamos 1 a esta variable
     bool matched[3];
     bool rematched[4];

//La suma de primarias y extendidas debera ser 4 como maximo
}fdisk;*/

fdisk  particion=
{0, 'K', "",'P', 'W', "",'T',0,{"tamanio","path","nombre"}, {"add", "delete","tipo", "fit"}, 3};

/**
typedef struct montar{ //COMANDO 3
    char path[100];
    char name[100];
    char *obligados;
    int parametros;
}mount;*/

mount montar=
{ "","",{"path","name"},2};



umount desmontar=
{"", {"id"},};

bool otherLine=false;
bool fault= false;




void resetAnalizer(){
    fault=false;
    actCmd[0]='\0';
    actParam[0]= '\0';
    lastCmd=-1;
    lastToken= -1;
    resetOtherLine();


}


void resetOtherLine(){
    otherLine= false;

}


bool checkCommand(char cmd[]){

        

    resetAnalizer();


    /*****************************

    Variables del automata

    *******************************/
    int estado=0;
    char token[100]="";


    /**********Automata**********/

    int i=0;
    char actual='\0';


    for(i=0; cmd[i]!='\0' && i<strlen(cmd); i++ ){
        actual= cmd[i];
        switch(estado){
            case 0:
                switch(actual){
                    case '"':
                        estado=6;
                    case '-':
                        estado=2;
                    case '+':
                        estado=3;
                    case '>':
                        estado=4;
                    default:
                        if(actual>= '0' && actual <= '9'){
                            estado= 1;

                        }





                }
                break;


            case 1:
                estado=9;


        }
        return false;
    }

}

void ejecutarComando(int comando){
    if(fault)
        return;


    switch(comando){
        case 1:
            crearDisco();
            break;

        default:
            break;
    }
}

void crearDisco(){

    printf( "Comando :  %s", nuevo.obligados[2]);



}

void toLowerCase(char *cadena){

}

void append (char *cadena, char car){
        int len= strlen(cadena);
        cadena[len]=car;
        cadena[len+1]= '\0';


}






