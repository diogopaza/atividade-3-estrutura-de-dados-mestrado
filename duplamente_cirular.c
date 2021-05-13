#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct No_lista{
    struct No_lista *ant;
    struct No_lista *prox;
    int info;
} No_lista;

typedef No_lista* Lista;
int tamanho = 1024, resultado,valor_buscado;
clock_t start,t; //variável para armazenar tempo
double tempo_ordenacao, tempo_execucao;
int numerosSorteados[100];
FILE *arquivo;
char nome_busca[30];



void adicionar(int parametro, Lista *inicial){
    if(*inicial == 0 ){
        (*inicial) = malloc(sizeof(No_lista));
        //(*inicial)->ant = *inicial;
         (*inicial)->ant = NULL;
        (*inicial)->prox = *inicial;
        (*inicial)->info = parametro;
    }else{
        No_lista *aux, *ultimo;
        aux = *inicial;
        while(aux->prox != *inicial)
            aux = aux->prox;
        aux->prox = malloc(sizeof(No_lista));
        ultimo = aux->prox;
        ultimo->ant = aux;
        ultimo->prox = *inicial;        
        ultimo->info = parametro;
        (*inicial)->ant = ultimo;
       
    }
}

void printLista(Lista *inicial){
    No_lista *aux;
    aux = *inicial;
    printf("Imprimindo lista:\n");
    do{
        printf("%d ", aux->info);
        aux = aux->prox;
    }while(aux != *inicial);
    printf("\n");
}

void ordena(Lista *p_l){ //insertion sort
    No_lista *cur, *ptr, *tmp, *aux, *aux_ant, *aux_prox;
//  if(listaVazia(p_l))
//      return;

    cur = *p_l;
    cur = cur->prox;

    // Tratando para o caso da lista com 2 elementos
    if( cur->prox == *p_l){
        if( (*p_l)->info > cur->info)
            (*p_l) = (*p_l)->prox;
        return;
    }

    while(cur!=*p_l){
        ptr=cur;
        tmp=cur->ant;
        cur=cur->prox;

        while (tmp->prox != *p_l && tmp->info > ptr->info){
            aux_ant = tmp->ant;
            aux_prox = ptr->prox;

            aux_ant->prox = ptr;
            ptr->prox = tmp;
            tmp->prox = aux_prox;
            aux_prox->ant = tmp;
            tmp->ant = ptr;
            ptr->ant = aux_ant;

            tmp = ptr;
            ptr = tmp->prox;

            if(ptr==*p_l)
                *p_l = tmp;

            tmp=tmp->ant;
            ptr = ptr->ant;
        }
    }
}

int buscaBinaria(Lista *p_l, int x)
{   
    strcpy(nome_busca, "Binaria");
	if ((*p_l) == NULL) 
    return NULL;
  	Lista p = *p_l;
   	int count = 0;
  	 while (p != NULL && p->info != x) {
		  printf("while\n"); 
		 p = p->prox;			 		
        if(count++ == tamanho/2){
			 if (p->prox->info == x){
				printf("retornando\n");
				return p->prox;
			}               
            else{
                if(p->prox->info > x){
					return -1;
                }else{
					printf("entrei 2\n");
                    return -1;
                }
            }
        }
   }
}

int buscaSequencial(Lista *p_l, int x){
    
    strcpy(nome_busca, "Sequencial");
    Lista p = *p_l;
    int cont = 0;
    while (cont < tamanho){
       if (p->info == x){
           return x;
        }      		
         p = p->prox;
         cont++;
    }
	return -1;
}

void preencheLista(Lista p_l, int menor, int maior,int TAM){
    //Lista p = *p_l;
    for(int i=0 ;i<tamanho; i++){
        int k;
        k = (rand() % maior) + menor;
       adicionar(k, p_l);
    }
}

void sortearNumerosTestarALgoritmos(int vetor[],int menor, int maior){

     for(int i = 0; i < 100; i++)
    {
       vetor[i] = rand() % maior + menor;
       //printf("Numero sorteado é [%d] : %d \n",i, vetor[i]);
    }
}

void criarArquivoCsv(){
    arquivo = fopen("tabela_listas.csv", "w");
    if(arquivo == NULL)
    {
        printf("Não foi possível abrir o arquivo\n");
        getchar();
        exit(1);
    }
}


int main()
{
    srand(time(NULL));

    Lista *li, p = NULL;
    li = &p;

    preencheLista(li,0,500,tamanho);    
    sortearNumerosTestarALgoritmos(numerosSorteados, 0, 1024);
    criarArquivoCsv();
    
    fprintf(arquivo,"Busca;Posicao;Valor_Pesquisado;Tempo_Execucao;Tempo_Ordenar_Vetor;Tamanho_Vetor\n");

    //executando busca sequencial
     for(int i = 0; i < 100; i++){   
        valor_buscado = numerosSorteados[i];
        printf("valor buscado %d\n", valor_buscado);
        start = clock();    
        t = clock() - start;
        resultado = buscaSequencial(li,numerosSorteados[i]);
        tempo_execucao = (double)t / (CLOCKS_PER_SEC/1000);//conversão para double  
        fprintf(arquivo, "%s; %i; %i; %lf; %i\n",nome_busca,resultado,valor_buscado,tempo_execucao,0,tamanho);
        
     }
/*
    start = clock();
	ordena(li);
	t = clock() - start;
	tempo_ordenacao = (double)t / (CLOCKS_PER_SEC/1000);//conversão para double
	printf("Tempo ordenação %lf\n", tempo_ordenacao);
    printLista(li);
*/
    

    return 0;
}    