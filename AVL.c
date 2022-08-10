#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    int conteudo;
    struct no *pai;
    struct no *filhoEsq;
    struct no *filhoDir;
}elemento;

void inserir(elemento *raiz, int dado){
    elemento *p, *q, *r;
    int i;
    p = raiz;
    if(dado > p->conteudo && p->filhoDir == NULL){
        q = (elemento *)malloc(sizeof(elemento));
        q->conteudo = dado;
        q->filhoDir = NULL;
        q->filhoEsq = NULL;
        q->pai = p;
        p->filhoDir = q;
    }else if (dado < p->conteudo && p->filhoEsq == NULL){
        q = (elemento *)malloc(sizeof(elemento));
        q->conteudo = dado;
        q->filhoDir = NULL;
        q->filhoEsq = NULL;
        q->pai = p;
        p->filhoEsq = q;
    }else if(dado > p->conteudo && p->filhoDir != NULL){
        inserir(p->filhoDir, dado);
    }else if(dado < p->conteudo && p->filhoEsq != NULL){
        inserir(p->filhoEsq, dado);
    }
}
void inserElemento();
int calculAltura(); 
void rotDir();
void rotEsq();

int main(){
    return 0;
}