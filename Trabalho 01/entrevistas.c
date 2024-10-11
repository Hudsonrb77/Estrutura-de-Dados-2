#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Data {
    char dia[3];
    char mes[3];
    char ano[3]; 
} Data;


typedef struct Entrevista {
    char titulo_da_entrevista[100]; 
    Data data;
    float  duracao;  
    char nome_do_entrevistado[50], especialidade_do_entrevistado[20]; 
    struct Entrevista *esq, *dir;
} Entrevista;



void preencherData(Data *data, const char dia[], const char mes[], const char ano[]);
Entrevista *criaNo_Entrevistas(const char tituloEntrevista[], const char dia[], const char mes[], const char ano[], float duracao, const char nome_entrevistado[], const char especialidade_entrevistado[]);
Entrevista *inserirEntrevistas(Entrevista **raiz, const char tituloEntrevista[], const char dia[], const char mes[], const char ano[], float duracao, const char nome_entrevistado[], const char especialidade_entrevistado[]);

void imprimir_Entrevistas(Entrevista *raiz);

int verificarFolha(Entrevista *no);
Entrevista *obterUnicoFilho(Entrevista *node);
Entrevista *encontrarMaiorDireita(Entrevista *no);
int removerEntrevista(Entrevista **raiz, const char tituloEntrevista[]);

void limpaMemoria_entrevistas(Entrevista *raiz);

int main() {
   Entrevista *raiz = NULL;

    // Inserção dos elementos
    raiz = inserirEntrevistas(&raiz, "Literatura", "10", "08", "2021", 20.8, "J.K. Rowling", "Escritora");
    raiz = inserirEntrevistas(&raiz, "Historias de Vida", "15", "03", "2022", 60.0, "Nelson Mandela", "Político");
    raiz = inserirEntrevistas(&raiz, "Ciencia", "19", "04", "2024", 30.5, "Albert Einstein", "Físico");
    raiz = inserirEntrevistas(&raiz, "Gastronomia", "20", "05", "2023", 45.2, "Gordon Ramsay", "Chef");

    // Impressão dos elementos
    printf("---Entrevistas do Tema---\n\n");
    imprimir_Entrevistas(raiz);

    // Remover elemento
    // Impressão dos elementos
    printf("---Remover Entrevistas do Tema---\n\n");
    removerEntrevista(&raiz, "ss de Vida");


    // Impressão dos elementos
    printf("---Entrevistas do Tema---\n\n");
    imprimir_Entrevistas(raiz);

    //Liberar a memoria
    void limpaMemoria_entrevistas(Entrevista *raiz);

    return 0;
}


void preencherData(Data *data, const char dia[], const char mes[], const char ano[]) {
    strcpy(data->dia, dia);
    strcpy(data->mes, mes);
    strcpy(data->ano, ano);
}


Entrevista *criaNo_Entrevistas(const char tituloEntrevista[], const char dia[], const char mes[], const char ano[], float duracao, const char nome_entrevistado[], const char especialidade_entrevistado[]) {
    
    Entrevista *novo_no = (Entrevista *)malloc(sizeof(Entrevista)); // Aloca memória para o novo nó.

    if (novo_no == NULL) {
        printf("Erro na alocação de memória.\n");
        exit(1);
    }


    strcpy(novo_no->titulo_da_entrevista, tituloEntrevista); 
    preencherData(&(novo_no->data), dia, mes, ano);
    novo_no->duracao = duracao;
    strcpy(novo_no->nome_do_entrevistado, nome_entrevistado);
    strcpy(novo_no->especialidade_do_entrevistado, especialidade_entrevistado);
    novo_no->esq = NULL;
    novo_no->dir = NULL;


    return novo_no;
}


