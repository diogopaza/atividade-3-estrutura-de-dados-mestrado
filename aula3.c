#include <stdio.h> 
#include <malloc.h>
#define MAX 50

typedef int TIPOCHAVE;

typedef struct
{
    REGISTRO A[MAX];
    int nroElem;
} LISTA;
    

typedef struct 
{
    TIPOCHAVE chave;

} REGISTRO;

void inicializarLista(LISTA* l){
        l->nroElem = 0;
    }

main(){

    

    return 0;

}