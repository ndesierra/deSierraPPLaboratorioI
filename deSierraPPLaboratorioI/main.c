#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "datawarehouse.h"

#define TAMMARCA 3
#define TAMCOLOR 5
#define TAMAUTO 5
#define TAMSER 5
#define TAMT 5
#define HARD_TAM 5

typedef struct
{
    int dia;
    int mes;
    int anio;

} eFecha;

typedef struct
{
    int id;
    char descripcion[20];

} eMarca;

typedef struct
{
    int id;
    char nombreColor[20];

} eColor;

typedef struct
{

    int id;
    char patente[10];
    int idMarca;
    int idColor;
    eFecha modelo;
    int isEmpty;

} eAuto;

typedef struct
{

    int id;
    char descripcion[25];
    float precio;

} eServicio;

typedef struct
{

    int id;
    int patente;
    int idServicio;
    eFecha fecha;
    int isEmpty;

} eTrabajo;

void hardcodearMarcas(eMarca vec[], int cant);
void hardcodearColores(eColor vec[], int cant);
void hardcodearServicios(eServicio vec[], int cant);
char menu();
void inicializarAutos(eAuto vec[], int tamauto);
int altaAuto(int idx, eAuto vec[], int tamauto, eMarca marcas[], int tammarca, eColor colores[], int tamcolor);
int buscarLibreAuto(eAuto vec[], int tamauto);
int submenuAuto();
int modificarAuto(eAuto vec[], int tamauto, eColor colores[], int tamcolor, eMarca marcas[], int tammarca);
int buscarAuto(char patente, eAuto vec[], int tamauto);
void bajaAuto(eAuto vec[], int tamauto, eMarca marcas[], int tammarca,eColor colores[], int tamcolor);
void mostrarAuto(eAuto x, eMarca marcas[], int tammarca,eColor colores[], int tamcolor);
int cargarDescripcionMarca(char descripcionMarca[], int idMarca, eMarca marcas[], int tammarca);
int cargarDescripcionColor(char descripcionColor[], int idColor, eColor colores[], int tamcolor);
void listarAutos(int tamauto, eAuto autos[], eMarca marcas[], int tammarca);
void listarMarcas(eMarca marcas[], int tammarca);
void listarColores(eColor colores[], int tamcolor);
void listarServicios(eServicio servicios[], int tamser);
int altaTrabajo(int idx, eTrabajo vec[], int tamt, eAuto autos[], int tamauto, eServicio servicios[], int tamser, int tammarca, int tamcolor);
int buscarLibreTrabajo(eTrabajo vec[], int tamt);
//void mostrarServicios(eServicio x, int tamser);
//int cargarDescripcionServicio(char descripcionServicio, eServicio servicios[], int tamser, int idServicio);

int main()
{
    char seguir = 's';
    char confirma;
    int idAuto = 1;
    int proximoIdMarca = 1000;
    int proximoIdColor = 5000;
    int proximoIdServicio = 20000;
    eMarca marcas [TAMMARCA];
    eColor colores [TAMCOLOR];
    eAuto autos [TAMAUTO];
    eServicio servicios [TAMSER];
    eTrabajo trabajos [TAMT];

    inicializarAutos(autos, TAMAUTO);

    hardcodearMarcas(marcas, HARD_TAM);
    proximoIdMarca+= HARD_TAM;


    do
    {
        switch(menu())
        {
        case 'a':
            if ((altaAuto(idAuto, autos, TAMAUTO, marcas, TAMMARCA, colores, TAMCOLOR))== 1)
            {
                idAuto++;
                proximoIdMarca++;
                proximoIdColor++;
            }
            break;
        case 'b':
            modificarAuto(autos, TAMAUTO, colores, TAMCOLOR, marcas, TAMMARCA);
            break;
        case 'c':
            bajaAuto(autos,TAMAUTO, marcas, TAMMARCA, colores,TAMCOLOR);
            break;
        case 'd':
            listarAutos(TAMAUTO, autos, marcas,TAMMARCA);
            break;
        case 'e':
            listarMarcas(marcas, TAMMARCA);
            break;
        case 'f':
            listarColores(colores, TAMCOLOR);
            break;
        case 'g':
            listarServicios(servicios, TAMSER);
            break;
        case 'h':
            printf("H.	ALTA TRABAJO\n");
            break;
        case 'i':
            printf("I.	LISTAR TRABAJOS\n");
            break;
        case 'j':
            printf("J. SALIR\n\n");
            fflush(stdin);
            scanf("%c", &confirma);
            if (confirma == 's')
            {
                seguir = 'n';
            }
            break;
        }
        system("pause");

    }
    while (seguir == 's');

    return 0;
    return 0;
}

