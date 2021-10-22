#include <stdio.h>
#include <stdlib.h>

#define new(a) ((a*) calloc(1, sizeof(a)))
#define max 20
#define invalido -1
#define true 1
#define false 0
#define bool char
#define tipochave int

typedef struct
{
    tipochave chave;
}produto;


typedef struct
{
    produto prod;
    int prox;
}elemento;

typedef struct
{
    elemento list[max];
    int inicio;
    int disponivel;
}lista;

void inicializarLista(lista* l)
{
    for(int i = 0; i < max - 1; i++) l->list[i].prox = i + 1;

    l->list[max - 1].prox = invalido;
    l->inicio = invalido;
    l->disponivel = 0;
}

int tamanhoLista(lista* l)
{
    int tamanho = 0;
    int i = l->inicio;

    while(i != invalido){
        i = l->list[i].prox;
        tamanho++;
    }

    return tamanho;
}

void printLista(lista* l)
{
    int i = l->inicio;

    printf("Lista: ");

    while(i != invalido){
        printf("%d ", l->list[i].prod.chave);
        i = l->list[i].prox;
    }

    printf("\n");
}

int buscaSequencialOrdenada(lista* l, tipochave chv)
{
    int i = l->inicio;

    while(i != invalido && l->list[i].prod.chave < chv){
        i = l->list[i].prox;
    }

    if(l->list[i].prod.chave == chv){
        
        printf("buscaSequencialOrdenada: Produto com a chave %d foi encontrado!\n", chv);
        return i;
    }

    printf("buscaSequencialOrdenada: Um produto com a chave %d não foi encontrado!\n", chv);

    return invalido;
}

int obterNo(lista* l)
{
    int retirado = l->disponivel;

    if(l->disponivel != invalido) l->disponivel = l->list[retirado].prox;

    return retirado;
}

bool inserirElemento(lista* l, produto p)
{
    if(l->disponivel == invalido){
        
        printf("inserirElemento: A lista está cheia!\n");
        return false;
    }

    int i = l->inicio;
    int anterior = invalido;
    tipochave chv = p.chave;

    while(i != invalido && l->list[i].prod.chave < chv){
          
        anterior = i;
        i = l->list[i].prox;
    }

    if(i != invalido && l->list[i].prod.chave == chv){
        
        printf("inserirElemento: Um produto com a chave %d já está na lista!\n", chv);
        return false;
    }

    i = obterNo(l);
    l->list[i].prod = p;

    if(anterior == invalido){

        l->list[i].prox = l->inicio;
        l->inicio = i;
    }

    else{

        l->list[i].prox = l->list[anterior].prox;
        l->list[anterior].prox = i;
    }

    printf("inserirElemento: A inserção do produto com chave %d foi um sucesso!\n", chv);
    return true;
}

void removerNo(lista* l, int i)
{
    l->list[i].prox = l->disponivel;
    l->disponivel = i;
}

bool removerElemento(lista* l, tipochave chv)
{
    if(l->inicio == invalido){

        printf("removerElemento: Está lista está vazia!\n");
        return false;
    }
    
    int i = l->inicio;
    int anterior = invalido;

    while(i != invalido && l->list[i].prod.chave < chv){
        
        anterior = i;
        i = l->list[i].prox;
    }

    if(i == invalido || l->list[i].prod.chave != chv){

        printf("removerElemento: Um produto com a chave %d não está na lista!\n", chv);
        return false;
    }

    if(anterior == invalido) l->inicio = l->list[i].prox;

    else l->list[anterior].prox = l->list[i].prox;

    removerNo(l, i);
    printf("removerElemento: A remoção do produto com chave %d foi um sucesso!\n", chv);
    return true;
}

int main()
{
    lista* listaa = new(lista);
    inicializarLista(listaa);
    printf("Tamanho da lista: %d.\n", tamanhoLista(listaa));
    produto prod1, prod2, prod3, prod4, prod5;
    prod1.chave = 40;
    prod2.chave = 1;
    prod3.chave = 10;
    prod4.chave = 20;
    prod5.chave = 30;

    inserirElemento(listaa, prod1);
    inserirElemento(listaa, prod2);
    inserirElemento(listaa, prod3);
    inserirElemento(listaa, prod4);
    inserirElemento(listaa, prod5);

    printLista(listaa);

    removerElemento(listaa, prod2.chave);
    removerElemento(listaa, 50);
    removerElemento(listaa, listaa->list[buscaSequencialOrdenada(listaa, 40)].prod.chave);

    printLista(listaa);

    return 0;
}