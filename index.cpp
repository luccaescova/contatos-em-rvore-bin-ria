#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Estrutura para um contato
struct Contato
{
    char nome[50];
    char celular[15];
    struct Contato* esquerda;
    struct Contato* direita;
};
// Funções para implementar no final do código
struct Contato* inserir(struct Contato* raiz, struct Contato* novo);
struct Contato* buscar(struct Contato* raiz, const char* nome);
struct Contato* remover(struct Contato* raiz, const char* nome);

void listar(struct Contato* raiz);

void menu();

int main()
{
    struct Contato* raiz = NULL;
    int opcao;
    do
    {
        menu();
        scanf("%d", &opcao);
        switch (opcao)
        {
            case 1:
            {
                // Adicionar contato
                struct Contato* novo = (struct Contato*)malloc(sizeof(struct Contato));
                printf("Nome: ");
                fg("%s", novo->nome);
                printf("Celular: ");
                scanf("%s", novo->celular);
                novo->esquerda = NULL;
                novo->direita = NULL;
                raiz = inserir(raiz, novo);
                break;
            }
            case 2: {
                // Buscar contato
                char nome[50];
                printf("Nome para buscar: ");
                scanf("%s", nome);
                struct Contato* encontrado = buscar(raiz, nome);
                if (encontrado)
                {
                    printf("Contato encontrado: %s, Celular: %s\n", encontrado->nome, encontrado->celular);
                }
                else
                {
                    printf("Contato não encontrado.\n");
                }
                break;
            }
            case 3:
            {
                // Remover contato
                char nome[50];
                printf("Nome para remover: ");
                scanf("%s", nome);
                raiz = remover(raiz, nome);
                break;
            }
            case 4:
            {
                // Listar contatos
                printf("Contatos:\n");
                listar(raiz);
                break;
            }
            case 5:
            printf("Saindo...\n");
            break;
            default:
            printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 5);
    return 0;
}
void menu()
{
    printf("\nMenu:\n");
    printf("1. Adicionar contato\n");
    printf("2. Buscar contato\n");
    printf("3. Remover contato\n");
    printf("4. Listar contatos\n");
    printf("5. Sair\n");
    printf("Escolha uma opção: ");
}
// Funções para implementar
struct Contato* inserir(struct Contato* raiz, struct Contato* novo)
{

    if (raiz == NULL)
    {
        return novo;
    }


    if (strcmp(novo->nome, raiz->nome) < 0)
    {

        raiz->esquerda = inserir(raiz->esquerda, novo);
    }
    else if (strcmp(novo->nome, raiz->nome) > 0)
    {

        raiz->direita = inserir(raiz->direita, novo);
    }
    else
    {

        printf("Contato com nome '%s' já existe. Não será inserido.\n", novo->nome);
        free(novo);
    }

    return raiz;
}
struct Contato* buscar(struct Contato* raiz, const char* nome)
{
    if (raiz == NULL)
    {

        return NULL;
    }


    if (strcmp(nome, raiz->nome) == 0)
    {

        return raiz;
    }
    else if (strcmp(nome, raiz->nome) < 0)
    {

        return buscar(raiz->esquerda, nome);
    }
    else
    {

        return buscar(raiz->direita, nome);
    }
    return NULL;
}
struct Contato* remover(struct Contato* raiz, const char* nome)
{
    if (raiz == NULL)
    {
        printf("Contato '%s' não encontrado.\n", nome);
        return NULL;
    }


    if (strcmp(nome, raiz->nome) < 0)
    {
        raiz->esquerda = remover(raiz->esquerda, nome);
    }
    else if (strcmp(nome, raiz->nome) > 0)
    {
        raiz->direita = remover(raiz->direita, nome);
    }
    else
    {

        if (raiz->esquerda == NULL && raiz->direita == NULL)
        {
            free(raiz);
            return NULL;
        }


        if (raiz->esquerda == NULL)
        {
            struct Contato* temp = raiz->direita;
            free(raiz);
            return temp;
        }
        else if (raiz->direita == NULL)
        {
            struct Contato* temp = raiz->esquerda;
            free(raiz);
            return temp;
        }


        struct Contato* substituto = raiz->direita;
        while (substituto->esquerda != NULL)
        {
            substituto = substituto->esquerda;
        }


        strcpy(raiz->nome, substituto->nome);
        strcpy(raiz->celular, substituto->celular);


        raiz->direita = remover(raiz->direita, substituto->nome);
    }
    return raiz;
}
void listar(struct Contato* raiz)
{
   if (raiz == NULL)
    {
        return;
    }


    listar(raiz->esquerda);
    printf("Nome: %s, Celular: %s\n", raiz->nome, raiz->celular);
    listar(raiz->direita);
}
