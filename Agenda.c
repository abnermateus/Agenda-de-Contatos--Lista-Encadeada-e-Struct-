#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define TAM_STR 80

typedef char texto_t[TAM_STR];

typedef struct Contato_T
{
    texto_t nome;
    texto_t endereco;
    texto_t telefone_res;
    texto_t telefone_cel;
    texto_t data_nascimento;
} Contato;

Contato *criarContato()
{
    Contato *contato = (Contato *)malloc(sizeof(Contato));

    printf("Nome: ");
    fgets(contato->nome, TAM_STR - 1, stdin);
    contato->nome[strlen(contato->nome) - 1] = '\0';

    printf("Endereco: ");
    fgets(contato->endereco, TAM_STR - 1, stdin);
    contato->endereco[strlen(contato->endereco) - 1] = '\0';

    printf("Telefone residencial: ");
    fgets(contato->telefone_res, TAM_STR - 1, stdin);
    contato->telefone_res[strlen(contato->telefone_res) - 1] = '\0';

    printf("Telefone celular: ");
    fgets(contato->telefone_cel, TAM_STR - 1, stdin);
    contato->telefone_cel[strlen(contato->telefone_cel) - 1] = '\0';

    printf("Data de nascimento: ");
    fgets(contato->data_nascimento, TAM_STR - 1, stdin);
    contato->data_nascimento[strlen(contato->data_nascimento) - 1] = '\0';

    return contato;
}

void mostrarContato(Contato *contato)
{
    printf("Nome: %s\n", contato->nome);
    printf("Endereco: %s\n", contato->endereco);
    printf("Telefone residencial: %s\n", contato->telefone_res);
    printf("Telefone celular: %s\n", contato->telefone_cel);
    printf("Data de nascimento: %s\n", contato->data_nascimento);
}

typedef Contato ItemLista;

typedef struct Celula_T
{
    ItemLista *item;
    struct Celula_T *prox;
} Celula;

Celula *criarCelula(ItemLista *item, Celula *prox)
{
    Celula *celula = (Celula *)malloc(sizeof(Celula));

    if (celula != NULL) 
    {
        celula->item = item;
        celula->prox = prox;
    }
    return celula;
}

typedef struct ListaEncadeada_T
{
    Celula *inicio;
    Celula *fim;    
    int quantos;   
} ListaEncadeada;

ListaEncadeada *criarListaEncadeada()
{
    ListaEncadeada *lista = (ListaEncadeada *)malloc(sizeof(ListaEncadeada));

    if (lista != NULL) 
    {
        lista->inicio = lista->fim = NULL;
        lista->quantos = 0;
    }
    return lista;
}

int inserirNoFim(ListaEncadeada *lista, ItemLista *item)
{
    if (lista == NULL)
        return 0;
    else
    {
        Celula *novo = criarCelula(item, NULL);

        if (novo == NULL)
            return 0; 

        if (estah_vazia(lista) == 1)
            lista->inicio = lista->fim = novo;
        else
        {
            lista->fim->prox = novo; 
        }
        lista->quantos++;
        return 1;
    }
}

int inserirNoInicio(ListaEncadeada *lista, ItemLista *item)
{
    if (lista == NULL)
        return 0;
    else
    {
        Celula *novo = criarCelula(item, lista->inicio);

        if (novo == NULL)
            return 0; 

        lista->inicio = novo;

        if (estah_vazia(lista) == 1)
            lista->fim = novo;

        lista->quantos++;
        return 1;
    }
}

int estah_vazia(ListaEncadeada *lista)
{
    if ((lista == NULL) || (lista->quantos == 0))
        return 1;

    return 0;
}

int item_ehIgual(ItemLista *item1, ItemLista *item2)
{
    if ((item1 != NULL) && (item2 != NULL) && strcmp(item1->nome, item2->nome) == 0)
        return 1;

    return 0;
}

ItemLista *excluirNoInicio(ListaEncadeada *lista)
{
    if ((lista == NULL) || (estah_vazia(lista) == 1))
        return NULL;

    Celula *aux = lista->inicio;
    lista->inicio = aux->prox;
    aux->prox = NULL;

    ItemLista *temp = aux->item;
    lista->quantos--;
    free(aux);
    return temp;
}

ItemLista *excluirNoFim(ListaEncadeada *lista)
{
    if ((lista == NULL) || (estah_vazia(lista) == 1))
        return NULL;

    Celula *aux = lista->inicio;
    ItemLista *result = NULL;

    if (tamanho(lista) == 1)
        lista->inicio = lista->fim = NULL;
    else
    {
        while (aux->prox != lista->fim)
            aux = aux->prox;

        lista->fim = aux;
        aux = aux->prox;
        lista->fim->prox = NULL;
    }
    result = aux->item;
    free(aux);
    lista->quantos--;
    return result;
}

