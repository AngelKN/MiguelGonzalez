#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

char nombre[50+1];
char rol[50+1];
char tuser[11] = "Usuario.txt";
char tlibr[11] = "Libros.txt";
char tpres[13] = "Prestados.txt";

typedef struct
{
    int cedula;
    char name[50+1];
    double telefono;
    char correo[50+1];
    char clave[12+1];
    char rol[10+1];
    char estado[10+1];
}tusuarios;

typedef struct
{
    int id;
    char name[50+1];
    int cantidad;
    char autor[50+1];
    char url[12+1];
    char estado[10+1];
}tlibros;

typedef struct
{
    int id;
    char name[50+1];
    int cantidad;
    char autor[50+1];
    char url[12+1];
    char nameU[50+1];
    char fechaHora[70+1];
    char fechaHoraE[70+1];
    char estado[10+1];
}tprestados;

void crearDocUser(char tuser[11])
{
    FILE *arch;
    arch=fopen(tuser,"at");
    if (arch==NULL)
        exit(1);
    fclose(arch);
}

void admin(char tuser[11])
{
    FILE *arch;
    arch=fopen(tuser,"at");
    if (arch==NULL)
        exit(1);
    tusuarios usuario;
    memset(&usuario,0,sizeof(usuario));
    usuario.cedula=100215468;
    strcat(usuario.name,"Lucas");
    usuario.telefono=3208965004;
    strcat(usuario.correo,"lucas@gmail.com");
    strcat(usuario.clave,"123456");
    strcat(usuario.rol,"Admin");
    strcat(usuario.estado,"ACTIVO");
    fwrite(&usuario, sizeof(tusuarios), 1, arch);
    fclose(arch);
}

void crearDocLibro(char tlibr[11])
{
    FILE *arch;
    arch=fopen(tlibr,"at");
    if (arch==NULL)
        exit(1);
    fclose(arch);
}

void crearDocPres(char tpres[13])
{
    FILE *arch;
    arch=fopen("Prestados.txt","at");
    if (arch==NULL)
        exit(1);
    fclose(arch);
}

int codi()
{
    printf("Ingrese el Codigo:");
    int cod=0;
    scanf("%i", &cod);
    return cod;
}

int verificarReg(tusuarios p, char tuser[11])
{
    FILE *arch;
    arch=fopen(tuser,"rt");
    if (arch==NULL)
        exit(1);
    int veri=0;
    tusuarios ver;
    fread(&ver, sizeof(tusuarios), 1, arch);
    while(!feof(arch))
    {
        if((strcmp(p.correo, ver.correo))==0 && (strcmp(p.clave, ver.clave))==0 && (strcmp(ver.estado, "ACTIVO"))==0)
        {
            veri=1;
            break;
        }
        fread(&ver, sizeof(tusuarios), 1, arch);
    }

    return veri;
}

void registro(char tuser[11])
{
    FILE *arch;
    arch=fopen(tuser,"at");
    if (arch==NULL)
        exit(1);
    tusuarios usuario;
    memset(&usuario,0,sizeof(usuario));
    int op=0;
    do{
        printf("Ingrese Cedula:");
        scanf("%i",&usuario.cedula);
        fflush(stdin);
        printf("Ingrese Nombre:");
        gets(usuario.name);
        printf("Ingrese Telefono:");
        scanf("%lf",&usuario.telefono);
        fflush(stdin);
        printf("Ingrese Correo:");
        gets(usuario.correo);
        printf("Ingrese Clave:");
        gets(usuario.clave);
        strcat(usuario.rol,"User");
        strcat(usuario.estado,"ACTIVO");

        int verif=0;

        if(usuario.cedula==0 || (strcmp(usuario.name, ""))==0 || usuario.telefono==0 || (strcmp(usuario.correo, ""))==0 || (strcmp(usuario.clave, ""))==0)
        {
            verif=2;
        }else
        {
            verif=verificarReg(usuario, tuser);
        }

        if(verif==0)
        {
            printf("%cLos Datos Son Correctos? SI:1/NO:0: ",63);
            scanf("%i",&op);
            fflush(stdin);

            if(op!=0 && op!=1)
            {
                op=0;
            }
        }else if(verif==1)
        {
            printf("EL CORREO YA SE ENCUENTRE REGISTRADO\n");
        }else
        {
            printf("NO PUEDE DEJAR ESPACIOS EN BLANCO\n");
        }

    }while(op==0);

    fwrite(&usuario, sizeof(tusuarios), 1, arch);
    printf("SE REGISTRO CORRECTAMENTE\n");
    fclose(arch);
}

