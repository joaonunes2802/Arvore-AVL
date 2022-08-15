#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    int conteudo;
    int altura;
    struct no *filhoEsq;
    struct no *filhoDir;
}elemento;

int altura(elemento *p);
void rotDir(elemento **p);
void rotEsq(elemento  **p);
elemento *rotDirEsq(elemento *no);
elemento *rotEsqDir(elemento *no);
int maior(int a, int b);
int altura(elemento *p);
int fb(elemento *p1, elemento *p2);
int fbNULLEsq(elemento *p1);
int fbNULLDir(elemento *p1);
void inserir(elemento **raiz, int dado);
void preOrderBalanceamento(elemento **p);

void rotDir(elemento **p){
elemento *q, *temp;
q = (*p)->filhoEsq;
temp = q->filhoDir;
q->filhoDir = *p;
(*p)->filhoEsq = temp;
*p = q;
}


void rotEsq(elemento  **p){
    elemento *q, *temp;
    q = (*p)->filhoDir;
    temp = q->filhoEsq;
    q->filhoEsq = *p;
    (*p)->filhoDir = temp;
    *p = q;
}

elemento *rotEsqDir(elemento *p){
    rotEsq(&p->filhoEsq);
    rotDir(&p);
    return p;
}

elemento  *rotDirEsq(elemento *p){
    rotDir(&p->filhoDir);
    rotEsq(&p);
    return p;
}

int maior(int a, int b){
    if(a > b)
        return a;
    else
        return b;
}

int altura(elemento *p){
    if((p == NULL) || (p->filhoEsq== NULL && p->filhoDir== NULL))
        return 0;
    else
        return 1 + maior(altura(p->filhoEsq), altura(p->filhoDir));
}


int fb(elemento *p1, elemento *p2){
    int fb;
    fb= altura(p1)- altura(p2);
    return fb;
}

int fbNULLEsq(elemento *p1){
    int fb;
    fb= altura(p1)-0;
    return fb;
}

int fbNULLDir(elemento *p1){
    int fb;
    fb= 0- altura(p1);
    return fb;
}


/*int inserir(elemento **raiz, int dado){
    int res;
    if(*raiz == NULL){//árvore vazia ou nó folha
        elemento *novo;
        novo = (elemento*)malloc(sizeof(elemento));
        if(novo == NULL)
            return 0;

        novo->conteudo = dado;
        
        novo->filhoEsq = NULL;
        novo->filhoDir = NULL;
        *raiz = novo;
        return 1;
    }

    elemento *atual = *raiz;
    if(dado < atual->conteudo){
        if((res = inserir(&(atual->filhoEsq), dado)) == 1){
            if(fb(atual) >= 2){
                if(dado < (*raiz)->filhoEsq->conteudo ){
                    rotDir(raiz);
                }else{
                    rotDirEsq(*raiz);
                }
            }
        }
    }else{
        if(dado > atual->conteudo){
            if((res = inserir(&(atual->filhoDir), dado)) == 1){
                if(fb(atual) >= 2){
                    if((*raiz)->filhoDir->conteudo < dado){
                        rotEsq(raiz);
                    }else{
                        rotEsqDir(*raiz);
                    }
                }
            }
        }
    }

    return res;
}*/

void inserir(elemento **raiz, int dado){
    if(*raiz == NULL){
        *raiz = (elemento *) malloc(sizeof(elemento));
        (*raiz)->conteudo = dado;
        (*raiz)->filhoDir = NULL;
        (*raiz)->filhoEsq = NULL;
    }
    else if(dado > (*raiz)->conteudo){
        inserir(&((*raiz)->filhoDir), dado);
    }
    else if(dado <= (*raiz)->conteudo){
        inserir(&((*raiz)->filhoEsq), dado);
    }
    preOrderBalanceamento(&(*raiz));
    
    /*int fator = fb(*raiz);
    
    if (fator > 1 && dado < (*raiz)->filhoEsq->conteudo)
        rotDir((raiz));

    else if (fator < -1 && dado > (*raiz)->filhoDir->conteudo)
        rotEsq((raiz));

    else if (fator > 1 && dado > (*raiz)->filhoEsq->conteudo) {
        rotEsqDir(*raiz);
    }

    else if (fator < -1 && dado < (*raiz)->filhoDir->conteudo) {
        rotDirEsq(*raiz);
  }*/

}

void preOrderBalanceamento(elemento **p) {// supondo que aux = 1 ou 2
    elemento *t;
    int fb1, fb2;
    if ((*p)->filhoDir == NULL) {
        fb1 = fbNULLDir((*p));
    } else if ((*p)->filhoEsq == NULL) {
        fb1 = fbNULLEsq((*p));
    } else {
        fb1 = fb((*p)->filhoDir, (*p)->filhoEsq);
    }
    if ((fb1 == 0) || (fb1 == 1) || fb1 == -1) {
    }
        else {
            if (fb1 == -2) {
                t = (*p)->filhoEsq;
                if(t->filhoDir==NULL){
                    fb2= fbNULLDir(t);
;                }
                else if(t->filhoEsq==NULL){
                    fb2= fbNULLEsq(t);
                }
                else
                    fb2 = fb(t->filhoDir, t->filhoEsq);
            } else if (fb1 == 2) {
                t = (*p)->filhoDir;
                if(t->filhoDir==NULL){
                    fb2= fbNULLDir(t);
                }
                else if(t->filhoEsq==NULL){
                    fb2= fbNULLEsq(t);
                }
                else
                    fb2 = fb(t->filhoDir, t->filhoEsq);
            }
            if (((fb1 - 1) == fb2) || (fb1 + 1) == fb2) {
                if (fb1 > 0)
                    rotEsq(&(*p));
                else
                    rotDir(&(*p));
            } else {
                if (fb2 > 0) {
                    *p = rotEsqDir(*p);
                } else
                    *p = rotDirEsq(*p);
            }
        }
}



int main(){
    elemento *raiz = NULL, *raiz2 = NULL, *raiz3 = NULL;
    int n[6] = {8,4,10,9,15,12};
    int n2[6] = {8,4,10,2,6,5};
    //int n3[6]={8,2,15,9,20,17};
    for(int i = 0 ; i < 6; i++){
        inserir(&raiz, n[i]);
    }

    for (int i = 0; i < 7; i++)
    {
        inserir(&raiz2, n2[i]);
    }

    /*for (int i = 0; i < 7; i++)
    {
        inserir(&raiz3, n3[i]);
    }*/

    
    return 0;
}