#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char texto_t[80];
typedef struct Contato_T Contato;
{
    texto_t nome;
    texto_t endereco;
    texto_t telefone_res;
    texto_t telefone_cel;
    texto_t data_nascimento;
    Contato *proximo;
} Contato;

Contato* criarContato()
{
    Contato *contato = (Contato *) malloc(sizeof(Contato));
    //TODO: Popular dados do contato
    contato->proximo = NULL;

    return contato;
}

typedef struct ListaEncadeada_T
{
    Contato *primeiro;
} ListaEncadeada;

ListaEncadeada* criarListaEncadeada()
{
    ListaEncadeada *lista = (ListaEncadeada *) malloc(sizeof(ListaEncadeada));
    lista->primeiro = NULL;
    return lista;
}

// inserir sempre no final
void inserirContato(ListaEncadeada *lista, Contato *novo)
{
    if (lista->primeiro == NULL)
        lista->primeiro = novo;
    else {
        Contato *aux = lista->primeiro; // percorre a partir do primeiro
        while(aux->proximo != NULL)     // até achar o último
            aux = aux->proximo;         
        aux->proximo = novo;            // insere no final
    }
}

// 1: se foi excluído com sucesso
// 0: se contato não existe na lista
int excluirContato(ListaEncadeada *lista, Contato *contato);

// NULL: se contato não existe na lista
// !NULL: contato existe na lista
Contato* pesquisarContato(ListaEncadeada *lista, texto_t nome);

// número de itens na lista
int tamanho(ListaEncadeada *lista){
    int cont = 0;
    Contato *aux = lista->primeiro;
    while (aux != NULL)
    {
        aux = aux->proximo;
        cont++;
    }
    return cont;
}