int verificarLib(tlibros p, char tlibr[11])
{
    FILE *arch;
    arch=fopen(tlibr,"rt");
    if (arch==NULL)
        exit(1);
    int veri=0;
    tlibros ver;
    memset(&ver,0,sizeof(ver));
    fread(&ver, sizeof(tlibros), 1, arch);
    while(!feof(arch))
    {
        if(ver.id==p.id && (strcmp(ver.name,p.name))==0)
        {
            veri=1;
            break;
        }
        fread(&ver, sizeof(tlibros), 1, arch);
    }

    return veri;
}

int imprimirLib(char tlibr[11])
{
    FILE *arch;
    arch=fopen(tlibr,"rt");
    if (arch==NULL)
        exit(1);

    tlibros libros;
    memset(&libros,0,sizeof(libros));
    fread(&libros, sizeof(tlibros), 1, arch);
    while(!feof(arch))
    {
        if((strcmp(libros.estado, "ACTIVO"))==0 && libros.cantidad!=0)
        {
            printf("-Id: %i  -Libro: %s  -Cantidad: %i  -Autor: %s  -Url: %s  -Estado: %s\n", libros.id, libros.name, libros.cantidad, libros.autor, libros.url, libros.estado);
        }
        fread(&libros, sizeof(tlibros), 1, arch);
    }
    return libros.id;
    fclose(arch);
}

void nuevoLibro(char tlibr[11])
{
    static int ide;
    ide=imprimirLib(tlibr);
    FILE *arch;
    arch=fopen(tlibr,"at");
    if (arch==NULL)
        exit(1);
    tlibros libro;
    memset(&libro,0,sizeof(libro));
    int op=0;
    do{
        //printf("Ingrese id:");

        //fflush(stdin);
        printf("Ingrese Nombre:");
        gets(libro.name);
        printf("Ingrese Cantidad:");
        scanf("%i",&libro.cantidad);
        fflush(stdin);
        printf("Ingrese Autor:");
        gets(libro.autor);
        printf("Ingrese Url:");
        gets(libro.url);
        strcat(libro.estado,"ACTIVO");

        int verif=0;

        if((strcmp(libro.name, ""))==0 || libro.cantidad==0 || (strcmp(libro.autor, ""))==0 || (strcmp(libro.url, ""))==0)
        {
            verif=2;
        }else
        {
            verif=verificarLib(libro, tlibr);
        }

        if(verif==0)
        {
            printf("%cLos Datos Son Correctos? SI:1/NO:0: ",63);
            scanf("%i",&op);
            fflush(stdin);
            if(op!=0 && op!=1)
            {
                op=0;
            }
        }else
        {
            printf("EL LIBRO YA SE ENCUENTRE REGISTRADO\n");
        }

    }while(op==0);
    ide++;
    libro.id=ide;
    fwrite(&libro, sizeof(tlibros), 1, arch);
    printf("SE REGISTRO CORRECTAMENTE\n");
    fclose(arch);
}

void imprimirUser(char tuser[11])
{
    FILE *arch;
    arch=fopen(tuser,"rt");
    if (arch==NULL)
        exit(1);

    tusuarios usuario;
    memset(&usuario,0,sizeof(usuario));
    fread(&usuario, sizeof(tusuarios), 1, arch);
    while(!feof(arch))
    {
        if((strcmp(usuario.estado, "ACTIVO"))==0)
        {
            printf("-Cedula: %i  -Nombre: %s  -Telefono: %0.0f  -Correo: %s  -Clave: %s  -Rol: %s  -Estado: %s\n", usuario.cedula, usuario.name, usuario.telefono, usuario.correo, usuario.clave, usuario.rol, usuario.estado);
        }
        fread(&usuario, sizeof(tusuarios), 1, arch);
    }
    fclose(arch);
}