void hardcodearMarcas(eMarca vec[], int cant){

    for(int i=0; i < cant; i++){
        strcpy( vec[i].descripcion, marcas[i]);
    }
}
void hardcodearColores(eColor vec[], int cant){

    for(int i=0; i < cant; i++){
        strcpy( vec[i].nombreColor, colores[i]);
    }
}
void hardcodearServicios(eServicio vec[], int cant){

    char descripcion[20];

    for(int i=0; i < cant; i++){
        strcpy( vec[i].descripcion, descripcion);
        vec[i].precio = precioServicio[i];
    }
}
char menu()
{
    char opcion;

    system("cls");
    printf("***Gestion de Lavadero***\n\n");
    printf("A.	ALTA AUTO\n");
    printf("B.	MODIFICAR AUTO:\n");
    printf("C.	BAJA AUTO\n");
    printf("D.	LISTAR AUTOS\n");
    printf("E.	LISTAR  MARCAS \n");
    printf("F.	LISTAR COLORES\n");
    printf("G.	LISTAR SERVICIOS\n");
    printf("H.	ALTA TRABAJO\n");
    printf("I.	LISTAR TRABAJOS\n");
    printf("J. SALIR\n\n");
    printf("Ingrese opcion: ");
    fflush(stdin);
    scanf("%c", &opcion);

    return opcion;

}
void inicializarAutos(eAuto vec[], int tamauto)
{

    for(int i=0; i < tamauto; i++)
    {
        vec[i].isEmpty = 1;
    }
}

