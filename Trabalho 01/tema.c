#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Temas {
    char tema[100]; 
    //Temporadas *temporadas;
    struct Temas *esq, *dir;
    //Temporadas temporadas;
} Temas;



Temas *criaNo_Temas(const char tema[]);
Temas *inserirTemas(Temas **raiz, const char tema[]);

void imprimirOsTemas(Temas *raiz);

int verificarFolha(Temas *no);
Temas *obterUnicoFilho(Temas *node);
Temas *encontrarMaiorDireita(Temas *no);
int removerTemas(Temas **raiz, const char tema[]);


int main() {
   Temas *raiz = NULL;
   raiz = inserirTemas(&raiz, "Gastronomia");
   raiz = inserirTemas(&raiz, "Ciencia");
   raiz = inserirTemas(&raiz, "Historias de Vida");
   raiz = inserirTemas(&raiz, "Literatura");

   printf("---Temas de podcast---\n\n");
   imprimirOsTemas(raiz);

   printf("\n\n---Adicionando---\n\n");
   removerTemas(&raiz, "Ciencia");

   printf("---Temas de podcast---\n\n");
   imprimirOsTemas(raiz);

    return 0;
}

Temas *criaNo_Temas(const char tema[]) {
    Temas *novo_no = (Temas *)malloc(sizeof(Temas)); // Aloca memória para o novo nó.

    if (novo_no == NULL) {
        printf("Erro na alocação de memória.\n");
        exit(1);
    }


    strncpy(novo_no->tema, tema, sizeof(novo_no->tema)); 
    novo_no->esq = NULL;
    novo_no->dir = NULL;

    return novo_no;
}

Temas *inserirTemas(Temas **raiz, const char tema[]) {
    if (*raiz == NULL) {
        *raiz = criaNo_Temas(tema);
    } else {
      if (strcmp(tema,(*raiz)->tema) < 0)
         (*raiz)->esq = inserirTemas(&((*raiz)->esq), tema);
      else if (strcmp(tema, (*raiz)->tema) > 0)
         (*raiz)->dir = inserirTemas(&((*raiz)->dir), tema);
        
    }

    return *raiz;
}

void imprimirOsTemas(Temas *raiz) {
    if (raiz != NULL) {

        imprimirOsTemas(raiz->esq);
        printf("Título: %s\n", raiz->tema);        
        imprimirOsTemas(raiz->dir);
    }
}
int verificarFolha(Temas *no) {
    return (no->esq == NULL && no->dir == NULL);
}

Temas *obterUnicoFilho(Temas *no) {
    if (no->esq != NULL && no->dir == NULL)
        return no->esq;
    else if (no->dir != NULL && no->esq == NULL)
        return no->dir;
    else
        return NULL;
}

Temas *encontrarMaiorDireita(Temas *no) {
    // Se não houver um filho à direita, este nó é o maior
    if (no->dir == NULL)
        return no;
    
    // Chamada recursiva para o filho à direita
    return encontrarMaiorDireita(no->dir);
}

int removerTemas(Temas **raiz, const char tema[]) {
    int remove = 1;
    Temas *maior = NULL;

    if (*raiz != NULL) {

        if (strcmp((*raiz)->tema, tema) == 0) {
            Temas *Aux, *filho;

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
                strcpy((*raiz)->tema, maior->tema);
                removerTemas(&((*raiz)->esq), maior->tema);
                free(Aux);
            }
        } else if (strcmp(tema, (*raiz)->tema) < 0) {
            remove = removerTemas(&((*raiz)->esq), tema);
        } else {
            remove = removerTemas(&((*raiz)->dir), tema);
        }
    } else {
        remove = 0;
    }
    return remove;
}
