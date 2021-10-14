#include <stdio.h>

#define max 20
#define invalido -1
#define true 1
#define false 0

typedef int bool;
typedef int tipochave;

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

int main(){

    return 0;
}

void inicializarLista(lista* l){

    for(int i = 0; i < max - 1; i++) l->list[i].prox - i + 1;

    l->list[max - 1].prox = invalido;
    l->inicio = invalido;
    l->disponivel = 0;
}

int tamanhoLista(lista* l){

    int tamanho = 0;
    int i = l->inicio;

    while(i != invalido){
        i = l->list[i].prox;
        tamanho++;
    }

    return tamanho;
}

void printLista(lista* l){

    int i = l->inicio;

    printf('Lista: ');

    while(i != invalido){
        printf('i% ', l->list[i].prod.chave);
        i = l->list[i].prox;
    }

    printf('\n');
}

int buscaSequencial(lista* l, tipochave chv){

    int i = l->inicio;

    while(i != invalido && l->list[i].prod.chave){
        i = l->list[i].prox;
    }

    if(i != invalido) return i;

    return invalido;
}

bool inserirElemento(lista* l, produto p){

    if(l->disponivel == invalido){
        
        printf('A lista está cheia!\n');
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
        
        printf('Um produto com a mesma chave já está na lista!\n');
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

    printf('A inserção foi um sucesso!\n');
    return true;
}

int obterNo(lista* l){

    int retirado = l->disponivel;

    if(l->disponivel != invalido) l->disponivel = l->list[retirado].prox;

    return retirado;
}

bool removerElemento(lista* l, tipochave chv){

    if(l->inicio == invalido){

        printf('Está lista está vazia');
        return false;
    }
    
    int i = l->inicio;
    int anterior = invalido;

    while(i != invalido && l->list[i].prod.chave < chv){
        
        anterior = i;
        i = l->list[i].prox;
    }

    if(i != invalido && l->list[i].prod.chave != chv){

        printf('Um produto com essa chave não está na lista!\n');
        return false;
    }

    if(anterior == invalido) l->inicio = l->list[i].prox;

    else l->list[anterior].prox = l->list[i].prox;

    removerNo(l, i);
    printf('A remoção foi um sucesso!');
    return true;
}

void removerNo(lista* l, int i){

    l->list[i].prox = l->disponivel;
    l->disponivel = i;
}