void imprimirPres(char tpres[13])
{
    FILE *arch;
    arch=fopen("Prestados.txt","rt");
    if (arch==NULL)
        exit(1);

    tprestados prestados;
    memset(&prestados,0,sizeof(prestados));
    fread(&prestados, sizeof(tprestados), 1, arch);
    while(!feof(arch))
    {
        if(prestados.cantidad!=0 && (strcmp(prestados.estado,"ACTIVO"))==0)
        {
            printf("-Id: %i  -Libro: %s  -Cantidad: %i  -Autor: %s  -Url: %s  -Usuario: %s  -Fecha Prestado: %s  -Fecha Entrega: %s  -Estado: %s\n", prestados.id, prestados.name, prestados.cantidad, prestados.autor, prestados.url,prestados.nameU,prestados.fechaHora,prestados.fechaHoraE, prestados.estado);
        }
        fread(&prestados, sizeof(tprestados), 1, arch);
    }
    fclose(arch);
}

void imprimirLibroP(char nom[15])
{
    FILE *arch;
    arch=fopen("Prestados.txt","rb");
    if (arch==NULL)
        exit(1);

    tprestados press;
    memset(&press,0,sizeof(press));
    fread(&press, sizeof(tprestados), 1, arch);
    while(!feof(arch))
    {
        if(press.id != 0)
        {
            if((strcmp(rol, "Admin"))==0 && ((strcmp(nom, press.nameU))==0 || (strcmp(nom, press.name))==0))
            {
                printf("-Id: %i  -Libro: %s  -Cantidad: %i  -Autor: %s  -Url: %s  -Usuario: %s  -Fecha Prestado: %s  -Fecha Entrega: %s  -Estado: %s\n", press.id, press.name, press.cantidad, press.autor, press.url,press.nameU,press.fechaHora,press.fechaHoraE, press.estado);
            }else if((strcmp(press.nameU, nombre))==0)
            {
                printf("-Id: %i  -Libro: %s  -Cantidad: %i  -Autor: %s  -Url: %s  -Usuario: %s  -Fecha Prestado: %s  -Fecha Entrega: %s  -Estado: %s\n", press.id, press.name, press.cantidad, press.autor, press.url,press.nameU,press.fechaHora,press.fechaHoraE, press.estado);
            }

        }
        fread(&press, sizeof(tprestados), 1, arch);
    }
    fclose(arch);
}

int imprimirPresVeri(char tpres[13], char nom[15], int cod)
{
    FILE *arch;
    arch=fopen("Prestados.txt","rt");
    if (arch==NULL)
        exit(1);
    int existe=0;
    tprestados prestados;
    memset(&prestados,0,sizeof(prestados));
    fread(&prestados, sizeof(tprestados), 1, arch);
    while(!feof(arch))
    {
        if(prestados.id==cod && prestados.cantidad!=0 && (strcmp(prestados.estado,"ACTIVO"))==0)
        {
            if((strcmp(prestados.nameU,nom))==0)
            {
                existe=1;
                break;
            }
        }
        fread(&prestados, sizeof(tprestados), 1, arch);
    }
    return existe;
    fclose(arch);
}

int imprimirLibSoli(char tlibr[11])
{
    FILE *arch;
    arch=fopen(tlibr,"rt");
    if (arch==NULL)
        exit(1);

    tlibros libros;
    memset(&libros,0,sizeof(libros));
    fread(&libros, sizeof(tlibros), 1, arch);
    while(!feof(arch))
    {
        if((strcmp(libros.estado, "ACTIVO"))==0 && libros.cantidad!=0)
        {
            if(imprimirPresVeri(tpres, nombre, libros.id)==0)
            {
                printf("-Id: %i  -Libro: %s  -Cantidad: %i  -Autor: %s  -Url: %s  -Estado: %s\n", libros.id, libros.name, libros.cantidad, libros.autor, libros.url, libros.estado);
            }
        }
        fread(&libros, sizeof(tlibros), 1, arch);
    }
    return libros.id;
    fclose(arch);
}

