#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct no{
    int dado;
    struct no *esq;
    struct no *dir;
}no;

void rot_dir(no **p);
void rot_esq(no  **p);
no *rot_esq_dir(no *p);
no *rot_dir_esq(no *p);
void inserir(no **p, int di);
void preOrder(no *p);
int fb(no *p1, no *p2);
int maior(int a, int b);
int altura(no *p);


int main() {
    no *p=NULL;
    int high;
    inserir(&p, 8);
    inserir(&p, 4);
    inserir(&p, 10);
    inserir(&p, 2);
    inserir(&p, 6);
    inserir(&p, 5);
    preOrder(p);
    p=rot_esq_dir(p);
    printf("\n");
    preOrder(p);
    high=altura(p);
    printf("\n\n%d", high);
    return 0;
}

void rot_dir(no **p){
no *q, *temp;
q = (*p)->esq;
temp = q->dir;
q->dir = *p;
(*p)->esq = temp;
*p = q;
}


void rot_esq(no  **p){
    no *q, *temp;
    q = (*p)->dir;
    temp = q->esq;
    q->esq = *p;
    (*p)->dir = temp;
    *p = q;
}

no *rot_esq_dir(no *p){
    rot_esq(&p->esq);
    rot_dir(&p);
    return p;
}

no  *rot_dir_esq(no *p){
    rot_dir(&p->dir);
    rot_esq(&p);
    return p;
}

void inserir(no **p, int di){
    no *q, *t;
    int aux=0, fb1,fb2;

    q = (no *) malloc(sizeof(no));
    if(*p==NULL){
        q->dado=di;
        q->esq=NULL;
        q->dir=NULL;
        *p=q;
    }
    else {
        t = *p;
        while ((t != NULL) && (aux == 0)) {
            if (di < (t->dado)) {
                if (t->esq != NULL) {
                    t = t->esq;
                } else {
                    t->esq = q;
                    q->dado = di;
                    q->esq = NULL;
                    q->dir = NULL;
                    aux = 1;
                }

            } else if (di > (t->dado)) {
                if (t->dir != NULL) {
                    t = t->dir;
                } else {
                    t->dir = q;
                    q->dado = di;
                    q->esq = NULL;
                    q->dir = NULL;
                    aux = 2;
                }
            }
        }
        /*if (aux == 1)
            fb1=fb(*p, (*p)->esq);
        else
            fb2=fb(*p,(*p)->dir);
*/
    }



}

int fb(no *p1, no *p2){
    int fb;
    fb= altura(p1)- altura(p2);
    return fb;
}

void preOrder(no *p){
    if(p!=NULL) {
        printf("%d\n", p->dado);
        preOrder(p->esq);
        preOrder(p->dir);
    }
}

int maior(int a, int b){
    if(a > b)
        return a;
    else
        return b;
}

int altura(no *p){
    if((p == NULL) || (p->esq== NULL && p->dir== NULL))
        return 0;
    else
        return 1 + maior(altura(p->esq), altura(p->dir));
}


