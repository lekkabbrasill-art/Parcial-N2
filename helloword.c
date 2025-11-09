#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct {
    int dia;
    int mes;
} Data;

typedef struct {
    char nome[40];
    char telefone[15];
    char celular[15];
    char email[40];
    Data aniversario;
} Contato;

typedef struct elemento {
    Contato info;
    struct elemento *prox;
} Elemento;

void limpa_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

Elemento* cria_agenda() {
    return NULL;
}

Elemento* insere_contato(Elemento *lista) {
    Elemento *novo = (Elemento*) malloc(sizeof(Elemento));
    if (novo == NULL) {
        printf("Erro de memória!\n");
        return lista;
    }

    printf("Nome: ");
    fgets(novo->info.nome, sizeof(novo->info.nome), stdin);
    novo->info.nome[strcspn(novo->info.nome, "\n")] = 0;

    printf("Telefone: ");
    fgets(novo->info.telefone, sizeof(novo->info.telefone), stdin);
    novo->info.telefone[strcspn(novo->info.telefone, "\n")] = 0;

    printf("Celular: ");
    fgets(novo->info.celular, sizeof(novo->info.celular), stdin);
    novo->info.celular[strcspn(novo->info.celular, "\n")] = 0;

    printf("Email: ");
    fgets(novo->info.email, sizeof(novo->info.email), stdin);
    novo->info.email[strcspn(novo->info.email, "\n")] = 0;

    printf("Dia de aniversário: ");
    while (scanf("%d", &novo->info.aniversario.dia) != 1) {
        printf("Entrada invalida. Digite um numero para o dia: ");
        limpa_buffer();
    }
    limpa_buffer();

    printf("Mês de aniversário: ");
    while (scanf("%d", &novo->info.aniversario.mes) != 1) {
        printf("Entrada invalida. Digite um numero para o mes: ");
        limpa_buffer();
    }
    limpa_buffer();

    novo->prox = NULL;

    if (lista == NULL)
        return novo;

    Elemento *aux = lista;
    while (aux->prox != NULL)
        aux = aux->prox;

    aux->prox = novo;
    return lista;
}

void lista_contatos(Elemento *lista) {
    if (lista == NULL) {
        printf("\nAgenda vazia!\n");
        return;
    }

    Elemento *aux = lista;
    printf("\n--- Lista de Contatos ---\n");
    while (aux != NULL) {
        printf("\nNome: %s", aux->info.nome);
        printf("\nTelefone: %s", aux->info.telefone);
        printf("\nCelular: %s", aux->info.celular);
        printf("\nEmail: %s", aux->info.email);
        printf("\nAniversário: %02d/%02d\n", aux->info.aniversario.dia, aux->info.aniversario.mes);
        aux = aux->prox;
    }
}

Elemento* busca_contato(Elemento *lista, char nome[]) {
    Elemento *aux = lista;
    while (aux != NULL) {
        if (strcmp(aux->info.nome, nome) == 0)
            return aux;
        aux = aux->prox;
    }
    return NULL;
}

Elemento* remove_contato(Elemento *lista) {
    char nome[40];
    printf("Digite o nome do contato a remover: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = 0;

    Elemento *ant = NULL, *aux = lista;

    while (aux != NULL && strcmp(aux->info.nome, nome) != 0) {
        ant = aux;
        aux = aux->prox;
    }

    if (aux == NULL) {
        printf("Contato não encontrado!\n");
        return lista;
    }

    if (ant == NULL)
        lista = aux->prox;
    else
        ant->prox = aux->prox;

    free(aux);
    printf("Contato removido com sucesso!\n");
    return lista;
}

void atualiza_contato(Elemento *lista) {
    char nome[40];
    printf("Digite o nome do contato que deseja editar: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = 0;

    Elemento *contato = busca_contato(lista, nome);

    if (contato == NULL) {
        printf("Contato não encontrado!\n");
        return;
    }

    printf("Novo telefone: ");
    fgets(contato->info.telefone, sizeof(contato->info.telefone), stdin);
    contato->info.telefone[strcspn(contato->info.telefone, "\n")] = 0;

    printf("Novo celular: ");
    fgets(contato->info.celular, sizeof(contato->info.celular), stdin);
    contato->info.celular[strcspn(contato->info.celular, "\n")] = 0;

    printf("Novo email: ");
    fgets(contato->info.email, sizeof(contato->info.email), stdin);
    contato->info.email[strcspn(contato->info.email, "\n")] = 0;

    printf("Novo dia de aniversário: ");
    while (scanf("%d", &contato->info.aniversario.dia) != 1) {
        printf("Entrada invalida. Digite um numero para o dia: ");
        limpa_buffer();
    }
    limpa_buffer();

    printf("Novo mês de aniversário: ");
    while (scanf("%d", &contato->info.aniversario.mes) != 1) {
        printf("Entrada invalida. Digite um numero para o mes: ");
        limpa_buffer();
    }
    limpa_buffer();

    printf("Contato atualizado com sucesso!\n");
}

int main() {
    setlocale(LC_ALL, "");

    Elemento *agenda = cria_agenda();
    int opcao;
    char nome_busca[40];
    Elemento *encontrado;

    do {
        printf("\n--- MENU ---\n");
        printf("1. Inserir Contato\n");
        printf("2. Listar Contatos\n");
        printf("3. Buscar Contato\n");
        printf("4. Editar Contato\n");
        printf("5. Remover Contato\n");
        printf("6. Sair\n");
        printf("Escolha uma opção: ");

        if (scanf("%d", &opcao) != 1) {
            printf("Entrada inválida. Digite um número de 1 a 6.\n");
            limpa_buffer();
            continue;
        }
        limpa_buffer();

        switch (opcao) {
            case 1:
                agenda = insere_contato(agenda);
                break;
            case 2:
                lista_contatos(agenda);
                break;
            case 3:
                printf("Digite o nome do contato a buscar: ");
                fgets(nome_busca, sizeof(nome_busca), stdin);
                nome_busca[strcspn(nome_busca, "\n")] = 0;
                encontrado = busca_contato(agenda, nome_busca);
                if (encontrado != NULL) {
                    printf("Contato encontrado: %s\n", encontrado->info.nome);
                } else {
                    printf("Contato não encontrado!\n");
                }
                break;
            case 4:
                atualiza_contato(agenda);
                break;
            case 5:
                agenda = remove_contato(agenda);
                break;
            case 6:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 6);

    return 0;
}