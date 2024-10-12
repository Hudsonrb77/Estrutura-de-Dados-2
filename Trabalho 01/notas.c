#include <stdio.h>
#include <stdlib.h>

typedef struct Notas{
    int codigo_da_disciplina, semestre_cursado;
    float nota_final;
} Notas;

typedef struct ArvCursos {
    Notas info; 
    struct ArvCursos *esq, *dir;
} ArvCursos;

// Funções
ArvCursos *criaNo_Disciplina(int codigoDisciplina, int semestreCursado, float notaFinal);
ArvCursos *inserirDisciplina(ArvCursos **raiz, int codigoDisciplina, int semestreCursado, float notaFinal);
void imprimir_Cursos(ArvCursos *raiz);
int verificarFolhaMatricula(ArvCursos *no);
ArvCursos *obterUnicoFilhoMatricula(ArvCursos *node);
ArvCursos *encontrarMaiorDireitaMatricula(ArvCursos *no);
int removerMatricula(ArvCursos **raiz, int codigo);
void limpa_temas(ArvCursos *raiz);

int main() {
    ArvCursos *raiz = NULL;
    // Árvore de Notas: código da disciplina, semestre cursado, nota final obtida pelo aluno. A árvore deve ser 
    // organizada pelo código da disciplina. 
    // Inserindo temas com base no código da disciplina (agora números inteiros)
    raiz = inserirDisciplina(&raiz, 103, 1, 8.5); 
    raiz = inserirDisciplina(&raiz, 102, 3, 8.2);
    raiz = inserirDisciplina(&raiz, 105, 2, 2); // Historias de Vida
    raiz = inserirDisciplina(&raiz, 104, 1, 10); // Literatura

    printf("---Temas de podcast---\n\n");
    imprimir_Cursos(raiz);

    printf("\n\n---Removendo---\n\n");
    removerMatricula(&raiz, 102); // Removendo Ciencia

    printf("---Temas de podcast---\n\n");
    imprimir_Cursos(raiz);

    // Liberando Memoria
    limpa_temas(raiz);
    return 0;
}

// Função para criar um nó
ArvCursos *criaNo_Disciplina(int codigoDisciplina, int semestreCursado, float notaFinal) {
    ArvCursos *novo_no = (ArvCursos *)malloc(sizeof(ArvCursos)); // Aloca memória para o novo nó

    if (novo_no == NULL) {
        printf("Erro na alocação de memória.\n");
        exit(1);
    }

    novo_no->info.codigo_da_disciplina = codigoDisciplina;
    novo_no->info.semestre_cursado = semestreCursado;
    novo_no->info.nota_final = notaFinal;
    novo_no->esq = NULL;
    novo_no->dir = NULL;

    return novo_no;
}

// Função para inserir um novo código de disciplina (tema)
ArvCursos *inserirDisciplina(ArvCursos **raiz, int codigoDisciplina, int semestreCursado, float notaFinal) {
    if (*raiz == NULL) {
        *raiz = criaNo_Disciplina(codigoDisciplina, semestreCursado, notaFinal);
        printf("Tema com código '%d' cadastrado com sucesso!\n", codigoDisciplina);
    } else {
        if (codigoDisciplina < (*raiz)->info.codigo_da_disciplina)
            (*raiz)->esq = inserirDisciplina(&((*raiz)->esq), codigoDisciplina, semestreCursado, notaFinal);
        else if (codigoDisciplina > (*raiz)->info.codigo_da_disciplina)
            (*raiz)->dir = inserirDisciplina(&((*raiz)->dir), codigoDisciplina, semestreCursado, notaFinal);
        else
            printf("Nao e possivel cadastrar o podcast com código '%d' novamente na mesma plataforma.\n", codigoDisciplina);
    }

    return *raiz;
}

// Função para imprimir os temas (inorder traversal)
void imprimir_Cursos(ArvCursos *raiz) {
    if (raiz != NULL) {
        imprimir_Cursos(raiz->esq);
        printf("Código da Disciplina: %d  Semestre Cursado: %d  Nota final: %.2f\n", raiz->info.codigo_da_disciplina, raiz->info.semestre_cursado, raiz->info.nota_final);        
        imprimir_Cursos(raiz->dir);
    }
}

// Função para verificar se o nó é uma folha
int verificarFolhaMatricula(ArvCursos *no) {
    return (no->esq == NULL && no->dir == NULL);
}

// Função para obter o único filho (se houver)
ArvCursos *obterUnicoFilhoMatricula(ArvCursos *no) {
    if (no->esq != NULL && no->dir == NULL)
        return no->esq;
    else if (no->dir != NULL && no->esq == NULL)
        return no->dir;
    else
        return NULL;
}

// Função para encontrar o maior valor à direita
ArvCursos *encontrarMaiorDireitaMatricula(ArvCursos *no) {
    if (no->dir == NULL)
        return no;
    return encontrarMaiorDireitaMatricula(no->dir);
}

// Função para remover um tema (código da disciplina)
int removerMatricula(ArvCursos **raiz, int codigoDisciplina) {
    int remove = 1;
    ArvCursos *maior = NULL;

    if (*raiz != NULL) {

        if ((*raiz)->info.codigo_da_disciplina == codigoDisciplina) {
            ArvCursos *Aux, *filho;

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
                (*raiz)->info.codigo_da_disciplina = maior->info.codigo_da_disciplina;
                removerMatricula(&((*raiz)->esq), maior->info.codigo_da_disciplina);
                free(Aux);
            }
        } else if (codigoDisciplina < (*raiz)->info.codigo_da_disciplina) {
            remove = removerMatricula(&((*raiz)->esq), codigoDisciplina);
        } else {
            remove = removerMatricula(&((*raiz)->dir), codigoDisciplina);
        }
    } else {
        remove = 0;
    }
    return remove;
}

// Função para liberar a memória da árvore
void limpa_temas(ArvCursos *raiz) {
    if (raiz != NULL) {
        limpa_temas(raiz->esq);
        limpa_temas(raiz->dir);
        free(raiz);
    }
}
