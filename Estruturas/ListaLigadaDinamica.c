#include <stdio.h>
#include <stdlib.h>

#define new(a) ((a*) calloc(1, sizeof(a)))
#define true 1
#define false 0
#define bool char
#define tipochave int

typedef struct
{
    tipochave chave;
}PRODUTO;

typedef struct no
{
    PRODUTO prod;
    struct no* prox;
}ELEMENTO;

#define NO ELEMENTO*

typedef struct
{
    NO head;
}LISTA;

void inicializarLista(LISTA* l){
    l->head = NULL;
}

int tamanhoLista(LISTA* l)
{
    int tamanho = 0;
    NO i = l->head;

    while(i != NULL){
        i = i->prox;
        tamanho++;
    }

    return tamanho;
}

void printLista(LISTA* l)
{
    NO i = l->head;

    printf("Lista: ");

    while(i != NULL){
        printf("%d ", i->prod.chave);
        i = i->prox;
    }

    printf("\n");
}
 
NO buscaSequencialOrdenada(LISTA* l, tipochave chv)
{
    NO pont = l->head;

    while(pont != NULL && pont->prod.chave < chv) pont = pont->prox;

    if(pont != NULL && pont->prod.chave ) return pont;
    
    return NULL;
}

NO buscaAuxiliar(LISTA* l, tipochave chv, NO *ant){
    *ant = NULL;
    NO atual = l->head;
    
    while(atual != NULL && atual->prod.chave < chv){
        *ant = atual;
        atual = atual->prox;
    }

    if(atual != NULL && atual->prod.chave == chv)
        return atual;
    
    return NULL;
}

bool inserirNo(LISTA* l, PRODUTO prod)
{
    tipochave chv = prod.chave;
    NO ant;
    NO i;

    i = buscaAuxiliar(l, chv, &ant);

    i = (NO) malloc(sizeof(NO));
    i->prod = prod;

    if(ant != NULL){
        i->prox = ant->prox;
        ant->prox = i;
    }

    else{
        i->prox = l->head;
        l->head = i;
    }

    printf("inserirNO: A inserção do produto com chave %d foi um sucesso!\n", chv);

    return true;
}

bool removerNo(LISTA* l, tipochave chv)
{
    NO ant;
    NO i;

    i = buscaAuxiliar(l, chv, &ant);

    if(i == NULL){
        printf("removerNO: Um produto com a chave %d não está na lista!\n", chv);
        return false;
    }
    if(ant != NULL) ant->prox = i->prox;

    else l->head = i->prox;

    free(i);

    printf("removerNO: A remoção do produto com chave %d foi um sucesso!\n", chv);

    return true;
}

void reiniciarLista(LISTA* l)
{
    NO apagar;

    while(l->head != NULL){
        apagar = l->head;
        l->head = l->head->prox;
        free(apagar);
    }

    printf("reiniciarLista: Lista zerada!\n");
}

int main()
{
    LISTA* lista = new(LISTA);
    inicializarLista(lista);

    PRODUTO prod1, prod2, prod3, prod4, prod5;
    prod1.chave = 40;
    prod2.chave = 1;
    prod3.chave = 10;
    prod4.chave = 20;
    prod5.chave = 30;

    inserirNo(lista, prod1);
    inserirNo(lista, prod2);
    inserirNo(lista, prod3);
    inserirNo(lista, prod4);
    inserirNo(lista, prod5);

    printLista(lista);

    removerNo(lista, prod2.chave);
    removerNo(lista, 50);
    removerNo(lista, buscaSequencialOrdenada(lista, 40)->prod.chave);

    printLista(lista);

    reiniciarLista(lista);

    printLista(lista);

    return 0;
}