void bloquearUser(char tuser[11])
{
    FILE *arch;
    arch=fopen(tuser,"r+b");
    if (arch==NULL)
        exit(1);
    int cod = codi();
    tusuarios usuario;
    memset(&usuario,0,sizeof(usuario));
    int existe=0;
    fread(&usuario, sizeof(tusuarios), 1, arch);
    while(!feof(arch))
    {
        if (cod==usuario.cedula)
        {
            printf("-Cedula: %i  -Nombre: %s  -Telefono: %i  -Correo: %s  -Clave: %s  -Rol: %s  -Estado: %s\n", usuario.cedula, usuario.name, usuario.telefono, usuario.correo, usuario.clave, usuario.rol, usuario.estado);
            strcpy(usuario.estado,"INACTIVO");
            int pos=ftell(arch)-sizeof(tusuarios);
            fseek(arch,pos,SEEK_SET);
            fwrite(&usuario, sizeof(tusuarios), 1, arch);
            printf("Se bloqueo el usuario.\n");
            existe=1;
            break;
        }
        fread(&usuario, sizeof(tusuarios), 1, arch);
    }
    if (existe==0)
        printf("No existe un usuario con dicha cedula\n");
    else
        printf("SE BLOQUEO CORRECTAMENTE\n");
    fclose(arch);
}

void eliminarLibro(char tlibr[11])
{
    FILE *arch;
    arch=fopen(tlibr,"r+b");
    if (arch==NULL)
        exit(1);
    int cod=codi();
    tlibros libro;
    memset(&libro,0,sizeof(libro));
    int existe=0;
    fread(&libro, sizeof(tlibros), 1, arch);
    while(!feof(arch))
    {
        if (cod==libro.id)
        {
            printf("-Id: %i  -Libro: %s  -Cantidad: %i  -Autor: %s  -Url: %s\n", libro.id, libro.name, libro.cantidad, libro.autor, libro.url);
            strcpy(libro.estado,"INACTIVO");
            int pos=ftell(arch)-sizeof(tlibros);
            fseek(arch,pos,SEEK_SET);
            fwrite(&libro, sizeof(tlibros), 1, arch);
            printf("Se elimino el producto.\n");
            existe=1;
            break;
        }
        fread(&libro, sizeof(tlibros), 1, arch);
    }
    if (existe==0)
        printf("No existe un libro con dicho codigo\n");
    else
        printf("SE ELIMINO CORRECTAMENTE\n");
    fclose(arch);
}

void verLibro(char tlibr[11])
{
    FILE *arch;
    arch=fopen(tlibr,"r+b");
    if (arch==NULL)
        exit(1);

    printf("Ingrese el codigo del libro a modificar:");
    int cod;
    scanf("%i", &cod);
    tlibros libro;
    memset(&libro,0,sizeof(libro));
    int existe=0;
    fread(&libro, sizeof(tlibros), 1, arch);
    while(!feof(arch))
    {
        if (cod==libro.id)
        {
            printf("-Id: %i  -Libro: %s  -Cantidad: %i  -Autor: %s  -Url: %s\n", libro.id, libro.name, libro.cantidad, libro.autor, libro.url);

            printf("ID: %i\n",libro.id);
            scanf("%i",&libro.id);
            fflush(stdin);
            printf("Libro: %s\n",libro.name);
            gets(libro.name);
            printf("Cantidad: %i\n",libro.cantidad);
            scanf("%i",&libro.cantidad);
            fflush(stdin);
            printf("Autor: %s\n",libro.autor);
            gets(libro.autor);
            printf("Url: %s\n",libro.url);
            gets(libro.url);
            printf("Estado: %s\n",libro.estado);


            int op=0;
            printf("¿Desea editar el libro? SI:1/NO:0: ");
            scanf("%i",&op);
            fflush(stdin);

            if(op==1)
            {
                int pos=ftell(arch)-sizeof(tlibros);
                fseek(arch,pos,SEEK_SET);
                fwrite(&libro, sizeof(tlibros), 1, arch);
                printf("Se modifico el libro.\n");
            }
            existe=1;
            break;
        }
        fread(&libro, sizeof(tlibros), 1, arch);
    }
    if (existe==0)
        printf("No existe un libro con dicho codigo\n");
    fclose(arch);
}

