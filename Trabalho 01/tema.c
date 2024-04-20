#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tema {
    char nome[100]; 
    struct Tema *esq, *dir;
} Tema;



Tema *criaNo_Tema(const char tema[]);
Tema *inserirTema(Tema **raiz, const char tema[]);

void imprimirOsTemas(Tema *raiz);

int verificarFolha(Tema *no);
Tema *obterUnicoFilho(Tema *node);
Tema *encontrarMaiorDireita(Tema *no);
int removerTemas(Tema **raiz, const char tema[]);

void limpa_temas(Tema *raiz);
int main() {
   Tema *raiz = NULL;
   raiz = inserirTema(&raiz, "Gastronomia");
   raiz = inserirTema(&raiz, "Ciencia");
   raiz = inserirTema(&raiz, "Historias de Vida");
   raiz = inserirTema(&raiz, "Literatura");

   printf("---Temas de podcast---\n\n");
   imprimirOsTemas(raiz);

   printf("\n\n---Removendo---\n\n");
   removerTemas(&raiz, "Ciencia");

   printf("---Temas de podcast---\n\n");
   imprimirOsTemas(raiz);

    //Liberando Memoria
    limpa_temas(raiz);
    return 0;
}

Tema *criaNo_Tema(const char tema[]) {
    Tema *novo_no = (Tema *)malloc(sizeof(Tema)); // Aloca memória para o novo nó.

    if (novo_no == NULL) {
        printf("Erro na alocação de memória.\n");
        exit(1);
    }


    strncpy(novo_no->nome, tema, sizeof(novo_no->nome)); 
    novo_no->esq = NULL;
    novo_no->dir = NULL;

    return novo_no;
}

Tema *inserirTema(Tema **raiz, const char tema[]) {
    if (*raiz == NULL) {
        *raiz = criaNo_Tema(tema);
        printf("Tema '%s' cadastrado com sucesso!\n", tema);
    } else {
        if (strcmp(tema,(*raiz)->nome) < 0)
            (*raiz)->esq = inserirTema(&((*raiz)->esq), tema);
        else if (strcmp(tema, (*raiz)->nome) > 0)
            (*raiz)->dir = inserirTema(&((*raiz)->dir), tema);
        else
            printf("Nao e possivel cadastrar o podcast '%s' novamente na mesma plataforma.\n", tema);
    }

    return *raiz;
}

void imprimirOsTemas(Tema *raiz) {
    if (raiz != NULL) {

        imprimirOsTemas(raiz->esq);
        printf("Título: %s\n", raiz->nome);        
        imprimirOsTemas(raiz->dir);
    }
}
int verificarFolha(Tema *no) {
    return (no->esq == NULL && no->dir == NULL);
}

Tema *obterUnicoFilho(Tema *no) {
    if (no->esq != NULL && no->dir == NULL)
        return no->esq;
    else if (no->dir != NULL && no->esq == NULL)
        return no->dir;
    else
        return NULL;
}

Tema *encontrarMaiorDireita(Tema *no) {
    // Se não houver um filho à direita, este nó é o maior
    if (no->dir == NULL)
        return no;
    
    // Chamada recursiva para o filho à direita
    return encontrarMaiorDireita(no->dir);
}

int removerTemas(Tema **raiz, const char tema[]) {
    int remove = 1;
    Tema *maior = NULL;

    if (*raiz != NULL) {

        if (strcmp((*raiz)->nome, tema) == 0) {
            Tema *Aux, *filho;

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
                strcpy((*raiz)->nome, maior->nome);
                removerTemas(&((*raiz)->esq), maior->nome);
                free(Aux);
            }
        } else if (strcmp(tema, (*raiz)->nome) < 0) {
            remove = removerTemas(&((*raiz)->esq), tema);
        } else {
            remove = removerTemas(&((*raiz)->dir), tema);
        }
    } else {
        remove = 0;
    }
    return remove;
}

void limpa_temas(Tema *raiz) {
    if (raiz != NULL) {
        limpa_temas(raiz->esq);
        limpa_temas(raiz->dir);
        free(raiz);
    }
}