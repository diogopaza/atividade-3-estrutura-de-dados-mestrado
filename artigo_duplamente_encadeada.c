#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct No{
    int num;
    struct No *prox;
    struct No *ant;
};
typedef struct No No;
char nome_busca[30];
int tamanho=32768,resultado,posicao=0;
int numerosSorteados[100], *vetorPreenchido;
FILE *arquivo, *arquivo2;
double tempo_execucao,tempo_criacao_lista,tempo_criacao_lista_ordenada,
tempo_execucao_busca_binaria,tempo_execucao_busca_sequencial;
clock_t start,t,start_inicio_binaria,start_inicio_sequencial; //variável para armazenar tempo
int busca_Binaria = 0;
int *ponteiro;

*ponteiro = &busca_Binaria;

/*registro do tipo Lista contento dois ponteiros do tipo nó para controlar a lista*/
struct Lista{
    struct No *inicio; /*aponta para o elemento do início da lista*/
    struct No *fim; /*aponta para o elemento do fim da lista*/
};
typedef struct Lista Lista;

/*necessitaremos também de três ponteiros auxilares *aux , *aux2 e *anterior */
No *aux;
No *aux2;
No *anterior;
No *p;

Lista* cria_lista(){
    /*alocação do ponteiro li para controlar a lista*/
    Lista* li = (Lista*) malloc(sizeof(Lista));
    if(li != NULL){
        /*Se a lista está inicialmente vazia, inicio e fim apontam para NULL */
        li->fim = NULL;
        li->inicio = NULL;
    }
    return li;
}	

void insereListaOrdenada(Lista *li, int valor){
    No *novo =(No*) malloc(sizeof(No)); /*a cada inserção alocamos dinamicamente um espaço para um novo nó*/
    novo->num = valor;
	
    if(li->inicio == NULL){ /*caso a lista estiver vazia o elemento a ser inserido será o primeiro e último elemento da lista*/
        /*como será o único elemento da lista, novo->prox e novo->ant apontam para null*/
        novo->prox = NULL;
        novo->ant = NULL;
        li->inicio = novo; /*aqui fazemos com que inicio aponte para o mesmo endereço que novo aponta*/
        li->fim = novo; /*aqui fazemos com que fim aponte para o mesmo endereço que novo aponta*/
    }else{ /*caso a lista não esteja vazia*/
        aux = li->inicio; /*aux aponta para o endereço que inicio aponta*/
        /*enquanto ainda houverem elementos na lista e o novo número for maior que aux->num,
         ou seja enquanto não for encontrado um número maior que o número inserido*/
        while(aux != NULL && novo->num > aux->num){
            aux = aux->prox; /*aux aponta para o próximo elemento da lista*/
             /*isso é feito para encontrar o ponto exato para o número ser inserido*/
        }
        /*caso não existam números maiores ou iguais ao novo número , ele será inserido no início da lista*/
        if(aux == li->inicio){
            novo->prox = li->inicio; /*novo->prox apontara para o atual inicio, que depois será o segundo elemento*/
            novo->ant = NULL; /*como novo será o primeiro da lista, seu ponteiro ant deverá apontar para null*/
            li->inicio->ant = novo; /*o inicio atual(que depois será o segunda da lista) em ant, apontara para o endereço de novo*/
            li->inicio = novo; /*inicio aponta para novo*/
        /*caso todos elementos da lista sejam menores que o número a ser inserido, ele será inserido no fim*/
        }else if(aux == NULL){
            li->fim->prox = novo; /*o fim atual (que depois será o penultimo da lista) em prox, apontará para novo*/
            novo->ant = li->fim; /*novo -> ant aponta para o endereço do fim atual.*/
            li->fim = novo; /*fim aponta para novo*/
            li->fim->prox = NULL; /*todo ultimo elemento da lista  em prox aponta para null*/
        }else{  /*caso novo seja inserido no meio da lista, ele será inserido antes de aux*/
            novo->prox = aux; /*novo será inserido antes do aux atual, então novo->prox aponta para o aux atual*/
            aux->ant->prox = novo; /*o número que estava antes de aux em prox aponta para novo*/
            novo->ant = aux->ant; /*novo-> ant aponta para o nó anterior a aux atual*/
            aux->ant = novo; /*aux atual será o elemento seguinte a novo, portanto em ant apontará para novo*/
        }
    }
}		

void imprime_lista_inicio_ao_fim(Lista *li){
    /*caso a lista esteja vazia*/
    if( li->inicio == NULL){
        printf("\nLista Vazia!!");
    /*caso a lista não esteja vazia*/
    }else{
        /*utilizando o ponteiro aux,  fazemos com ele aponte para o mesmo endereço que inicio aponta*/
        aux =  li->inicio;
        do{
            /*impressão do elemento que aux aponta*/
            printf(" %d ", aux->num);
            /*aux aponta para o próximo elemento da lista, que será o endereço contido no ponteiro prox.*/
            aux = aux->prox;
            /*essa operação será feita até aux ser diferente de NULL, ou seja, não houverem mais elementos
             a serem impressos*/
        }while(aux != NULL);
    }
}

int buscaSequencial(int valor, Lista *li){
	strcpy(nome_busca, "Sequencial");
    aux =  li->inicio;
    int posicao =0;
    while (aux != NULL){
       // printf("Valor: %i\n", atual->valor);
        if (aux->num == valor)
      		return posicao;
		 	aux = aux->prox;
            posicao++;
    }
	return -1;
}

