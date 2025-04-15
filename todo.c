#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int TareaID;
    char *Descripcion;
    int duracion;

} Tarea;

typedef struct Nodo
{
    Tarea T;
    struct Nodo *siguiente;
} Nodo;

int idAleatorio = 1000;

void ListarTareas(Nodo **nodo)
{

    while (*nodo != NULL)
    {
        printf("ID: %d, Descripcion: %s, Duracion: %d\n", (*nodo)->T.TareaID, (*nodo)->T.Descripcion, (*nodo)->T.duracion);
        nodo = &(*nodo)->siguiente;
    }
}

Nodo *CrearListaVacia()
{
    return NULL;
}

Nodo *CrearNodo(Tarea t)
{

    Nodo *nodo = (Nodo *)malloc(sizeof(Nodo));
    nodo->T = t;
    nodo->siguiente = NULL;
    return nodo;
}
void InsertarNodo(Nodo **start, Nodo *nodo)
{
    nodo->siguiente = *start;
    *start = nodo;
}

Nodo *BuscarNodo(Nodo **start, int dato)
{
    Nodo *aux = *start;
    while (aux && aux->T.TareaID != dato)
    {
        aux = aux->siguiente;
    }
    return aux;
}
Nodo *QuitarNodo(Nodo **start, int id)
{
    Nodo **aux = start;
    while (*aux != NULL && (*aux)->T.TareaID != id)
    {
        aux = &(*aux)->siguiente;
    }

    if (*aux)
    {
        Nodo *temp = *aux;
        *aux = (*aux)->siguiente;
        temp->siguiente = NULL;
        return temp;
    }
    return NULL;
}
Nodo *EliminarNodo(Nodo *nodo)
{
    free(nodo);
}

main()
{

    // lista de tareas pendientes
    Nodo *listaTareaPendiente = CrearListaVacia();
    // lista de tareas realizadas
    Nodo *listaTareaRealizada = CrearListaVacia();

    // carga de tareas pendientes

    int opcion = 0;

    printf("Carga de tareas pendientes\n");
    do
    {
        Tarea t;
        t.TareaID = idAleatorio++;
        printf("Ingrese la descripcion de la tarea: ");
        t.Descripcion = malloc(sizeof(char) * 50);
        gets(t.Descripcion);
        printf("Ingrese la duracion de la tarea: ");
        // la duracion debe estar entre 10 y 100
        do
        {
            scanf("%d", &t.duracion);
            if (t.duracion < 10 || t.duracion > 100)
            {
                printf("La duracion debe estar entre 10 y 100\n");
            }
        } while (t.duracion < 10 || t.duracion > 100);
        Nodo *nodo = CrearNodo(t);
        InsertarNodo(&listaTareaPendiente, nodo);

        printf("Desea ingresar otra tarea? (1 para si, 0 para no): ");
        scanf("%d", &opcion);
    } while (opcion == 1);

    ListarTareas(&listaTareaPendiente);

    printf("Cambio de tareas pendientes a realizadas\n");
    // mostrar las tareas pendientes disponibles con su id
    // Nodo *aux = listaTareaPendiente;
    // printf("Tareas pendientes:\n");
    // ListarTareas(&aux);

    int id;
    int seguir = 0;

    do
    {
        printf("Ingrese el ID de la tarea que desea marcar como realizada: ");
        scanf("%d", &id);

        Nodo *tareaAMover = QuitarNodo(&listaTareaPendiente, id);
        if (tareaAMover)
        {
            InsertarNodo(&listaTareaRealizada, tareaAMover);
            printf("Tarea %d transferida a realizadas.\n", id);
        }
        else
        {
            printf("No se encontró la tarea con ID %d.\n", id);
        }

        printf("¿Desea transferir otra tarea? (1: si, 0: no): ");
        scanf("%d", &seguir);

    } while (seguir == 1);

    printf("quedan Tareas pendientes:\n");
    ListarTareas(&listaTareaPendiente);

    printf("quedan Tareas realizadas:\n");
    ListarTareas(&listaTareaRealizada);

    return 0;
}
