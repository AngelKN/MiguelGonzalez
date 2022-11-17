#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#define TAMANO 100

typedef struct{
    int cod;
    char name[50];
    int cantidad;
    float precio;
}tproducto;

struct nodo{
    tproducto pro;
    struct nodo *sig;
    struct nodo *ant;
};

struct nodo *raiz=NULL;

int vacia(){
    if (raiz == NULL)
        return 1;
    else
        return 0;
}

int cantidad()
{
    int cant = 0;
    if (!vacia())
    {
        struct nodo *reco = raiz;
        do {
            cant++;
            reco = reco->sig;
        } while (reco != raiz);
    }
    return cant;
}

void insertar()
{
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

    struct nodo *nuevo;
    nuevo=malloc(sizeof(struct nodo));
    nuevo->pro=producto;
    nuevo->ant = NULL;

    if (raiz == NULL)
    {
        nuevo->sig = NULL;
        raiz = nuevo;

    }
    else
    {
        nuevo->sig=raiz;
        raiz->ant=nuevo;
        raiz=nuevo;
    }

    printf("Producto Almacenado Correctamente.\n");
}

void imprimir()
{
    struct nodo *reco=raiz;
    printf("Lista completa.\n");
    while (reco!=NULL)
    {
        if(vacia())
        {
            printf("NO HAY PRODUCTOS REGISTRADOS\n");
        }else
        {
            printf("Codigo:  %i     Producto: %s     Cantidad: %i    Precio: $%0.2f\n", reco->pro.cod, reco->pro.name, reco->pro.cantidad, reco->pro.precio);
            reco=reco->sig;
        }

    }
    printf("\n");
}

void ventas()
{
    static float total = 0;
    int op = 0, cod;
    int existe=0;
    do
    {
        printf("Ingrese el Codigo del Producto\n");
        cod = 0;
        scanf("%i", &cod);
        fflush(stdin);

        struct nodo *reco=raiz;

        while(reco!=NULL)
        {
            if(cod==reco->pro.cod)
            {
                printf("Codigo:  %i     Producto: %s     Cantidad: %i    Precio: $%0.2f\n", reco->pro.cod, reco->pro.name, reco->pro.cantidad, reco->pro.precio);
                reco->pro.cantidad -= 1;
                total += reco->pro.precio;
                printf("-Total: %0.2f\n", total);
                existe=1;
                break;
            }
        }
        if (existe==0)
        {
            printf("No existe un producto con dicho codigo\n");
        }

        printf("Otro producto SI:1/NO:0: ");
        scanf("%i",&op);
        reco=raiz;

    }while(op==1);

    printf("\n----------------------------\n");
    printf("Total: %0.2f",total);
    printf("\n----------------------------\n\n");

    total=0;
}

void eliminar()
{
    printf("Ingrese el Codigo del Producto\n");
    int cod, existe=0;
    scanf("%i", &cod);
    fflush(stdin);

    struct nodo *reco=raiz;

    while(reco!=NULL)
    {
        if(cod==reco->pro.cod)
        {
            struct nodo *nex=reco->sig;
            struct nodo *bef=reco->ant;
            struct nodo *bor=reco;
            if(reco==raiz)
            {
                printf("Codigo:  %i     Producto: %s     Cantidad: %i    Precio: $%0.2f\n", reco->pro.cod, reco->pro.name, reco->pro.cantidad, reco->pro.precio);
                reco->sig=NULL;
                raiz=nex;

            }else if(reco->sig==NULL)
            {
                printf("Codigo:  %i     Producto: %s     Cantidad: %i    Precio: $%0.2f\n", reco->pro.cod, reco->pro.name, reco->pro.cantidad, reco->pro.precio);
                reco->ant=NULL;
                bef->sig=NULL;
            }else
            {
                printf("Codigo:  %i     Producto: %s     Cantidad: %i    Precio: $%0.2f\n", reco->pro.cod, reco->pro.name, reco->pro.cantidad, reco->pro.precio);
                bef->sig=nex;
                nex->ant=bef;
            }

            existe=1;
            free(bor);
            printf("SE ELIMINO CORRECTAMENTE\n");
            break;
        }
        reco=reco->sig;
    }
    if (existe==0)
    {
        printf("No existe un producto con dicho codigo\n");
    }
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
            case 1: insertar();
                    break;
            case 2: ventas();
                    break;
            case 3: eliminar();
                    break;
            case 4: imprimir();
                    break;
            case 5: printf("SALIENDO\n");
                    break;
            default:printf("SELECCIONE UNA DE LAS OPCIONES\n");
                    break;
        }
    } while (op!=5);
    return 0;
}
