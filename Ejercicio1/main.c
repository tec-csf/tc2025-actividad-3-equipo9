/*
 *  Tarea 3
 *  Programación avanzada
 * 
 *  Equipo 9
 *  Daniel Roa
 *  Miguel Monterrubio 
 * 
 *  IMPORTANTE:
 *  ESTE CÓDIGO FUE ELABORADO CON EL APOYO DE SERGIO HERNÁNDEZ, DEBIDO A QUE IGUAL LE TOCÓ
 *  TRABAJAR EN ESTE MISMO EJERCICIO.
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int procMando;
    int childId;
    int execTime;
}theChild;

typedef struct helper
{
    theChild * babyYoda;
    struct helper * forward;
}helper_t;

helper_t * head = NULL;
int procAmount = 0;

void enqueue(int childId, int procMando, int execTime)
{
    helper_t *current = head;

    if (procAmount == 0)
    {         
        theChild * vL = (theChild*)malloc(sizeof(theChild));
        vL->childId = childId;
        vL->procMando = procMando;
        vL->execTime = execTime;

        head->babyYoda = vL;
    }
    else{ 
        while (current->forward != NULL){
            current = current->forward;
        }

        current->forward = malloc(sizeof(helper_t));
        
        theChild *vL = (theChild *)malloc(sizeof(theChild));
        vL->childId = childId;
        vL->procMando = procMando;
        vL->execTime = execTime;

        current->forward->babyYoda = vL;
        current->forward->forward = NULL;
    }
    ++procAmount;
}

helper_t * dequeue(){
    helper_t * returningValue;

    if (procAmount == 1){
        returningValue = head->babyYoda;
    }
    else{

        helper_t *nextProc = head->forward;
        returningValue = head->babyYoda;
        free(head->babyYoda);
        free(head);
        head = nextProc;
    }
    --procAmount;
    return returningValue;
}

int main(int argc, char const *argv[]){
    
    head = malloc(sizeof(helper_t));
    head->forward = NULL; 

    //Variables donde se encuentran las cantidades ingresadas
    int cpu = 0, \
    cantProc = 0, \
    cantSub = 0, \
    execTimeIn = 0;
    
    //Varbiables para realizar contadores
    int contProc = 0,\
    contSub = 0,\
    cont = 0;

    printf("\nIngrese la cantidad de procesos que se van a crear: ");
    scanf("%d", &cantProc);

    printf("\nIngrese la cantidad de CPUs que va a utilizar: ");
    scanf("%d", &cpu);

    theChild * yodas = (theChild*) malloc(sizeof(theChild) * cantProc);
    theChild * fin = yodas + cantProc;

    printf("Inserta los datos que se soliciten a continuación:\n");

    theChild * auxilio = yodas;

    while (cont != cantProc){

        printf("Escriba la cantidad de subprocesos que va a tener el proceso: %d\n", cont);
        scanf("%d", &cantSub);

        if(contSub < cantSub){
            for (; contSub < cantSub; contSub++){
                
                auxilio->procMando = cont;
                auxilio->childId = contSub;

                printf("\nEscriba el tiempo de ejecución: ");
                scanf("%d", &execTimeIn);

                auxilio->execTime = execTimeIn;

                printf("Proceso padre #%d\n", auxilio->procMando);
                printf("Proceso hijo #%d\n", auxilio->childId);
                printf("Tiempo de ejecución: %d\n", auxilio->execTime);
            }
            

            printf("\nProceso hijo por comenzar a manejar: %d\n\n", contSub);
        }
        cont+=1;
        contSub = 0;
        cantSub = 0;
    }

    for (theChild * support = 0; support < fin; ++support)
    {
        printf("Mando process: %d\tChild process: %d\tExec time: %d", support->procMando, support->childId, support->execTime);
    }
    

    return 0;
}
