#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Cursos{
    int codigo_da_disciplina, periodo, carga_horaria;
    char nome_da_disciplina[50];
} Cursos;

typedef struct ArvCursos {
    Cursos info; 
    struct ArvCursos *esq, *dir;
} ArvCursos;

// Funções
ArvCursos *criaNo_Disciplina(int codigoDisciplina, char nome_da_disciplina[], int periodo, int carga_horaria);
ArvCursos *inserirDisciplina(ArvCursos **raiz, int codigoDisciplina, char nome_da_disciplina[], int periodo, int carga_horaria);
void imprimir_Cursos(ArvCursos *raiz);
int verificarFolhaCurso(ArvCursos *no);
ArvCursos *obterUnicoFilhoCurso(ArvCursos *node);
ArvCursos *encontrarMaiorDireitaCurso(ArvCursos *no);
int removerCurso(ArvCursos **raiz, int codigo);
void limpar_cursos(ArvCursos *raiz);

int main() {
    ArvCursos *raiz = NULL;
    // Árvore de Notas: código da disciplina, semestre cursado, nota final obtida pelo aluno. A árvore deve ser 
    // organizada pelo código da disciplina. 
    // Inserindo temas com base no código da disciplina (agora números inteiros)
    raiz = inserirDisciplina(&raiz, 103, "Portugues", 1, 30); 
    raiz = inserirDisciplina(&raiz, 102, "Matematica", 3, 120);
    raiz = inserirDisciplina(&raiz, 105, "Algoritmo", 2, 90); // Historias de Vida
    raiz = inserirDisciplina(&raiz, 104, "Circuitos", 1, 30); // Literatura

    printf("---ANTES DE REMOVER UM ELEMENTO---\n\n");
    imprimir_Cursos(raiz);

    printf("\n\n---Removendo uma disciplina---\n\n");
    removerCurso(&raiz, 102); // Removendo Ciencia

    printf("---MOSTRANDO AS DISCIPLINAS---\n\n");
    imprimir_Cursos(raiz);

    // Liberando Memoria
    limpar_cursos(raiz);
    return 0;
}

// Função para criar um nó
ArvCursos *criaNo_Disciplina(int codigoDisciplina, char nome_da_disciplina[], int periodo, int carga_horaria) {
    ArvCursos *novo_no = (ArvCursos *)malloc(sizeof(ArvCursos)); // Aloca memória para o novo nó

    if (novo_no == NULL) {
        printf("Erro na alocação de memória.\n");
        exit(1);
    }
    printf("Disciplina com código '%s' cadastrado com sucesso!\n", nome_da_disciplina);

    novo_no->info.codigo_da_disciplina = codigoDisciplina;
    strcpy(novo_no->info.nome_da_disciplina, nome_da_disciplina);
    novo_no->info.periodo = periodo;
    novo_no->info.carga_horaria = carga_horaria;
    novo_no->esq = NULL;
    novo_no->dir = NULL;

    return novo_no;
}

// Função para inserir um novo código de disciplina (tema)
ArvCursos *inserirDisciplina(ArvCursos **raiz, int codigoDisciplina, char nome_da_disciplina[], int periodo, int carga_horaria) {
    if (*raiz == NULL) {
        *raiz = criaNo_Disciplina(codigoDisciplina, nome_da_disciplina, periodo, carga_horaria);
        //printf("Disciplina com código '%s' cadastrado com sucesso!\n", nome_da_disciplina);
    } else {
        if (codigoDisciplina < (*raiz)->info.codigo_da_disciplina)
            (*raiz)->esq = inserirDisciplina(&((*raiz)->esq), codigoDisciplina, nome_da_disciplina, periodo, carga_horaria);
        else if (codigoDisciplina > (*raiz)->info.codigo_da_disciplina)
            (*raiz)->dir = inserirDisciplina(&((*raiz)->dir), codigoDisciplina, nome_da_disciplina, periodo, carga_horaria);
        else
            printf("Nao e possivel cadastrar o podcast com código '%d' novamente na mesma plataforma.\n", codigoDisciplina);
    }

    return *raiz;
}

// Função para imprimir os temas (inorder traversal)
void imprimir_Cursos(ArvCursos *raiz) {
    if (raiz != NULL) {
        imprimir_Cursos(raiz->esq);
        printf("Código da Disciplina: %d  Nome da Disciplina: %s Periodo: %d  Carga horaria: %d\n", raiz->info.codigo_da_disciplina, raiz->info.nome_da_disciplina, raiz->info.periodo, raiz->info.carga_horaria);        
        imprimir_Cursos(raiz->dir);
    }
}

// Função para verificar se o nó é uma folha
int verificarFolhaCurso(ArvCursos *no) {
    return (no->esq == NULL && no->dir == NULL);
}

// Função para obter o único filho (se houver)
ArvCursos *obterUnicoFilhoCurso(ArvCursos *no) {
    if (no->esq != NULL && no->dir == NULL)
        return no->esq;
    else if (no->dir != NULL && no->esq == NULL)
        return no->dir;
    else
        return NULL;
}

// Função para encontrar o maior valor à direita
ArvCursos *encontrarMaiorDireitaCurso(ArvCursos *no) {
    if (no->dir == NULL)
        return no;
    return encontrarMaiorDireitaCurso(no->dir);
}

// Função para remover um tema (código da disciplina)
int removerCurso(ArvCursos **raiz, int codigoDisciplina) {
    int remove = 1;
    ArvCursos *maior = NULL;

    if (*raiz != NULL) {

        if ((*raiz)->info.codigo_da_disciplina == codigoDisciplina) {
            ArvCursos *Aux, *filho;

            if (verificarFolhaCurso(*raiz)) {
                Aux = *raiz;
                *raiz = NULL;
                free(Aux);
            } else if ((filho = obterUnicoFilhoCurso(*raiz)) != NULL) {
                Aux = *raiz;
                *raiz = filho;
                free(Aux);
            } else {
                Aux = *raiz;
                maior = encontrarMaiorDireitaCurso((*raiz)->esq);
                (*raiz)->info.codigo_da_disciplina = maior->info.codigo_da_disciplina;
                removerCurso(&((*raiz)->esq), maior->info.codigo_da_disciplina);
                free(Aux);
            }
        } else if (codigoDisciplina < (*raiz)->info.codigo_da_disciplina) {
            remove = removerCurso(&((*raiz)->esq), codigoDisciplina);
        } else {
            remove = removerCurso(&((*raiz)->dir), codigoDisciplina);
        }
    } else {
        remove = 0;
    }
    return remove;
}

// Função para liberar a memória da árvore
void limpar_cursos(ArvCursos *raiz) {
    if (raiz != NULL) {
        limpar_cursos(raiz->esq);
        limpar_cursos(raiz->dir);
        free(raiz);
    }
}