int buscaBinaria(int valor, Lista *li)
{
	strcpy(nome_busca, "Binaria");
	p =  li->inicio;
    busca_Binaria = 0;
   	if (aux == NULL) 
    return NULL;
  	int count;     
    while (p != NULL && p->num != valor) {
        p = p->prox;
        busca_Binaria++;
        if(count++ == tamanho/2){
            if (p->prox->num == valor)                 
                return p->prox;                                            
			else{
                if(p->prox->num > valor){
					return -1;
                }else{
					return -1;
                }
            }
        }
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
    arquivo = fopen("tabela_listas_.csv", "w");
    if(arquivo == NULL)
    {
        printf("Não foi possível abrir o arquivo\n");
        getchar();
        exit(1);
    }
    arquivo2 = fopen("tempo_total_buscas.csv", "a");
    if(arquivo == NULL)
    {
        printf("Não foi possível abrir o arquivo\n");
        getchar();
        exit(1);
    }
}

void preencheVetor(int menor, int maior,int tamanho){
    
    for(int i=0 ;i<tamanho ; i++){
        int k;
        k = (rand() % maior) + menor;
        vetorPreenchido[i] = k;        
    }
}

void insereFimLista(Lista *li, int valor){
    /*a cada inserção alocamos dinamicamente um espaço para um novo nó*/
    No *novo =(No*) malloc(sizeof(No));
    novo->num = valor;
    /*caso a lista estiver vazia o primeiro elemento a ser inserido será o primeiro e último elemento da lista*/
    if( li->inicio == NULL){
        li->inicio = novo; /*aqui fazemos com que inicio aponte para o mesmo endereço que novo aponta*/
        li->fim = novo; /*aqui fazemos com que fim aponte para o mesmo endereço que novo aponta*/
        /*como será o único elemento da lista, novo->prox e novo->ant apontam para null*/
        novo->prox = NULL;
        novo->ant = NULL;
    }else{
        /*fim no atributo prox recebe o endereço de novo, aqui ainda fim não foi alterado, portanto essa linha é necessária para
        quando esse elemento vier a ser o penultimo da lista possa apontar para o novo elemento que se tonará o novo fim*/
        li->fim->prox = novo;
        /*como a inserção é no fim, o novo nó inserido receberá no atributo ant(seu ponteiro que aponta para o nó anterior) o
           atual endereço que fim aponta*/
        novo->ant =  li->fim;
        /*como será o ultimo elemento da lista, novo no atributo prox apontará para null*/
        novo->prox = NULL;
        /*fim aponta para o novo nó inserido*/
        li->fim = novo;
    }
    
}

void preencheListas(Lista *li, Lista *ordenada){

    start = clock();  
    //lista destinada a busca padrão sequencial sem ordenação
    for (int i = 0; i < tamanho; i++)
    {   
        insereFimLista(li, vetorPreenchido[i]);
    }
    t = clock() - start;
    tempo_criacao_lista = (double)t / (CLOCKS_PER_SEC/1000);//conversão para double 

      
    start = clock();  
    //lista destinada a busca binária com ordenação
    for (int i = 0; i < tamanho; i++)
    {   
        insereListaOrdenada(ordenada, vetorPreenchido[i]);
    }
    t = clock() - start;
    tempo_criacao_lista_ordenada = (double)t / (CLOCKS_PER_SEC/1000);//conversão para double


}


int main(){
   
    vetorPreenchido = malloc(tamanho * sizeof(int));    
    
    Lista *li = cria_lista();
    Lista *liOrdenada = cria_lista();
    preencheVetor(0,32000,tamanho);
    start = clock();   
    preencheListas(li, liOrdenada);
   

    sortearNumerosTestarALgoritmos(numerosSorteados, 0,8000);
    criarArquivoCsv();

	fprintf(arquivo,"Busca;Posicao;Valor_Pesquisado;Tempo_Execucao;Tempo_Insercao_Lista;Tamanho_Vetor\n");
  
    //executando busca binaria
    start_inicio_binaria = clock();  
    for(int i = 0; i < 100; i++){  
        start = clock();          
        int valor_buscado = numerosSorteados[i];
        int posicaoBinaria = buscaBinaria(valor_buscado, liOrdenada); 
        t = clock() - start;
        tempo_execucao = (double)t / (CLOCKS_PER_SEC/1000);//conversão para double 
        if( posicaoBinaria != valor_buscado){
             fprintf(arquivo, "%s; %i; %i; %lf; %lf; %i\n",nome_busca,-1,valor_buscado,tempo_execucao,tempo_criacao_lista_ordenada,tamanho);
        }else{
             fprintf(arquivo, "%s; %i; %i; %lf; %lf; %i\n",nome_busca,busca_Binaria,valor_buscado,tempo_execucao,tempo_criacao_lista_ordenada,tamanho);
        }         
    } 
    t = clock() - start_inicio_binaria;
    tempo_execucao_busca_binaria = (double)t / (CLOCKS_PER_SEC/1000);//conversão para double;
   
   
    //executando busca sequencial
    start_inicio_sequencial = clock();  
    for(int i = 0; i < 100; i++){   
        start = clock();   
        int valor_buscado = numerosSorteados[i];
        resultado = buscaSequencial(valor_buscado, li); 
        t = clock() - start;
        tempo_execucao = (double)t / (CLOCKS_PER_SEC/1000);//conversão para double 
        fprintf(arquivo, "%s; %i; %i; %lf; %lf; %i\n",nome_busca,resultado,valor_buscado,tempo_execucao,tempo_criacao_lista,tamanho);
    }  
    t = clock() - start_inicio_sequencial;
    tempo_execucao_busca_sequencial = (double)t / (CLOCKS_PER_SEC/1000);//conversão para double;
    fprintf(arquivo2,"%lf; %lf %i\n", tempo_execucao_busca_sequencial,tempo_execucao_busca_binaria,tamanho);
    
    printf("Busca executada\n");
    imprime_lista_inicio_ao_fim(liOrdenada);
    free(li);
    free(liOrdenada);
    return 0;
}