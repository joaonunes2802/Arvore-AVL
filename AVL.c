#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    int conteudo;
    struct no *pai;
    struct no *filhoEsq;
    struct no *filhoDir;
}elementoAr;

void criArvore();
void inserElemento();
int calculAltura(); 
void rotDir();
void rotEsq();

int main(){
    return 0;
}