void prestados(tlibros libro, char tpres[13])
{
    FILE *arch;
    arch=fopen("Prestados.txt","at");
    if (arch==NULL)
        exit(1);

    time_t t = time(NULL);
    struct tm tiempoLocal = *localtime(&t);
    char fechaHora[70];
    char *formato = "%Y-%m-%d %H:%M:%S";
    int bytesEscritos = strftime(fechaHora, sizeof fechaHora, formato, &tiempoLocal);

    int inicio = 8;
    int cantidadCaracteres = 2;
    char dia[2+1] = "";
    strncpy(dia, fechaHora + inicio, cantidadCaracteres);
    int diae = atoi(dia);

    inicio = 5;
    cantidadCaracteres = 2;
    char mes[2+1] = "";
    strncpy(mes, fechaHora + inicio, cantidadCaracteres);
    int mese = atoi(mes);

    inicio = 0;
    cantidadCaracteres = 4;
    char ano[4+1] = "";
    strncpy(ano, fechaHora + inicio, cantidadCaracteres);
    int anoe = atoi(ano);

    inicio = 11;
    cantidadCaracteres = 8;
    char hora[8+1] = "";
    strncpy(hora, fechaHora + inicio, cantidadCaracteres);

    diae+=7;

    if(diae<31)
    {
        diae++;
    }else
    {
        diae-=31;
        if(mese!=12)
        {
            mese++;
        }else
        {
            mese=1;
            int inicio = 0;
            int cantidadCaracteres = 0;
            char ano[5+1] = "";
            strncpy(ano, fechaHora + inicio, cantidadCaracteres);
            int anoe = atoi(ano);
            anoe++;
        }
    }

    char total[70+1]="";
    char text[20+1]="";
    sprintf(text,"%d",anoe);
    strcat(total,text);
    strcat(total,"/");
    sprintf(text,"%d",mese);
    strcat(total,text);
    strcat(total,"/");
    sprintf(text,"%d",diae);
    strcat(total,text);
    strcat(total," ");
    strcat(total,hora);

    if (bytesEscritos != 0) {
        // Si no hay error, los bytesEscritos no son 0
        printf("Fecha y hora de Prestamo: %s\n", fechaHora);

        printf("Fecha de Entrega: %s\n",total);
    } else {
        printf("Error formateando fecha");
    }

    tprestados press;
    memset(&press,0,sizeof(press));
    press.id=libro.id;
    strcpy(press.name,libro.name);
    press.cantidad++;
    strcpy(press.autor,libro.autor);
    strcpy(press.url,libro.url);
    strcpy(press.nameU,nombre);
    strcpy(press.fechaHora,fechaHora);
    strcpy(press.fechaHoraE,total);
    strcpy(press.estado,"ACTIVO");


    fwrite(&press, sizeof(tprestados), 1, arch);
    printf("LIBRO PRESTADO\n");
    memset(&press,0,sizeof(tprestados));
    fclose(arch);
}

