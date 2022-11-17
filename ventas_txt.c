#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

typedef struct{
    int cod;
    char name[50];
    int cantidad;
    float precio;
}tproducto;

struct nodo{
    tproducto pro;
    struct nodo *sig;
};

struct nodo *raiz=NULL;

void insertar(int pro, char name[50], int cantidad, float precio)
{
    struct nodo *nuevo;
    nuevo = malloc(sizeof(struct nodo));
    nuevo->pro.cod = pro;
    strcat(nuevo->pro.name,name);
    nuevo->pro.cantidad = cantidad;
    nuevo->pro.precio = precio;
    if (raiz == NULL)
    {
        raiz = nuevo;
        nuevo->sig = NULL;
    }
    else
    {
        nuevo->sig = raiz;
        raiz = nuevo;
    }
}

void crear()
{
    FILE *arch;
    arch=fopen("DB.txt","wb");
    if (arch==NULL)
        exit(1);
    fclose(arch);
}

void cargar()
{
    FILE *arch;
    arch=fopen("DB.txt","ab");
    if (arch==NULL)
        exit(1);
    tproducto producto;

    printf("Ingrese el codigo del producto:");
    scanf("%i",&producto.cod);
    fflush(stdin);

    printf("Ingrese el nombre del producto:");
    gets(producto.name);
    fflush(stdin);

    printf("Ingrese la cantidad del producto:");
    scanf("%i",&producto.cantidad);
    fflush(stdin);

    printf("Ingrese el precio:");
    scanf("%f",&producto.precio);
    fflush(stdin);

    fwrite(&producto, sizeof(tproducto), 1, arch);
    fclose(arch);
}

void listado()
{
    FILE *arch;
    arch=fopen("DB.txt","rb");
    if (arch==NULL)
        exit(1);
    tproducto producto;
    fread(&producto, sizeof(tproducto), 1, arch);
    while(!feof(arch))
    {
        if(producto.cod != 0)
        {
            printf("-Codigo: %i  -Producto: %s  -Cantidad: %i  -Precio: %0.2f\n", producto.cod, producto.name, producto.cantidad, producto.precio);
        }
        fread(&producto, sizeof(tproducto), 1, arch);

    }
    fclose(arch);
}

float vender()
{
    int op=0;
    static float total = 0.0;

    float *mas=&total;
        FILE *arch;
        arch=fopen("DB.txt","r+t");
        if (arch==NULL)
            exit(1);

    do{
        printf("Ingrese el codigo de producto:");
        int cod=0;
        scanf("%i", &cod);
        tproducto producto;
        int existe=0;
        fread(&producto, sizeof(tproducto), 1, arch);
        while(!feof(arch))
        {
            if (cod==producto.cod)
            {
                //mostrar y almacenar en el nodo
                printf("-Codigo: %i  -Producto: %s  -Cantidad: %i  -Precio: %0.2f\n", producto.cod, producto.name, producto.cantidad, producto.precio);
                insertar(producto.cod, producto.name, producto.cantidad, producto.precio);

                //disminuir la cantidad
                producto.cantidad--;
                int pos=ftell(arch)-sizeof(tproducto);
                fseek(arch,pos,SEEK_SET);
                fwrite(&producto, sizeof(tproducto), 1, arch);

                //calcular el valor total
                total += producto.precio;
                printf("-Total: %0.2f\n", total);
                existe=1;
                break;
            }
            fread(&producto, sizeof(tproducto), 1, arch);
        }
        if (existe==0)
        {
            printf("No existe un producto con dicho codigo\n");
        }

        fseek(arch,0,SEEK_SET);

        printf("Otro producto SI:1/NO:0: ");
        scanf("%i",&op);

    }while(op==1);

    printf("\n----------------------------\n");
    factura();
    printf("Total: %0.2f",total);
    printf("\n----------------------------\n\n");


    liberar();
    total=0;

    fclose(arch);
    return total;
}

void factura()
{
    struct nodo *reco=raiz;
    printf("Factura\n");
    while (reco!=NULL)
    {
        printf("-Codigo: %i  -Producto: %s  -Cantidad: %i  -Precio: %0.2f\n", reco->pro.cod, reco->pro.name, reco->pro.cantidad, reco->pro.precio);
        reco=reco->sig;
    }
    printf("\n");
}

void liberar(){
    struct nodo *reco=raiz;
    struct nodo *bor;
    while (reco!=NULL)
    {
        bor=reco;
        reco=reco->sig;
        bor->sig=NULL;
        raiz=NULL;
    }
    printf("\n");
}

void eliminar()
{
   FILE *arch;
   arch=fopen("DB.txt","r+b");
   if (arch==NULL)
       exit(1);
   printf("Ingrese el codigo de producto a eliminar:");
   int cod;
   scanf("%i", &cod);
   tproducto producto;
   int existe=0;
   fread(&producto, sizeof(tproducto), 1, arch);
   while(!feof(arch))
   {
       if (cod==producto.cod)
       {
          printf("-Codigo: %i  -Producto: %s  -Cantidad: %i  -Precio: %0.2f\n", producto.cod, producto.name, producto.cantidad, producto.precio);
          producto.cod=0;
          int pos=ftell(arch)-sizeof(tproducto);
          fseek(arch,pos,SEEK_SET);
          fwrite(&producto, sizeof(tproducto), 1, arch);
          printf("Se eliminar el producto.\n");
          existe=1;
          break;
       }
       fread(&producto, sizeof(tproducto), 1, arch);
   }
   if (existe==0)
       printf("No existe un producto con dicho codigo\n");
   fclose(arch);
}

int main()
{
    int op;
    float total=0;

    do {
        printf("\n------------Menu------------\n");
        printf("1 - Registrar nuevo producto\n");
        printf("2 - Vender Producto\n");
        printf("3 - Eliminar Producto\n");
        printf("4 - Listar Productos\n");
        printf("5 - Finalizar\n");
        printf("----------------------------\n");
        printf("Ingrese su opcion:");
        scanf("%i",&op);
        fflush(stdin);
        switch (op) {
            case 1: cargar();
                    listado();
                    break;
            case 2: vender();
                    break;
            case 3: listado();
                    eliminar();
                    break;
            case 4: listado();
                    break;
            default:printf("SELECCIONE UNA DE LAS OPCIONES\n");
        }
    } while (op!=5);
    return 0;
}
