#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ArvMatricula {
    char nome[100]; 
    struct ArvMatricula *esq, *dir;
} ArvMatricula;



ArvMatricula *criaNo_Tema(const char tema[]);
ArvMatricula *inserirTema(ArvMatricula **raiz, const char tema[]);

void imprimir_Matriculas(ArvMatricula *raiz);

int verificarFolhaMatricula(ArvMatricula *no);
ArvMatricula *obterUnicoFilhoMatricula(ArvMatricula *node);
ArvMatricula *encontrarMaiorDireitaMatricula(ArvMatricula *no);
int removerTemas(ArvMatricula **raiz, const char tema[]);

void limpa_temas(ArvMatricula *raiz);
int main() {
   ArvMatricula *raiz = NULL;
   raiz = inserirTema(&raiz, "Gastronomia");
   raiz = inserirTema(&raiz, "Ciencia");
   raiz = inserirTema(&raiz, "Historias de Vida");
   raiz = inserirTema(&raiz, "Literatura");

   printf("---Temas de podcast---\n\n");
   imprimir_Matriculas(raiz);

   printf("\n\n---Removendo---\n\n");
   removerTemas(&raiz, "Ciencia");

   printf("---Temas de podcast---\n\n");
   imprimir_Matriculas(raiz);

    //Liberando Memoria
    limpa_temas(raiz);
    return 0;
}

ArvMatricula *criaNo_Tema(const char tema[]) {
    ArvMatricula *novo_no = (ArvMatricula *)malloc(sizeof(ArvMatricula)); // Aloca memória para o novo nó.

    if (novo_no == NULL) {
        printf("Erro na alocação de memória.\n");
        exit(1);
    }


    strncpy(novo_no->nome, tema, sizeof(novo_no->nome)); 
    novo_no->esq = NULL;
    novo_no->dir = NULL;

    return novo_no;
}

ArvMatricula *inserirTema(ArvMatricula **raiz, const char tema[]) {
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

void imprimir_Matriculas(ArvMatricula *raiz) {
    if (raiz != NULL) {

        imprimir_Matriculas(raiz->esq);
        printf("Título: %s\n", raiz->nome);        
        imprimir_Matriculas(raiz->dir);
    }
}
int verificarFolhaMatricula(ArvMatricula *no) {
    return (no->esq == NULL && no->dir == NULL);
}

ArvMatricula *obterUnicoFilhoMatricula(ArvMatricula *no) {
    if (no->esq != NULL && no->dir == NULL)
        return no->esq;
    else if (no->dir != NULL && no->esq == NULL)
        return no->dir;
    else
        return NULL;
}

ArvMatricula *encontrarMaiorDireitaMatricula(ArvMatricula *no) {
    // Se não houver um filho à direita, este nó é o maior
    if (no->dir == NULL)
        return no;
    
    // Chamada recursiva para o filho à direita
    return encontrarMaiorDireitaMatricula(no->dir);
}

int removerTemas(ArvMatricula **raiz, const char tema[]) {
    int remove = 1;
    ArvMatricula *maior = NULL;

    if (*raiz != NULL) {

        if (strcmp((*raiz)->nome, tema) == 0) {
            ArvMatricula *Aux, *filho;

            if (verificarFolhaMatricula(*raiz)) {
                Aux = *raiz;
                *raiz = NULL;
                free(Aux);
            } else if ((filho = obterUnicoFilhoMatricula(*raiz)) != NULL) {
                // OBS: Se a função tiver dois filhos ela tem que retornar NULL.
                Aux = *raiz;
                *raiz = filho;
                free(Aux);
            } else {
                Aux = *raiz;
                maior = encontrarMaiorDireitaMatricula((*raiz)->esq);
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

void limpa_temas(ArvMatricula *raiz) {
    if (raiz != NULL) {
        limpa_temas(raiz->esq);
        limpa_temas(raiz->dir);
        free(raiz);
    }
}