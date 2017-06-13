

typedef struct crearDisco {//COMANDO 0
    int tamanio;

    char  path [100];
    char name [100];
    char *obligados[3];

    int parametros;
    bool matched[3];

} mkdisk;



typedef struct borrarDisco{//COMANDO 1
    char path [100];
     char *obligados[1];

    int parametros;
    bool matched[1];
}rmdisk;

typedef struct particiones{ //COMANDO 2 , sUMA DE PRIMARIAS Y EXTENDIDAS ES 4
// SOLO UNA EXTENDIDA, LOGICAS SOLO DENTRO DE EXTENDIDAS
    int tamanio;
    char unit; // 'B', 'K' , 'M'
    char path[100];
    char type; // 'P' , 'E', 'L'
    char fit;//'B' , 'F', 'W'
    char name[100];
    char del; //T es fast, U es full
    int add;
    char *obligados[3]; //,{"tamanio","path","nombre", }
    char *opcionales[4];//= {"add", "del","type", "fit"}
    int parametros;  //


 //si encontramos add o delete le restamos 1 a esta variable
     bool matched[3];
     bool rematched[4];

}fdisk;


typedef struct montar{ //COMANDO 3
    char path[100];
    char name[100];
    char *obligados[2];
    int parametros;
    bool matched[2];
}mount;


typedef struct desmontar{ //COMANDO 4
    char id[100];
     char *obligados;
    int parametros;
    bool matched[1];

}umount;
