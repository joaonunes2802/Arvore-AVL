#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    int conteudo;
    struct no *filhoEsq;
    struct no *filhoDir;
}elemento;

void inserir(elemento **raiz, int dado){
    if(*raiz == NULL){
        *raiz = (elemento *) malloc(sizeof(elemento));
        (*raiz)->conteudo = dado;
        (*raiz)->filhoDir = NULL;
        (*raiz)->filhoEsq = NULL;
    }else if(dado > (*raiz)->conteudo){
        inserir(&((*raiz)->filhoDir), dado);
    }else if(dado <= (*raiz)->conteudo){
        inserir(&((*raiz)->filhoEsq), dado);
    }
}
int calculAlturaEsq(elemento *raiz){
    elemento *p;
    p = raiz->filhoEsq;
    if(p == NULL){
        return -1;
    }else{
        int esq = calculAlturaEsq(p->filhoEsq);
        int dir = calculAlturaEsq(p->filhoDir);
        if(esq > dir){
            return esq + 1;
        }else{
            return dir + 1;
        }
    }
}

int calculAlturaDir(elemento *raiz){
    elemento *p;
    p = raiz->filhoDir;
    if (p == NULL){
        return -1;
    }else{
        int esq = calculAlturaEsq(p->filhoEsq);
        int dir = calculAlturaEsq(p->filhoDir);
        if (esq > dir){
            return esq + 1;
        }else{
            return dir + 1;
        }
    }
}

void rotDir(elemento *no){
    elemento *p = NULL, *aux = NULL;
    p = no->filhoEsq;
    aux = p->filhoDir;
    p->filhoDir = no;
    no->filhoEsq = aux;
    no = p;
}

void rotEsq(elemento *no){
    elemento *p =   NULL, *aux = NULL;
    p = no->filhoDir;
    aux = p->filhoEsq;
    p->filhoEsq = no;
    no->filhoDir = aux;
    no = p;
}


int main(){
    return 0;
}