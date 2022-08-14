#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    int conteudo;
    struct no *filhoEsq;
    struct no *filhoDir;
}elemento;

/*void inserir(elemento **raiz, int dado){
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
    elemento *verify = *raiz;
    
}*/ 



int altura(elemento *raiz){
    if ((raiz == NULL) || (raiz->filhoEsq== NULL && raiz->filhoDir== NULL)){
        return 0;
    }
    int altura_esq = altura(raiz->filhoEsq);
    int altura_dir = altura(raiz->filhoDir);

    if(altura_esq > altura_dir){
        return(altura_esq +1);
    }
    else{
        return(altura_dir +1);
    }
}
void rotDir(elemento **no){
    elemento *p = NULL, *aux = NULL;
    p = (*no)->filhoEsq;
    aux = p->filhoDir;
    p->filhoDir = *no;
    (*no)->filhoEsq = aux;
    *no = p;
}

void rotEsq(elemento **no){
    elemento *p =   NULL, *aux = NULL;
    p = (*no)->filhoDir;
    aux = p->filhoEsq;
    p->filhoEsq = (*no);
    (*no)->filhoDir = aux;
    (*no) = p;
}

void *rotDirEsq(elemento *no){
    rotEsq(&no->filhoEsq);
    rotDir(&no);
}

void *rotEsqDir(elemento *no){
    rotDir(&no->filhoDir);
    rotEsq(&no);
}

int fb(elemento *no){
    return abs(altura(no->filhoEsq) - altura(no->filhoDir));
}

int inserir(elemento **raiz, int dado){
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
}


int main(){
    elemento *raiz = NULL;
    int n[6] = {8,4,10,9,15,12};
    int n2[6] = {2,4,5,6,8,10};
    

    for(int i = 0 ; i < 7; i++){
        inserir(&raiz, n[i]);
    }


    return 0;
}