#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    int conteudo;
    int altura;
    struct no *filhoEsq;
    struct no *filhoDir;
}elemento;

int altura(elemento *raiz){
    if ((raiz == NULL) /*|| (raiz->filhoEsq== NULL && raiz->filhoDir== NULL)*/){
        return -1;
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

void *rotDirEsq(elemento *no){
    rotEsq(&no->filhoEsq);
    rotDir(&no);
}

void *rotEsqDir(elemento *no){
    rotDir(&no->filhoDir);
    rotEsq(&no);
}

int fb(elemento *no){
    if(no->filhoDir == NULL && no->filhoEsq != NULL){
        return (no->filhoEsq->altura);
    }else if(no->filhoEsq == NULL && no->filhoDir != NULL){
        return (-(no->filhoDir->altura));
    }else if(no->filhoDir == NULL && no->filhoEsq == NULL){
        return 0;
    }else if(no->filhoDir != NULL && no->filhoEsq != NULL){
        return (no->filhoEsq->altura - no->filhoDir->altura);
    }
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

void preOrderAltura(elemento *raiz)
{
    if(raiz != NULL){
        raiz->altura = altura(raiz);
        preOrderAltura(raiz->filhoEsq);
        preOrderAltura(raiz->filhoDir);
    }
}

void preOrderBalanceamento(elemento *raiz){
    int balanceada = 0;
    if(raiz != NULL){
        int fator = fb(raiz);
        if(fator >= 2){
            int fator2 = fb(raiz->filhoEsq);
            if(fator2 >= 0){
                rotDir(raiz);
                balanceada = 1;
            }else if(fator2 < 0){
                rotEsq(raiz->filhoEsq);
                rotDir(raiz);
                balanceada = 1;
            }
        }else if(fator <= -2){
            int fator2 = fb(raiz->filhoDir);
            if(fator2 >= 0){
                rotDir(raiz->filhoDir);
                rotEsq(raiz);
                balanceada = 1;
            }else if(fator2 < 0){
                rotEsq(raiz);
                balanceada = 1;
            }
        }
        if(balanceada == 0){
            preOrderBalanceamento(raiz->filhoEsq);
            preOrderBalanceamento(raiz->filhoDir);
        }
    }
}

void preOrderImprimindo(elemento *p)
{
    if (p != NULL)
    {
        printf("%d\n", p->conteudo);
        preOrderImprimindo(p->filhoEsq);
        preOrderImprimindo(p->filhoDir);
    }
}

int main(){
    elemento *raiz = NULL, *raiz2 = NULL, *raiz3 = NULL;
    int n[6] = {8,4,10,9,15,12};
    int n2[6] = {8,4,10,2,6,5};
    //int n3[6]={8,2,15,9,20,17};
    for(int i = 0 ; i < 7; i++){
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

    printf("\nImprimindo a arvore n ja balanceada\n");
    preOrderBalanceamento(raiz);
    preOrderImprimindo(raiz);

    printf("\nImprimindo a arvore n2 ja balanceada\n");
    preOrderBalanceamento(raiz2);
    preOrderImprimindo(raiz2);
    return 0;
}