Entrevista *inserirEntrevistas(Entrevista **raiz, const char tituloEntrevista[], const char dia[], const char mes[], const char ano[], float duracao, const char nome_entrevistado[], const char especialidade_entrevistado[]) {
    if (*raiz == NULL) {
        *raiz = criaNo_Entrevistas(tituloEntrevista, dia, mes, ano, duracao, nome_entrevistado, especialidade_entrevistado);
        printf("Podcast '%s' cadastrado com sucesso!\n", tituloEntrevista);
    } else {
        if (strcmp(tituloEntrevista, (*raiz)->titulo_da_entrevista) < 0) {
            (*raiz)->esq = inserirEntrevistas(&((*raiz)->esq), tituloEntrevista, dia, mes, ano, duracao, nome_entrevistado, especialidade_entrevistado);
        }
        else if (strcmp(tituloEntrevista, (*raiz)->titulo_da_entrevista) > 0) {
            (*raiz)->dir = inserirEntrevistas(&((*raiz)->dir), tituloEntrevista, dia, mes, ano, duracao, nome_entrevistado, especialidade_entrevistado);
        }
        else {
            printf("Não é possível cadastrar o podcast '%s' novamente na mesma plataforma.\n", tituloEntrevista);
        }
    }

    return *raiz;
}


void imprimir_Entrevistas(Entrevista *raiz) {

    if (raiz != NULL) {

        imprimir_Entrevistas(raiz->esq);

        printf("Título: %s\n", raiz->titulo_da_entrevista);
        printf("Data da Entrevista: %s/%s/%s\n", raiz->data.dia, raiz->data.mes, raiz->data.ano);
        printf("Duração: %.2f\n", raiz->duracao);
        printf("Nome do Entrevistado: %s\n", raiz->nome_do_entrevistado);
        printf("Especialidade do Entrevistado: %s\n\n", raiz->especialidade_do_entrevistado);

        imprimir_Entrevistas(raiz->dir);
    }
}


int verificarFolha(Entrevista *no) {
    return (no->esq == NULL && no->dir == NULL);
}


Entrevista *obterUnicoFilho(Entrevista *no) {
    if (no->esq != NULL && no->dir == NULL)
        return no->esq;
    else if (no->dir != NULL && no->esq == NULL)
        return no->dir;
    else
        return NULL;
}


Entrevista *encontrarMaiorDireita(Entrevista *no) {
    // Se não houver um filho à direita, este nó é o maior
    if (no->dir == NULL)
        return no;
    
    // Chamada recursiva para o filho à direita
    return encontrarMaiorDireita(no->dir);
}


int removerEntrevista(Entrevista **raiz, const char tituloEntrevista[]) {
    int remove = 0;
    Entrevista *maior = NULL;

    if (*raiz != NULL) {

        if (strcmp((*raiz)->titulo_da_entrevista, tituloEntrevista) == 0) {
            Entrevista *Aux, *filho;

            if (verificarFolha(*raiz)) {
                Aux = *raiz;
                *raiz = NULL;
                free(Aux);
            } else if ((filho = obterUnicoFilho(*raiz)) != NULL) {
                // OBS: Se a função tiver dois filhos ela tem que retornar NULL.
                Aux = *raiz;
                *raiz = filho;
                free(Aux);
            } else {
                Aux = *raiz;
                maior = encontrarMaiorDireita((*raiz)->esq);
                strcpy((*raiz)->titulo_da_entrevista, maior->titulo_da_entrevista);
                removerEntrevista(&((*raiz)->esq), maior->titulo_da_entrevista);
                free(Aux);
            }
        } else if (strcmp(tituloEntrevista, (*raiz)->titulo_da_entrevista) < 0) {
            remove = removerEntrevista(&((*raiz)->esq), tituloEntrevista);
        } else {
            remove = removerEntrevista(&((*raiz)->dir), tituloEntrevista);
        }

    } else {
        remove = 1;
    }
    return remove;
}

void limpaMemoria_entrevistas(Entrevista *raiz) {
    if (raiz != NULL) {
        limpaMemoria_entrevistas(raiz->esq);
        limpaMemoria_entrevistas(raiz->dir);
        free(raiz);
    }
}