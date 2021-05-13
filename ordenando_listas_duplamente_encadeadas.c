#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct cel_ {
    int conteudo;
    struct cel_ *seg;
    struct cel_ *ant;
};
typedef struct cel_ celula;

int tamanho, resultado,valor_buscado, n=6;/** n Define aqui o tamanho da lista**/
double tempo_ordenacao, tempo_execucao;
clock_t start,t;
char nome_busca[100];
celula *lst;

/**FUNÇOES**/
celula *InserirLista (celula *lst, int n);
void ImprimeLista (celula *lst);
//void OrdenacaoInsercao (celula *lst);
int numerosSorteados[100];


int main() {
    
    celula * lst_numeros_sorteados;
    celula *fim;
    celula *p,*k;
    celula c, r;
    clock_t start, end;
    double cpu_time_used;
    int i; 

    tamanho += sizeof(celula)*n;

    lst = &c;
    fim = &r;
    lst_numeros_sorteados = &c;
    lst->seg = fim;
    lst->ant = NULL;
    lst_numeros_sorteados->seg = fim;
    lst_numeros_sorteados->ant = NULL;
    fim->seg = NULL;
    p = lst;
    k = lst_numeros_sorteados;
    srand(time(NULL));

    /**Inserindo elementos na lista**/
    for(i = 1; i <= n; i++)
        p = InserirLista(p, rand()%5);

    sortearNumerosTestarALgoritmos(numerosSorteados, 0, 1024);
    
    //mostrando na tela os numeros sorteados
    /*for (int i = 0; i < 100; i++)
    {
        printf("sorteado valor %i\n", numerosSorteados[i]);
    }*/    

     //GRAVANDO EM ARQUIVO
    FILE *arquivo;
    arquivo = fopen("tabela_listas.csv", "w");
    if(arquivo == NULL)
    {
        printf("Não foi possível abrir o arquivo\n");
        getchar();
        exit(1);
    }
   // exibirVetor(vetorOrdenar, TAM);
    fprintf(arquivo,"Busca;Posicao;Valor_Pesquisado;Tempo_Execucao;Tempo_Ordenar_Vetor\n");
  /*
    //realizando busca sequencial dos numeros sorteados
    for(i = 0; i < 100; i++){   
        valor_buscado = numerosSorteados[i];
        start = clock();    
        t = clock() - start;
        resultado = buscaSequencial(lst,numerosSorteados[i]);
        tempo_execucao = (double)t / (CLOCKS_PER_SEC/1000);//conversão para double  
        fprintf(arquivo, "%s; %i; %i; %lf; %i\n",nome_busca,resultado,valor_buscado,tempo_execucao,0);
    }*/
    
    //ordenando vetor e guardando tempo de ordenação
    start = clock();    
    t = clock() - start;
    OrdenacaoInsercao(lst);
    tempo_ordenacao = (double)t / (CLOCKS_PER_SEC/1000);//conversão para double      
    printf("\n\n\n");    
    printf("Tempo ordenação %lf\n", tempo_ordenacao);
    
    //realizando busca binaria dos numeros sorteados
    for(i = 0; i < 3; i++){   
        valor_buscado = numerosSorteados[i];
        //start = clock();    
       // t = clock() - start;
        resultado = buscaBinaria(5);   
        printf("valor= %i\n",resultado);     
       // tempo_execucao = (double)t / (CLOCKS_PER_SEC/1000);//conversão para double  
        fprintf(arquivo, "%s; %i; %i; %lf; %i\n",nome_busca,resultado,valor_buscado,tempo_execucao,tempo_ordenacao);
       
        
}
   ImprimeLista(lst);
    return 0;
}

celula *InserirLista (celula *p, int x) {
    celula * nova;
    nova = (celula*)malloc(sizeof(celula));
    nova->conteudo = x;
    nova->seg = p->seg;
    nova->ant = p;
    p->seg->ant = nova;
    p->seg = nova;
    return p;
}

void ImprimeLista (celula *lst) {
    celula *p = lst->seg;
    int cont = 0;
    while (p->seg != NULL){
        printf("posicao %i %d ",cont, p->conteudo);
        p = p->seg;
        cont++;
    }
}

void OrdenacaoInsercao (celula *lst) {
    celula *p = lst->seg->seg;
    celula *q;
    int x;
   
    while (p->seg != NULL) {
        q = p->ant;
        x = p->conteudo;

        while ((q != lst) && (q->conteudo > x)) {
            q->seg->conteudo =  q->conteudo;
            q = q->ant;
        }
        q->seg->conteudo = x;
        p = p->seg;
    }
}

int buscaSequencial(celula *lst, int valor){
    //Elemento *atual;
	//atual = inicio;
    int cont = 0;
    strcpy(nome_busca, "buscaSequencial");
    while (lst != NULL){
       
        if (lst->conteudo == valor)
      		return cont;
		 	lst = lst->seg;
            cont++;
}
	return -1;
}

void sortearNumerosTestarALgoritmos(int vetor[],int menor, int maior){

     for(int i = 0; i < 100; i++)
    {
       vetor[i] = rand() % maior + menor;
       //printf("Numero sorteado é [%d] : %d \n",i, vetor[i]);
    }
}

