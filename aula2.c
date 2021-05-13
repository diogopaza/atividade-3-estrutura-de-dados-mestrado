#include <stdio.h> 
#include <malloc.h>
#define alturaMaxima  225

typedef struct
{
   int peso;
   int altura;
} PesoAltura;

main(){

//PesoAltura pessoa1;
PesoAltura* pessoa1 = (PesoAltura*) malloc(sizeof(PesoAltura));
pessoa1->peso = 80;
pessoa1->altura = 185;
printf("Peso: %i, Altura %i ", pessoa1->peso, pessoa1->altura);

if(pessoa1->altura>alturaMaxima) printf("Altura acima da maxima.\n");
if(pessoa1->altura<alturaMaxima) printf("Altura abaixo da maxima.\n");


return 0;

/*
int* y = (int*) malloc(sizeof(int));
*y = 20;
int z = sizeof(int);
printf("*y=%i z=%i\n", *y, z);

return 0;
*/



}