void prestarLibro(char tpres[13])
{
    FILE *arch;
    arch=fopen("Libros.txt","r+b");
    if (arch==NULL)
        exit(1);

    imprimirLibSoli(tlibr);
    int cod=codi();
    int useVer=0;
    tlibros libro;
    memset(&libro,0,sizeof(libro));
    int existe=0;

    fread(&libro, sizeof(tlibros), 1, arch);
    while(!feof(arch))
    {
        useVer=imprimirPresVeri(tpres,nombre,libro.id);
        if (cod==libro.id && (strcmp(libro.estado, "INACTIVO"))!=0 && useVer==0)
        {
            printf("-Id: %i  -Libro: %s  -Cantidad: %i  -Autor: %s  -Url: %s\n", libro.id, libro.name, libro.cantidad, libro.autor, libro.url);
            libro.cantidad--;
            int pos=ftell(arch)-sizeof(tlibros);
            fseek(arch,pos,SEEK_SET);
            fwrite(&libro, sizeof(tlibros), 1, arch);

            prestados(libro, tpres);


            existe=1;
            break;
        }

        fread(&libro, sizeof(tlibros), 1, arch);
    }
    cod=0;
    if (existe==0)
        printf("No existe un libro con dicho codigo\n");
    fclose(arch);
}

void devolver(int cod, char tlibr[11])
{
    FILE *arch;
    arch=fopen(tlibr,"r+b");
    if (arch==NULL)
        exit(1);
    tlibros libro;
    memset(&libro,0,sizeof(libro));
    fread(&libro, sizeof(tlibros), 1, arch);
    while(!feof(arch))
    {
        if (cod==libro.id)
        {
            libro.cantidad++;
            int pos=ftell(arch)-sizeof(tlibros);
            fseek(arch,pos,SEEK_SET);
            fwrite(&libro, sizeof(tlibros), 1, arch);

            break;
        }
        fread(&libro, sizeof(tlibros), 1, arch);
    }
    fclose(arch);
}

void devolverLibro()
{
    FILE *arch;
    arch=fopen("Prestados.txt","r+b");
    if (arch==NULL)
        exit(1);
    printf("Ingrese el codigo del libro a devolver:");
    int cod;
    scanf("%i", &cod);
    tprestados press;
    memset(&press,0,sizeof(press));
    int existe=0;
    fread(&press, sizeof(tprestados), 1, arch);
    while(!feof(arch))
    {
        if (cod==press.id && press.cantidad!=0)
        {
            printf("-Id: %i  -Libro: %s  -Cantidad: %i  -Autor: %s  -Url: %s\n", press.id, press.name, press.cantidad, press.autor,press.url);
            devolver(press.id, tlibr);
            strcpy(press.estado,"INACTIVO");
            press.id=0;
            press.cantidad=0;
            int pos=ftell(arch)-sizeof(tprestados);
            fseek(arch,pos,SEEK_SET);
            fwrite(&press, sizeof(tprestados), 1, arch);

            existe=1;
            break;
        }
        fread(&press, sizeof(tprestados), 1, arch);
    }
    if (existe==0)
        printf("No existe un prestamo con dicho codigo\n");
    printf("SE DEVOLVIO EL LIBRO\n");
    fclose(arch);
}

void menuUsuario()
{
    int op=0;

    do {
        printf("\n---------BIENVENID@ %s -- %s---------\n",nombre,rol);
        printf("\n------------Menu Usuarios------------\n");
        printf("1 - Solicitar Prestamo Libro \n");
        printf("2 - Devolver Libro\n");
        printf("3 - Lista Disponible\n");
        printf("4 - Mis Libros\n");
        printf("5 - Salir\n");
        printf("----------------------------\n");
        printf("Ingrese su opcion:");
        scanf("%i",&op);
        fflush(stdin);
        switch (op) {
            case 1:
                printf("------------Libros Registrados------------\n");
                prestarLibro(tlibr);
                break;
            case 2:
                printf("------------Mis Libros------------\n");
                imprimirLibroP(0);
                printf("----------------------------\n");
                devolverLibro();
                break;
            case 3:
                imprimirLib(tlibr);
                break;
            case 4:
                printf("------------Mis Libro------------\n");
                imprimirLibroP(0);
                break;
            case 5: printf("SALIENDO\n");
                break;
            default: printf("SELECCIONE UNA DE LAS OPCIONES\n");
                break;
        }
    } while (op!=5);
}