int altaAuto(int idx, eAuto vec[], int tamauto, eMarca marcas[], int tammarca, eColor colores[], int tamcolor)
{
    int todoOk = 0;
    int indice = buscarLibreAuto(vec, tamauto);
    eAuto auxAuto;

    system("cls");
    printf("***Alta Auto***\n\n");

    if(indice == -1) //hay lugar?
    {
        printf("Sistema completo\n\n");
    }
    else
    {
            auxAuto.id = idx;

            printf("Ingrese patente: ");
            fflush(stdin);
            gets(auxAuto.patente);

            printf("Ingrese IdMarca: ");
            fflush(stdin);
            scanf("%d", &auxAuto.idMarca);

            printf("Ingrese IdColor: ");
            scanf("%d", &auxAuto.idColor);

            printf("Ingrese modelo: ");
            scanf("%4d", &auxAuto.modelo.anio);

            vec[indice] = auxAuto;//copio al vector del empleado nuevo
            todoOk = 1;
        }

    return todoOk;
}
int buscarLibreAuto(eAuto vec[], int tamauto)
{

    int indice = -1;

    for(int i=0; i < tamauto; i++)
    {
        if(vec[i].isEmpty == 1)
        {
            indice = i;
            break;
        }
    }

    return indice;
}
int submenuAuto()
{
    int opcion;

    system("cls");
    printf("***Parametros***\n\n");
    printf("1. Color\n");
    printf("2. Modelo\n");
    printf("3. Salir\n");
    printf("Ingrese opcion: ");
    fflush(stdin);
    scanf("%d", &opcion);

    return opcion;
}
int modificarAuto(eAuto vec[], int tamauto, eColor colores[], int tamcolor, eMarca marcas[], int tammarca)
{
    int exit = 0;
    char patente[10];
    char indice;
    char confirma;
    int nuevoColor;
    //float nuevoModelo;
    eFecha nuevoModelo;

    system("cls");
    printf("***Modificar Auto***\n\n");
    printf("Ingrese patente: ");
    gets(patente);

    indice = buscarAuto(patente, vec, tamauto);

    if(   indice == -1   )
    {

        printf("No hay registro de un auto con la patente: %s\n", patente);
    }
    else
    {
        mostrarAuto(vec[indice], marcas, tammarca, colores, tamcolor);

        printf("Ingrese el tipo de dato que desea modificar: ");
        switch(submenuAuto())
        {
        case 1:
            printf("\nModifica el color?: \n");
            fflush(stdin);
            scanf("%c", &confirma);

            if( confirma == 's')
            {
                printf("Ingrese el nuevo id Color: ");
                scanf("%d", & nuevoColor);
                fflush(stdin);

                vec[indice].idColor = nuevoColor;
                printf("Se ha actualizado el color con éxito\n\n");
            }
            else
            {
                printf("Se ha cancelado la operacion\n\n");
            }
            break;
        case 2:
            printf("\nModifica el modelo?: \n");
            fflush(stdin);
            scanf("%4d", &nuevoModelo.anio);

            if( confirma == 's')
            {
                printf("Ingrese el nuevo modelo: ");
                scanf("%d", &nuevoModelo.anio);
                fflush(stdin);

                vec[indice].modelo.anio = nuevoModelo.anio;
                printf("Se ha actualizado el sexo con exito\n\n");
            }
            else
            {
                printf("Se ha cancelado la operacion\n\n");
            }
            break;
        case 3:
            printf("Salir\n");
            exit = 1;
            break;
        default:
            printf("No es un parametro valido");
            break;
        }
    }
    return exit;
}
int buscarAuto(char patente, eAuto vec[], int tamauto)
{
    int indice = -1;

    for(int i=0; i < tamauto; i++)
    {

        if(vec[i].patente == patente && vec[i].isEmpty == 0)
        {
            indice = i;
            break;
        }
    }
    return indice;
}

void bajaAuto(eAuto vec[], int tamauto, eMarca marcas[], int tammarca,eColor colores[], int tamcolor)
{

    char patente;
    int indice;
    char confirma;

    system("cls");
    printf("***Baja Auto***\n\n");
    printf("Ingrese patente: ");
    gets(patente);

    indice = buscarAuto(patente, vec, tamauto);

    if(   indice == -1   )
    {

        printf("No hay registro de un auto con la patente: %s\n", patente);
    }
    else
    {
        mostrarAuto(vec[indice], marcas, tammarca, colores, tamcolor);

        printf("\nConfirma BAJA?: \n");
        fflush(stdin);
        scanf("%c", &confirma);

        if( confirma == 's')
        {
            vec[indice].isEmpty = 1;
            printf("Se ha realizado la baja con exito\n\n");
        }
        else
        {
            printf("Se ha cancelado la operacion\n");
        }
    }
}

