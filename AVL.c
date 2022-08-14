#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    int conteudo;
    struct no *filhoEsq;
    struct no *filhoDir;
}elemento;

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
    return altura(no->filhoEsq) - altura(no->filhoDir);
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

void preOrderBalanceamento(elemento *raiz)
{
    if (raiz != NULL)
    {
        if(((fb(raiz->filhoDir) == 1 || fb(raiz->filhoDir) == -1) && (fb(raiz->filhoEsq) == 1 || fb(raiz->filhoEsq) == -1))){
            int fator = fb(raiz);
            //int fator2 = fb(raiz->filhoEsq);
            //int fator3 = fb(raiz->filhoDir);
            if(fator >= 2 && raiz->filhoDir == NULL){
                int fator2 = fb(raiz->filhoEsq);
                if (fator2 == 1){
                    rotDir(raiz);
                }else if(fator2 == -1){
                    rotEsq(raiz->filhoEsq);
                    rotDir(raiz);
                }
            }
            else if (fator <= -2 && raiz->filhoDir == NULL){
                int fator2 = fb(raiz->filhoEsq);
                if (fator2 == 1)
                {
                    rotDir(raiz->filhoEsq);
                    rotEsq(raiz);
                }
                else if (fator2 == -1)
                {
                    rotEsq(raiz);
                }
            }
            else if (fator >= 2 && raiz->filhoEsq == NULL){
                int fator3 = fb(raiz->filhoDir);
                if (fator3 == 1)
                {
                    rotDir(raiz);
                }
                else if (fator3 == -1)
                {
                    rotEsq(raiz->filhoDir);
                    rotDir(raiz);
                }
            }
            else if (fator <= -2 && raiz->filhoEsq == NULL){
                int fator3 = fb(raiz->filhoDir);
                if (fator3 == 1)
                {
                    rotDir(raiz->filhoDir);
                    rotEsq(raiz);
                }
                else if (fator3 == -1)
                {
                    rotEsq(raiz);
                }
            }else if(fator >= 2 && (raiz->filhoDir != NULL && raiz->filhoEsq != NULL)){
                int fator3 = fb(raiz->filhoDir);
                int fator2 = fb(raiz->filhoEsq);
                if (fator2 == 1 && fator3 == 1){
                    rotDir(raiz);
                }
                else if (fator2 == -1){
                    rotEsq(raiz->filhoEsq);
                    rotDir(raiz);
                }
                else if (fator3 == -1){
                    rotEsq(raiz->filhoDir);
                    rotDir(raiz);
                }
            }
            else if (fator <= -2 && (raiz->filhoDir != NULL && raiz->filhoEsq != NULL)){
                int fator3 = fb(raiz->filhoDir);
                int fator2 = fb(raiz->filhoEsq);
                if (fator2 == -1 && fator3 == -1){
                    rotEsq(raiz);
                }else if(fator2 == 1){
                    rotDir(raiz->filhoEsq);
                    rotEsq(raiz);
                }else if(fator3 == 1){
                    rotDir(raiz->filhoDir);
                    rotEsq(raiz);
                }
            }
                /*if (fator >= 2 && (fator2 == 1 && fator3 == 1))
                {
                    rotDir(raiz);
                }
                else if (fator <= -2 && (fator2 == -1 && fator3 == -1))
                {
                    rotEsq(raiz);
                }
                else if (fator >= 2 && fator2 == -1)
                {
                    rotEsq(raiz->filhoEsq);
                    rotDir(raiz);
                }
                else if (fator <= -2 && fator2 == 1)
                {
                    rotDir(raiz->filhoEsq);
                    rotEsq(raiz);
                }
                else if (fator >= 2 && fator3 == -1)
                {
                    rotEsq(raiz->filhoDir);
                    rotDir(raiz);
                }
                else if (fator <= -2 && fator3 == 1)
                {
                    rotDir(raiz->filhoDir);
                    rotEsq(raiz);
                }*/
        }else{
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