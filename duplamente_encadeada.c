#include <stdio.h>
#include <stdlib.h>
#include <time.h>



typedef struct elemento Elemento;
struct elemento {
	int valor;
	Elemento *proximo;
	Elemento *anterior;
};
//Criar 2 variáveis globais.
Elemento *inicio;
Elemento *fim;
int tamanho;
int TAM=1024;
int valor_buscado, resultado; 
char nome_busca[100];
clock_t start,t; //variável para armazenar tempo
double tempo_ordenacao,tempo_execucao;
int numerosSorteados[100];
FILE *arquivo;


// Criando prototipos de função
void criaLista();
Elemento *aloca(int valor);
void insereInicio(int valor);
void insereFim(int valor);
void inserePosicao(int valor, int posicao);
void removeInicio();
void removeFim();
void imprimeLista();
void imprimeListaContrario();

//Criar 2 elemmentos nulos na lista.
void criaLista() {
	inicio = NULL;
	fim = NULL;
	tamanho = 0;
}
//Alocar um dado, e como funciona o esquema do lista duplamente encadeada:
Elemento *aloca(int valor) {
	Elemento *novo = (Elemento*)malloc(sizeof(Elemento));
	novo->valor = valor;
	novo->anterior = NULL;
	novo->proximo = NULL;
	return novo;
}

Elemento *criarElemento() {
	Elemento *novo = (Elemento*)malloc(sizeof(Elemento));
	novo->anterior = NULL;
	novo->proximo = NULL;
	return novo;
}

void removeInicio() {
	Elemento *atual = inicio;
	inicio = atual->proximo;
	inicio->anterior = NULL;
	tamanho--;
}
void removeFim() {
	Elemento *atual = fim;
	fim = atual->anterior;
	fim->proximo = NULL;
	tamanho--;
}

//Inserir no inicio da lista:
void insereInicio(int valor) {
	Elemento *novo = aloca(valor);   //criar novo elemento
	//verificar se o inicio for nulo, se sim, inicio recebe novo e o fim vai ser novo também, pois se os dois são nulos o inico e fim recebe o novo.
	if(inicio==NULL){
		inicio=novo;
		fim=novo;

	//Se a lista já tiver dado se cria outro elemento e aponta o ant para o dado 2 e prox do dado 2 para o 1.
	}else{
		Elemento *atual; //criar novo elemento caso tenha dado no inicio da lista.
		atual = inicio;
		novo->proximo = atual;
		atual->anterior = novo;
		inicio = novo;
	}
	tamanho++;
}

//Inserir no fim da lista:
void insereFim(int valor) {
	Elemento *novo = aloca(valor);   //criar novo elemento
	//verificar se o inicio for nulo, se sim, inicio recebe novo e o fim vai ser novo também, pois se os dois são nulos o inico e fim recebe o novo.
	if(inicio==NULL){
		inicio=novo;
		fim=novo;
	//Se a lista já tiver dado se cria outro elemento e aponta o ant para o dado 2 e prox do dado 2 para o 1.
	}else{
		Elemento *atual; //criar novo elemento caso tenha dado no inicio da lista.
		atual = fim;
		novo->anterior = atual;
		atual->proximo = novo;
		fim = novo;
	}
	tamanho++;
}

//Inserir no inicio da lista:
void inserePosicao(int valor, int posicao) {
	posicao = posicao-1;
	Elemento *novo = aloca(valor);   //criar novo elemento
	//verificar se o inicio for nulo, se sim, inicio recebe novo e o fim vai ser novo também, pois se os dois são nulos o inico e fim recebe o novo.
	if(inicio==NULL){
		inicio=novo;
		fim=novo;
	//Se a lista já tiver dado se cria outro elemento e aponta o ant para o dado 2 e prox do dado 2 para o 1.
	}else{
		Elemento *atual; //criar novo elemento caso tenha dado no inicio da lista.
		Elemento *tmp;
		int i;

		// Decidindo o ponto de incio
		if (posicao < (tamanho/2)) {
			atual = inicio;
			i = 0;
		} else {
			atual = fim;
			i = tamanho;
		}

		// Percorrer para encontrar a posição
		while ((i != posicao) && (i >= 0) && (i <= tamanho)) {
			if (i < posicao) {
				i++;
				atual = atual->proximo;
			} else if (i > posicao) {
				i--;
				atual = atual->anterior;
			}

			if (posicao == i) {
				// novo->anterior = 
				// novo->proximo =
				// atual = novo;
				printf("Valor antecessor ao quero inserir %d\n", atual->anterior->valor);
				printf("Valor proximo ao quero inserir %d\n", atual->proximo->valor);
			}
		}



	}
	// tamanho++;
}