void mostrarAuto(eAuto x, eMarca marcas[], int tammarca,eColor colores[], int tamcolor)
{
    char descripcionMarca[20];
    char descripcionColor[20];

    cargarDescripcionMarca(descripcionMarca, x.idMarca, marcas, tammarca);
    cargarDescripcionColor(descripcionColor, x.idColor, colores, tamcolor);

    printf("\n   %d   %10s   %10s   %10s      %4d   \n", x.id, x.patente, descripcionMarca, descripcionColor, x.modelo.anio);

}
int cargarDescripcionMarca(char descripcionMarca[], int idMarca, eMarca marcas[], int tammarca){

    int todoOk = 0;
    for(int i=0; i < tammarca; i++){
        if(marcas[i].id == idMarca){
            strcpy(descripcionMarca, marcas[i].descripcion);
            todoOk = 1;
        }
    }
    return todoOk;
}
int cargarDescripcionColor(char descripcionColor[], int idColor, eColor colores[], int tamcolor){

    int todoOk = 0;
    for(int i=0; i < tamcolor; i++){
        if(colores[i].id == idColor){
            strcpy(descripcionColor, colores[i].nombreColor);
            todoOk = 1;
        }
    }
    return todoOk;
}
void listarAutos(int tamauto, eAuto autos[], eMarca marcas[], int tammarca){

    system("cls");
    printf("\n****Listado de Autos****\n");
    printf("    Patente        Descripcion\n\n");

    for(int i=0; i < tamauto; i++)
    {
        printf("    %10s    %10s\n", autos[i].patente, marcas[i].descripcion);
    }
    printf("\n\n");
}
void listarMarcas(eMarca marcas[], int tammarca){

    system("cls");
    printf("\n****Listado de Marcas****\n");
    printf("    Id        Marca\n\n");

    for(int i=0; i < tammarca; i++)
    {
        printf("    %d    %10s\n", marcas[i].id, marcas[i].descripcion);
    }
    printf("\n\n");
}
void listarColores(eColor colores[], int tamcolor){

    system("cls");
    printf("\n****Listado de Colores****\n");
    printf("    Id        Color\n\n");

    for(int i=0; i < tamcolor; i++)
    {
        printf("    %d    %10s\n", colores[i].id, colores[i].nombreColor);
    }
    printf("\n\n");
}

void listarServicios(eServicio servicios[], int tamser){

    system("cls");
    printf("\n****Listado de Servicios****\n");
    printf("    Id        Color        Precio\n\n");

    for(int i=0; i < tamser; i++)
    {
        printf("    %d    %10s    %.2f\n", servicios[i].id, servicios[i].descripcion, servicios[i].precio);
    }
    printf("\n\n");
}
int altaTrabajo(int idx, eTrabajo vec[], int tamt, eAuto autos[], int tamauto, eServicio servicios[], int tamser, int tammarca, int tamcolor)
{
    int todoOk = 0;
    int indice = buscarLibreTrabajo(vec, tamt);
    eTrabajo auxTrabajo;

    system("cls");
    printf("***Alta Trabajo***\n\n");

    if(indice == -1) //hay lugar?
    {
        printf("Sistema completo\n\n");
    }
    else
    {
            auxTrabajo.id = idx;

           // mostrarAuto(vec, marcas, tammarca, colores, tamcolor);
            printf("Ingrese el id de un auto: ");
            fflush(stdin);
            scanf("%d", &auxTrabajo.id);

            //mostrarServicios(servicios, tamser);
            printf("Ingrese IdServicio: ");
            fflush(stdin);
            scanf("%d", &auxTrabajo.idServicio);

            vec[indice] = auxTrabajo;//copio al vector del empleado nuevo
            todoOk = 1;
        }

    return todoOk;
}
int buscarLibreTrabajo(eTrabajo vec[], int tamt)
{

    int indice = -1;

    for(int i=0; i < tamt; i++)
    {
        if(vec[i].isEmpty == 1)
        {
            indice = i;
            break;
        }
    }

    return indice;
}
/*void mostrarServicios(eServicio x, int tamser)
{
    char descripcionServicio[20];

    cargarDescripcionServicio(descripcionServicio, servicios[], tamser, idServicio);


    printf("\n   %d   %10s   %.2f\n", x.id, x.descripcion, x.precio);

}
int cargarDescripcionServicio(char descripcionServicio, eServicio servicios[], int tamser, int idServicio)
{

    int todoOk = 0;
    for(int i=0; i < tamser; i++){
        if(servicios[i].id == idServicio){
            strcpy(descripcionServicio, servicios[i].descripcion);
            todoOk = 1;
        }
    }
    return todoOk;
}*/