void menuAdmin()
{
    int op=0;
    char nom[15];

    do {
        printf("\n---------BIENVENID@ %s -- %s---------\n",nombre,rol);
        printf("------------Menu Administrador------------\n");
        printf("1 - Agregar Libro \n");
        printf("2 - Eliminar Libro\n");
        printf("3 - Editar Libro \n");
        printf("4 - Bloquear Usuario\n");
        printf("5 - Prestados Por Libro\n");
        printf("6 - Prestados Por Usuario\n");
        printf("7 - Usuarios Retrasados\n");
        printf("8 - Salir\n");
        printf("----------------------------\n");
        printf("Ingrese su opcion:");
        scanf("%i",&op);
        fflush(stdin);
        switch (op) {
            case 1:
                imprimirLib(tlibr);
                printf("----------------------------\n");
                nuevoLibro(tlibr);
                break;
            case 2:
                printf("------------Libros Registrados------------\n");
                imprimirLib(tlibr);
                printf("----------------------------\n");
                eliminarLibro(tlibr);
                break;
            case 3:
                printf("------------Libros Registrados------------\n");
                imprimirLib(tlibr);
                printf("----------------------------\n");
                verLibro(tlibr);
                break;
            case 4:
                printf("------------Usuarios Registrados------------\n");
                imprimirUser(tuser);
                printf("----------------------------\n");
                bloquearUser(tuser);
                break;
            case 5:
                printf("------------Libros Registrados------------\n");
                imprimirLib(tlibr);
                printf("----------------------------\n");
                printf("Ingrese el Codigo:");
                gets(nom);
                imprimirLibroP(nom);
                break;
            case 6:
                printf("------------Usuarios Registrados------------\n");
                imprimirUser(tuser);
                printf("----------------------------\n");
                printf("Ingrese el Codigo:");
                gets(nom);
                imprimirLibroP(nom);
                break;
            case 7:
                imprimirPres(tpres);
                printf("----------------------------\n");
                break;
            case 8:
                printf("SALIENDO\n");
                break;
            default:printf("SELECCIONE UNA DE LAS OPCIONES\n");
                break;
        }
    } while (op!=8);
}

void login(char tuser[11])
{
    char correo[50];
    char clave[12];
    int existe=0;

    FILE *arch;
    arch=fopen(tuser,"rb");
    if (arch==NULL)
        exit(1);

    printf("Ingrese Correo:");
    gets(correo);
    printf("Ingrese Clave:");
    gets(clave);

    tusuarios usuario;
    memset(&usuario,0x00,sizeof(usuario));
    fread(&usuario, sizeof(tusuarios), 1, arch);
    while(!feof(arch))
    {
        if(usuario.cedula != 0)
        {
            if((strcmp(usuario.correo,correo))==0 && (strcmp(usuario.clave,clave))==0 && (strcmp(usuario.estado,"ACTIVO"))==0)
            {
                strcpy(nombre,usuario.name);
                if((strcmp(usuario.rol,"User"))==0)
                {
                    strcpy(rol,usuario.rol);
                    menuUsuario();
                }else
                {
                    strcpy(rol,usuario.rol);
                    menuAdmin();
                }

                existe=1;
            }
        }
        fread(&usuario, sizeof(tusuarios), 1, arch);
    }

    if(existe==0)
    {
        printf("ERROR DE USUARIO O CONTRESENA\n");
    }

    fclose(arch);
}

int main() {
    crearDocUser(tuser);
    crearDocLibro(tlibr);
    crearDocPres(tpres);
    //admin(tuser);
    int op;
    do {
        op=0;
        printf("\n------------Menu------------\n");
        printf("1 - Ingresar\n");
        printf("2 - Registrarse\n");
        printf("3 - Salir\n");
        printf("----------------------------\n");
        printf("Ingrese su opcion:");
        scanf("%i",&op);
        fflush(stdin);
        switch (op) {
            case 1: login(tuser);
                break;
            case 2:
                system("cls");
                registro(tuser);
                break;
            case 3:
                imprimirLib(tlibr);
                imprimirUser(tuser);
                imprimirLibroP(tpres);
                printf("SALIENDO\n");
                break;
            default:printf("SELECCIONE UNA DE LAS OPCIONES\n");
                break;
        }
    } while (op!=3);
    return 0;
}
