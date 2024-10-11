#include <stdio.h>
#include <stdlib.h>

typedef struct ArvMatricula {
    int codigo_da_disciplina; 
    struct ArvMatricula *esq, *dir;
} ArvMatricula;

// Funções
ArvMatricula *criaNo_Matricula(int codigo);
ArvMatricula *inserirMatricula(ArvMatricula **raiz, int codigo);
void imprimir_Matriculas(ArvMatricula *raiz);
int verificarFolhaMatricula(ArvMatricula *no);
ArvMatricula *obterUnicoFilhoMatricula(ArvMatricula *node);
ArvMatricula *encontrarMaiorDireitaMatricula(ArvMatricula *no);
int removerMatricula(ArvMatricula **raiz, int codigo);
void limpa_temas(ArvMatricula *raiz);

int main() {
    ArvMatricula *raiz = NULL;
    // Inserindo temas com base no código da disciplina (agora números inteiros)
    raiz = inserirMatricula(&raiz, 103); 
    raiz = inserirMatricula(&raiz, 102);
    imprimir_Matriculas(raiz);
    raiz = inserirMatricula(&raiz, 105); // Historias de Vida
    raiz = inserirMatricula(&raiz, 104); // Literatura

    printf("---Temas de podcast---\n\n");
    imprimir_Matriculas(raiz);

    printf("\n\n---Removendo---\n\n");
    removerMatricula(&raiz, 102); // Removendo Ciencia

    printf("---Temas de podcast---\n\n");
    imprimir_Matriculas(raiz);

    // Liberando Memoria
    limpa_temas(raiz);
    return 0;
}

// Função para criar um nó
ArvMatricula *criaNo_Matricula(int codigo) {
    ArvMatricula *novo_no = (ArvMatricula *)malloc(sizeof(ArvMatricula)); // Aloca memória para o novo nó

    if (novo_no == NULL) {
        printf("Erro na alocação de memória.\n");
        exit(1);
    }

    novo_no->codigo_da_disciplina = codigo;
    novo_no->esq = NULL;
    novo_no->dir = NULL;

    return novo_no;
}

// Função para inserir um novo código de disciplina (tema)
ArvMatricula *inserirMatricula(ArvMatricula **raiz, int codigo) {
    if (*raiz == NULL) {
        *raiz = criaNo_Matricula(codigo);
        printf("Tema com código '%d' cadastrado com sucesso!\n", codigo);
    } else {
        if (codigo < (*raiz)->codigo_da_disciplina)
            (*raiz)->esq = inserirMatricula(&((*raiz)->esq), codigo);
        else if (codigo > (*raiz)->codigo_da_disciplina)
            (*raiz)->dir = inserirMatricula(&((*raiz)->dir), codigo);
        else
            printf("Nao e possivel cadastrar o podcast com código '%d' novamente na mesma plataforma.\n", codigo);
    }

    return *raiz;
}

// Função para imprimir os temas (inorder traversal)
void imprimir_Matriculas(ArvMatricula *raiz) {
    if (raiz != NULL) {
        imprimir_Matriculas(raiz->esq);
        printf("Código da Disciplina: %d\n", raiz->codigo_da_disciplina);        
        imprimir_Matriculas(raiz->dir);
    }
}

// Função para verificar se o nó é uma folha
int verificarFolhaMatricula(ArvMatricula *no) {
    return (no->esq == NULL && no->dir == NULL);
}

// Função para obter o único filho (se houver)
ArvMatricula *obterUnicoFilhoMatricula(ArvMatricula *no) {
    if (no->esq != NULL && no->dir == NULL)
        return no->esq;
    else if (no->dir != NULL && no->esq == NULL)
        return no->dir;
    else
        return NULL;
}

// Função para encontrar o maior valor à direita
ArvMatricula *encontrarMaiorDireitaMatricula(ArvMatricula *no) {
    if (no->dir == NULL)
        return no;
    return encontrarMaiorDireitaMatricula(no->dir);
}

// Função para remover um tema (código da disciplina)
int removerMatricula(ArvMatricula **raiz, int codigo) {
    int remove = 1;
    ArvMatricula *maior = NULL;

    if (*raiz != NULL) {

        if ((*raiz)->codigo_da_disciplina == codigo) {
            ArvMatricula *Aux, *filho;

            if (verificarFolhaMatricula(*raiz)) {
                Aux = *raiz;
                *raiz = NULL;
                free(Aux);
            } else if ((filho = obterUnicoFilhoMatricula(*raiz)) != NULL) {
                Aux = *raiz;
                *raiz = filho;
                free(Aux);
            } else {
                Aux = *raiz;
                maior = encontrarMaiorDireitaMatricula((*raiz)->esq);
                (*raiz)->codigo_da_disciplina = maior->codigo_da_disciplina;
                removerMatricula(&((*raiz)->esq), maior->codigo_da_disciplina);
                free(Aux);
            }
        } else if (codigo < (*raiz)->codigo_da_disciplina) {
            remove = removerMatricula(&((*raiz)->esq), codigo);
        } else {
            remove = removerMatricula(&((*raiz)->dir), codigo);
        }
    } else {
        remove = 0;
    }
    return remove;
}

// Função para liberar a memória da árvore
void limpa_temas(ArvMatricula *raiz) {
    if (raiz != NULL) {
        limpa_temas(raiz->esq);
        limpa_temas(raiz->dir);
        free(raiz);
    }
}