int excluir(ListaEncadeada *lista, ItemLista *item)
{
    if (lista == NULL) 
        return 0;
    else if (estah_vazia(lista)) 
        return 0;
    else
    {
        Celula *aux = lista->inicio;

        if (item_ehIgual(aux->item, item)) 
        {
            lista->inicio = aux->prox;
            aux->prox = NULL;
            free(aux->item);
            free(aux);
            lista->quantos--;
            return 1;
        }

        else 
        {
            while (aux->prox != NULL) 
            {
                if (item_ehIgual(aux->prox->item, item))
                {
                    Celula *temp = aux->prox;

                    if (aux->prox == lista->fim)
                        lista->fim = aux;

                    aux->prox = temp->prox;
                    temp->prox = NULL;
                    free(temp->item);
                    free(temp);
                    lista->quantos--;
                    return 1;
                }
                aux = aux->prox;
            }
        }
    }
    return 0; 
}

int tamanho(ListaEncadeada *lista)
{
    if (lista == NULL)
        return 0;

    return lista->quantos;
}

ItemLista *pesquisarItem(ListaEncadeada *lista, texto_t nome)
{
    if (estah_vazia(lista) == 1)
        return NULL;

    Celula *aux = lista->inicio;

    do
    {
        if (strcmp(aux->item->nome, nome) == 0)
            return aux->item;

        aux = aux->prox;
    } 
    while (aux != NULL);

    return NULL;
}

ItemLista **obterArray(ListaEncadeada *lista)
{
    ItemLista **array = (ItemLista **)malloc(tamanho(lista) * sizeof(ItemLista *));

    Celula *aux = lista->inicio;
    for (int i = 0; i < tamanho(lista); i++)
    {
        array[i] = aux->item;
        aux = aux->prox;
    }
    return array;
}

int menu()
{
    int opcao;

    printf("\n======== ESTA E SUA AGENDA DE CONTATOS! ========\n");
    printf("\nO que voce gostaria de fazer?\n"); 
    printf("\n1. Adicionar\n");
    printf("2. Remover\n");
    printf("3. Pesquisar\n");
    printf("4. Alterar\n");
    printf("5. Listar todos\n");
    printf("6. Sair\n");

    printf("\nDigite uma opcao: ");
    scanf("%d", &opcao);

    fflush(stdin);
    return opcao;
}

int main()
{
    int opcao = 6;
    ListaEncadeada *lista = criarListaEncadeada();
    Contato *contato;
    texto_t nome;

    do
    {
        opcao = menu();

        switch (opcao)
        {
        case 1: printf("### ADICIONAR ####\n"); contato = criarContato(); inserirNoFim(lista, contato); break;

        case 2: printf("### REMOVER ####\n"); printf("Informe o nome: "); fgets(nome, TAM_STR - 1, stdin); nome[strlen(nome) - 1] = '\0';   contato = pesquisarItem(lista, nome);
            if (contato != NULL)
            {
                excluir(lista, contato);
                printf("*** Contato Excluido ***\n");
                mostrarContato(contato);
            }
            else
                printf("Excluir::Nenhum contato com o nome '%s'\n\n", nome);
            break;

        case 3: printf("### PESQUISAR ####\n");printf("Informe o nome: "); fgets(nome, TAM_STR - 1, stdin); nome[strlen(nome) - 1] = '\0'; contato = pesquisarItem(lista, nome);
            if (contato != NULL)
                mostrarContato(contato);
            else
                printf("Pesquisar::Nenhum contato com o nome '%s'\n\n", nome);
            break;

        case 4: 
            printf("### ALTERAR ####\n");
            printf("Informe o nome: ");
            fgets(nome, TAM_STR - 1, stdin);
            nome[strlen(nome) - 1] = '\0';
            texto_t nome2;
            texto_t endereco2;
            texto_t telefone_res2;
            texto_t telefone_cel2;
            texto_t data_nascimento2;
            ItemLista *item = pesquisarItem(lista,nome);
            printf("Digite o nome:\n");
            fgets(nome2, TAM_STR - 1, stdin);
            nome[strlen(nome) - 1] = '\0';
            printf("digite o endereco:\n");
            fgets(endereco2, TAM_STR - 1, stdin);
            nome[strlen(nome) - 1] = '\0';
            printf("digite o telefone residencial:\n");
            fgets(telefone_res2, TAM_STR - 1, stdin);
            nome[strlen(nome) - 1] = '\0';
            printf("digite o telefone celular:\n");
                fgets(telefone_cel2, TAM_STR - 1, stdin);
                nome[strlen(nome) - 1] = '\0';
                printf("digite o data de nascimento:\n");
                fgets(data_nascimento2, TAM_STR - 1, stdin);
                nome[strlen(nome) - 1] = '\0';
                strcpy(item->nome,nome2);
                strcpy(item->endereco,endereco2);
                strcpy(item->telefone_res,telefone_res2);
                strcpy(item->telefone_cel,telefone_cel2);
                strcpy(item->data_nascimento,data_nascimento2);
            break;

            break;

        case 5: printf("### LISTAR ####\n"); Contato **contatos = obterArray(lista);
            for (int i = 0; i < tamanho(lista); i++)
            {
                printf("**************************\n");
                mostrarContato(contatos[i]);
            }
            break;

        case 6: printf("\nSaindo da sua agenda de contatos...\n"); exit(1); break;

        default: printf("\nOpcao invalida!\n"); break;
        }
        system("pause");
        system("cls");
    } 
    while (opcao != 6);

    return 0;
}