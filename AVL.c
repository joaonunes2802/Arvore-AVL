#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    int conteudo;
    struct no *pai;
    struct no *filhoEsq;
    struct no *filhoDir;
}elemento;

void inserir(elemento *raiz, int dado){
    elemento *p = NULL, *q = NULL;
    int aux = 0;
    p = raiz;
    do{
        if(dado > p->conteudo && p->filhoDir == NULL){
            q = (elemento *)malloc(sizeof(elemento));
            q->conteudo = dado;
            q->filhoDir = NULL;
            q->filhoEsq = NULL;
            q->pai = p;
            p->filhoDir = q;
            aux = 1;
        }else if (dado < p->conteudo && p->filhoEsq == NULL){
            q = (elemento *)malloc(sizeof(elemento));
            q->conteudo = dado;
            q->filhoDir = NULL;
            q->filhoEsq = NULL;
            q->pai = p;
            p->filhoEsq = q;
            aux = 1;
        }else if(dado > p->conteudo && p->filhoDir != NULL){
            inserir(p->filhoDir, dado);
            aux = 1;
        }else if(dado < p->conteudo && p->filhoEsq != NULL){
            inserir(p->filhoEsq, dado);
            aux = 1;
        }
    }while(aux != 1);
}
void inserElemento();
int calculAltura(); 
void rotDir();
void rotEsq();

int main(){
    return 0;
}