//Função para imprimir a lista:
void imprimeLista() {
	Elemento *atual;
	atual = inicio;
		
	while(atual){
		printf("lista: %d\n",atual->valor);
		atual=atual->proximo;
	}
}

//Função para imprimir a lista:
void imprimeListaContrario() {
	Elemento *atual;
	atual = fim;
	while(atual){
		printf("lista: %d\n",atual->valor);
		atual=atual->anterior;
	}
}

void preencheLista(int menor, int maior,int TAM){
   
    for(int i=0 ;i<TAM ; i++){
        int k;
        k = (rand() % maior) + menor;
        insereInicio(k);
    }
}

int buscaSequencial(int valor){
	 strcpy(nome_busca, "Sequencial");
    Elemento *atual;
	atual = inicio;
    while (atual != NULL){
       // printf("Valor: %i\n", atual->valor);
        if (atual->valor == valor)
      		return valor;
		 	atual = atual->proximo;
}
	return -1;
}


int quantidadeElementos(){
	Elemento *atual;
	atual = inicio;
	int qtde = 0;
	while (atual != NULL){
        atual = atual->proximo;
		qtde++;
}
	return qtde;

}

int buscaBinaria(int x)
{
	strcpy(nome_busca, "Binaria");
	Elemento *atual;
	atual = inicio;

   	if (atual == NULL) 
    return NULL;
  	Elemento *p = atual;
   	int count = 0;
  	 while (p != NULL && p->valor != x) {
		  p = p->proximo;		
		 		
        if(count++ == tamanho/2){
			  if (p->proximo->valor == x){
				return p->proximo;
			}               
            else{
                if(p->proximo->valor > x){
					return -1;
                }else{
					return -1;
                }
            }
        }
   }
}

void selectsort(Elemento *p) {
     Elemento *i, *j, *aux;
     aux = (Elemento *)malloc (sizeof (Elemento));
     i = p;
     while( i != NULL) {
            j = i->proximo;
            while (j != NULL) {
                   if (i->valor > j->valor){
                         //  swap dos ponteiros
                         *aux = *i ; // copia valor de i em aux.
                         *i =  *j; // copia valor de j em i.
                         i->proximo = aux->proximo; // altera ponterio do próximo de i para que ele continue sendo o mesmo que era antes da copia
                         aux->proximo = j->proximo; // copia o valor do ponteiro do proximo j
                         *j = *aux; // copia valor de aux em j.
                          j->proximo = aux->proximo; // altera ponterio do próximo de i para que ele continue sendo o mesmo que era antes da copia
                   }
                   j = j->proximo;
            }
      i = i->proximo;
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

int main() {
    srand(time(NULL));	

	criaLista();
	preencheLista(0,2000, TAM);	
	sortearNumerosTestarALgoritmos(numerosSorteados, 0, 500);
	criarArquivoCsv();

	fprintf(arquivo,"Busca;Posicao;Valor_Pesquisado;Tempo_Execucao;Tempo_Ordenar_Vetor;Tamanho_Vetor\n");

    //executando busca sequencial
    /* for(int i = 0; i < 100; i++){   
        valor_buscado = numerosSorteados[i];
        printf("valor buscado %d\n", valor_buscado);
        start = clock();   
		resultado = buscaSequencial(valor_buscado); 
        t = clock() - start;
        tempo_execucao = (double)t / (CLOCKS_PER_SEC/1000);//conversão para double  
        fprintf(arquivo, "%s; %i; %i; %lf; %i; %i\n",nome_busca,resultado,valor_buscado,tempo_execucao,0,TAM);
	 }    
	/*
	//ordenando lista
	Elemento *atual;
	atual = inicio;
	selectsort(atual);*/
	
	
	imprimeLista();
	
}