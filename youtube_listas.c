#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct tProduto{
    int codigo; //chave ordenacao
    char descricao[30];
};

struct tNo{
    struct tProduto dado;
    struct tNo *prox;
};


struct tDescritor{
    struct tNo *ini;
    struct tNo *fim;
    int qtd;
};


void incluir(struct tNo **lst,struct tNo *novo){
    if (*lst == NULL ){ // lista vazia
        novo->prox == NULL;
        *lst = novo;
    }else{

    }
}

int menu(void){
    int op;
    printf("\n\n*** MENU *** \n\n");
    printf("1. Inclusao\n");
    printf("2. Consulta\n");
    scanf("%d", &op);
    return op;


}



int main(){
    struct  tNo *lista, *p; 
    int opcao;
    do{
        opcao = menu();
        switch (opcao)
        {
        case 1:
            printf("\n\n\***Inclusao***\n\n");
             p = malloc(sizeof(struct tNo));
             printf("digite o codigo\n");
             scanf("%d", &(p->dado.codigo));
             printf("Digite a descrição:\n ");
             scanf("%s", p->dado.descricao);
             incluir(&lista, p);
            printf("Meu produto tem o codigo %d e a descrição %s\n", p->dado.codigo, p->dado.descricao);
            break;
        
       
        }
    }while(opcao != 0);
    


    return 0;
}


