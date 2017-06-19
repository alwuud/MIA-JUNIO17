#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tad.h"
#include "comando.h"
#define COMANDOS 5



char actCmd[25]=""; //Esta variable almacena la cadena del comando actual para buscarlo luego en 'comandos'
char actParam[25]=""; //Esta variable almacena el nombre del parametro actual para buscarlo luego en 'obligados' o 'optativos' de su respectivo comando
int lastToken=-1; //Indice que indica el tipo del ultimo token capturado (funcion real desconocida por ahora)
int lastCmd=-1; //Indice que establece el comando que se va a ejectura mediante el metodo 'ejecutarComando(indice)

/*lastCmd debe tener el valor de la posicion del comando actual en *comandos[5]*/

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

mkdisk nuevo={0,"", "", {"size", "path", "name"}, 3};

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
{0, 'K', "",'P', 'W', "",'T',0,{"size","path","name"}, {"unit", "type", "fit", "delete" , "add"}, 3};

/**
typedef struct montar{ //COMANDO 3
    char path[100];
    char name[100];
    char *obligados;
    int parametros;
}mount;*/

mount montar=
{ "","",{"path","name"},2};



umount desmontar= {"", {"id"}, 1};

bool otherLine=false;
bool fault= false;




void resetAnalizer(){
    fault=false;
    actCmd[0]='\0';
    actParam[0]= '\0';
    lastCmd=-1;
    lastToken= -1;
   
    otherLine=false;

}




bool checkCommand(char cmd[]){

        

    resetAnalizer();


    /*****************************

    Variables del automata

    *******************************/
    int estado=0;
    char token[100]="";


    /**********Automata**********/

    int i=0; //Variable para recorrer todos los caracteres del comando a ejecutar
    char actual='\0'; //Auxiliar para analizar el caracter actual que se esta leyendo
    int cmdLength= strlen(cmd);

    for(i=0; cmd[i]!='\0' && i<cmdLength; i++ ){
        actual= cmd[i];

        switch(estado){
            case 0:
                if(actual>= 'A' && actual <= 'Z'){
                    actual+=32;

                }
                switch(actual){
                    case '$':
                        estado=2; //En este estado se leen nombres de paramaetros obligatorios
                        break;
                    case '@':
                        estado=7; //En este estado se leen nombres de parametros optativos
                        break;
                    default:
           
                        
                        if(actual>= 'a' && actual <= 'z'){
                            estado=1;
                            append(actCmd, actual);
                        }else if( !(actual==9) && !(actual ==32)){
                            fault=true;
                        }
                        break;
                        
                }
                break;
                
                


            case 1:               
                if(actual>= 'A' && actual <= 'Z'){
                    actual+=32;

                }

                if(actual>= 'a' && actual <= 'z'){ 
                    append(actCmd, actual);
                }else if(actual==9 || actual==32){
                    if(guessCmd(actCmd)){
                        estado= 0;
                    }else{
                        fault= true;
                    }
                    
                }else{
                    fault=true;
                }
                break;
            case 2:

                if(actual>= 'A' && actual <= 'Z'){
                    actual+=32;

                }
                
                if(actual>= 'a' && actual <= 'z'){
                    append(actParam, actual);
                    estado=3;
                }
                
                else if( !(actual==9) && !(actual ==32)){
                    fault =true;
                    
                }
                break;
            case 3:
                
                if(actual>= 'A' && actual <= 'Z'){
                    actual+=32;

                }                
                
                if(actual>= 'a' && actual <= 'z'){
                    append(actParam, actual);
                    
                }else if ( actual==9 || actual==32){
                    if(guessObParam(actParam)){
                        estado=4;
                    }else{
                        fault=true; 
                    }
                    
                }else if (actual>= '0' && actual<= '9'){
                    append(actParam, actual);
                    estado=13;
                }else if( actual=='='){
                    if(guessObParam(actParam)){
                        estado=5;
                    }else{
                        fault =true;
                    }
                    
                }else{
                    fault=true;
                    
                }
                break;
            case 4:
                if(actual== "="){
                    estado=5;
                }else if (!(actual==9) && !(actual ==32)){
                    fault= true;
                    
                }
                break;
            case 5:
                if(actual ==">"){
                    estado=6;
                }else{
                    fault=true;
                }
                break;
            case 6:
                if(actual>= '0' && actual<= '9'){
                    append(token,actual);
                    estado = 15;
                    
                }else if ( actual==34){
                    estado=9;
                }else if(actual>= 'a' && actual <= 'z'){
                    append(token, actual);
                    estado=11;
                }else if (!(actual==9) && !(actual ==32)){
                    fault=true;
                }
            case 7:
                
                if(actual>= 'A' && actual <= 'Z'){
                    actual+=32;

                }    
                
                if(actual>= 'a' && actual <= 'z'){
                    append(actParam, actual);
                    estado=8;
                    
                }else if(!(actual==9) && !(actual ==32)){
                    fault=true;
                }
                break;
            case 8:
                if(actual>= 'A' && actual <= 'Z'){
                    actual+=32;

                }                
                
                if(actual>= 'a' && actual <= 'z'){
                    append(actParam, actual);
                    
                }else if ( actual==9 || actual==32){
                    guessParam(actParam);
                    estado=4;
                }else if( actual=='='){
                    guessParam(actParam);
                    estado=5;
                }else{
                    fault=true;
                    
                }
                break;   
                
            case 9:
                
                if( actual==13 || actual ==10){
                    fault=true;
                }else if( actual==33){
                    setParam(token);
                }else{
                    append(token,actual);
                }
                break;
            case 11:
                if(actual>= 'a' && actual <= 'z'){
                    append(actParam, actual);
                    
                }else if (actual =='_'){
                    append(actParam, actual);
                }else if(actual=='.'){
                    append(actParam,actual);
                    estado=12;
                }
                
            default:
                break;
                
                       
        }
        if(fault){
            resetAnalizer();
            return false;
        }
    }

}


bool setParam(char param[]){
    return true;
}

bool guessObParam(char cmd[]){
    return true;
}
bool guessOpParam(char cmd []){
    
    return true;
}

bool guessCmd(char cmd [] ){
    int it=0;
    for(it=0; it< COMANDOS; it++ ){
        
    }
    return true;
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

    printf( "Comando :  %s..", nuevo.obligados[2]);



}



void append (char *cadena, char car){
        int len= strlen(cadena);
        cadena[len]=car;
        cadena[len+1]= '\0';


}






