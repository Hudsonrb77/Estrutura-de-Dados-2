#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Cursos{
    int codigo_da_disciplina, quantidade_de_periodos;
    char nome_do_curso[50];
} Cursos;
//Código  do  curso,  Nome  do  curso,  quantidade  de  Períodos  e  uma  árvore  de 
//Disciplinas. 
typedef struct ArvCursos {
    Cursos info; 
    //Arvore de Disciplinas
    struct ArvCursos *esq, *dir;
} ArvCursos;

// Funções
ArvCursos *criaNo_Curso(int codigoDisciplina, char nome_do_curso[], int quantidade_de_periodos);
ArvCursos *inserirCurso(ArvCursos **raiz, int codigoDisciplina, char nome_do_curso[], int quantidade_de_periodos);
void imprimir_Cursos(ArvCursos *raiz);
int verificarFolhaCurso(ArvCursos *no);
ArvCursos *obterUnicoFilhoCurso(ArvCursos *node);
ArvCursos *encontrarMaiorDireitaCurso(ArvCursos *no);
int removerCurso(ArvCursos **raiz, int codigo);
void limpar_cursos(ArvCursos *raiz);

int main() {
    ArvCursos *raiz = NULL;

    raiz = inserirCurso(&raiz, 103, "Sistemas de Informacao", 1); 
    raiz = inserirCurso(&raiz, 102, "Matematica", 3);
    raiz = inserirCurso(&raiz, 105, "Medicina", 2);
    raiz = inserirCurso(&raiz, 104, "Biologia", 1); 

    printf("---ANTES DE REMOVER UM ELEMENTO---\n\n");
    imprimir_Cursos(raiz);

    printf("\n\n---Removendo um curso---\n\n");
    removerCurso(&raiz, 102); 

    printf("---MOSTRANDO OS CURSOS---\n\n");
    imprimir_Cursos(raiz);

    // Liberando Memoria
    limpar_cursos(raiz);
    return 0;
}

// Função para criar um nó
ArvCursos *criaNo_Curso(int codigoDisciplina, char nome_do_curso[], int quantidade_de_periodos) {
    ArvCursos *novo_no = (ArvCursos *)malloc(sizeof(ArvCursos)); 

    if (novo_no == NULL) {
        printf("Erro na alocação de memória.\n");
        exit(1);
    }
    printf("Disciplina com código '%s' cadastrado com sucesso!\n", nome_do_curso);

    novo_no->info.codigo_da_disciplina = codigoDisciplina;
    strcpy(novo_no->info.nome_do_curso, nome_do_curso);
    novo_no->info.quantidade_de_periodos = quantidade_de_periodos;
    novo_no->esq = NULL;
    novo_no->dir = NULL;

    return novo_no;
}

// Função para inserir um novo código de disciplina (tema)
ArvCursos *inserirCurso(ArvCursos **raiz, int codigoDisciplina, char nome_do_curso[], int quantidade_de_periodos) {
    if (*raiz == NULL) {
        *raiz = criaNo_Curso(codigoDisciplina, nome_do_curso, quantidade_de_periodos);
        
    } else {
        if (codigoDisciplina < (*raiz)->info.codigo_da_disciplina)
            (*raiz)->esq = inserirCurso(&((*raiz)->esq), codigoDisciplina, nome_do_curso, quantidade_de_periodos);
        else if (codigoDisciplina > (*raiz)->info.codigo_da_disciplina)
            (*raiz)->dir = inserirCurso(&((*raiz)->dir), codigoDisciplina, nome_do_curso, quantidade_de_periodos);
        else
            printf("Nao e possivel cadastrar o podcast com código '%d' novamente na mesma plataforma.\n", codigoDisciplina);
    }
    
    return *raiz;
}

// Função para imprimir os temas (inorder traversal)
void imprimir_Cursos(ArvCursos *raiz) {
    if (raiz != NULL) {
        imprimir_Cursos(raiz->esq);
        printf("Código da Disciplina: %d  Nome do Curso: %s Quantidade de Periodos: %d\n", raiz->info.codigo_da_disciplina, raiz->info.nome_do_curso, raiz->info.quantidade_de_periodos);        
        printf("Debug: Nome do Curso = %s\n", raiz->info.nome_do_curso); 
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
