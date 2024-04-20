#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura da plataforma dos podcasts (lista simples encadeada)
typedef struct plataforma {
    char nome[100];
    struct podcast *podcasts;
    struct plataforma *proximo;
} plataforma;

// Estrutura para organizar os podcasts (árvore binária de pesquisa)
typedef struct podcast {
    char nome[100];
    char entrevistado[100];
    struct Tema *temas;
    struct podcast *esquerda;
    struct podcast *direita;
} podcast;

typedef struct Tema {
    char nome[50]; 
   //Tema *temas;
    struct Tema *esq, *dir;
} Tema;


//PLATAFORMA
void cria_plataforma(plataforma **p);
void insere_plataforma(struct plataforma **p, char nome[100]);
void imprimir_Plataformas(plataforma *plataforma_atual);
plataforma *buscar_plataforma(plataforma *plataformas, const char nome_plataforma[]);


//PODCAST
struct podcast *cria_podcast(char nome[100], char entrevistado[100]);
void insere_podcast(struct podcast **raiz, char nome[100], char entrevistado[100]);
void exibe_podcasts(podcast *raiz);
struct podcast *buscar_podcast(struct podcast *raiz, const char nome_podcast[]);


//TEMA
Tema *criaNo_Tema(const char tema[]);
Tema *inserirTema(Tema **raiz, const char tema[]);
void imprimirOsTemas(Tema *raiz);

int verificarFolha(Tema *no);
Tema *obterUnicoFilho(Tema *node);
Tema *encontrarMaiorDireita(Tema *no);
int removerTemas(Tema **raiz, const char tema[]);

//LIBERAR MEMORIA
void limpa_temas(Tema *raiz);
void limparMemoria_Podcast(podcast *raiz);
void limparMemoria_Plataforma(plataforma *plataformas);




void exibir_menu();


int main() {
    plataforma *plataformas = NULL;
    plataforma *aux = NULL;
    char nome_plataforma[3][100] = {"Plataforma X", "Plataforma Y", "Plataforma Z"};
    char nome_entrevistado[3][100] = {"Entrevistado X", "Entrevistado Y", "Entrevistado Z"};
    char nome_podcast[9][100] = {"Podcast A", "Podcast B", "Podcast C", "Podcast D", "Podcast E", "Podcast F", "Podcast G", "Podcast H", "Podcast I"};
    char nome_tema[3][50] = {"Musica", "Arte", "Gastronomia"};

    
   int contPod =0;
    for (int i = 0; i < 3; i++) {
        insere_plataforma(&plataformas, nome_plataforma[i]);
    }

    podcast *auxPodcast = NULL;

    for (int i = 0; i < 3; i++) {
        aux = buscar_plataforma(plataformas, nome_plataforma[i]);

        for (int j = 0; j < 3; j++) {
            insere_podcast(&(aux->podcasts), nome_podcast[contPod], nome_entrevistado[i]);
            contPod++;


        }
    }
    int contTema=0;
    contPod = 0;
    for (int i = 0; i < 3; i++) {
        aux = buscar_plataforma(plataformas, nome_plataforma[i]);
        for (int j = 0; j < 3; j++) {
            buscar_podcast(aux->podcasts, nome_podcast[j]);
            for (int k = 0; k < 3; k++) {
                inserirTema(&(aux->podcasts->temas), nome_tema[contTema]);
                contTema++;
            }
            contPod++;
            contTema=0;
        }
    }


    
    int opcao;
    do {
        exibir_menu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                plataforma *plataformaBuscada = NULL;
               plataformaBuscada = buscar_plataforma(plataformas, "Plataforma X");
               if (plataformaBuscada == NULL){
                  printf("Plataforma nao encontrada.\n");
               } else{
                  exibe_podcasts(plataformaBuscada->podcasts);
               }
               printf("---------------xxxxxxxxxxxx-------\n\n");
               plataformaBuscada = buscar_plataforma(plataformas, "Plataforma Y");
               if (plataformaBuscada == NULL){
                  printf("Plataforma nao encontrada.\n");
               } else{
                  exibe_podcasts(plataformaBuscada->podcasts);
               }
               printf("---------------xxxxxxxxxxxx-------\n\n");
               plataformaBuscada = buscar_plataforma(plataformas, "Plataforma Z");
               if (plataformaBuscada == NULL){
                  printf("Plataforma nao encontrada.\n");
               } else{
                  exibe_podcasts(plataformaBuscada->podcasts);
               }

               printf("---------------xxxxxxxxxxxx-------\n\n");

               break;
            }
            case 2: {
                char nome_podcast[100];
                char entrevistado[100];
                char nome_plataforma[100];
                printf("Digite o nome da plataforma onde deseja cadastrar o podcast: ");
                scanf("%s", nome_plataforma);
                printf("Digite o nome do podcast: ");
                scanf("%s", nome_podcast);
                printf("Digite o nome do entrevistado: ");
                scanf("%s", entrevistado);

                int encontrou_plataforma = 0; 

                plataforma *temp = plataformas;
                while (temp != NULL && !encontrou_plataforma) {
                    if (strcmp(temp->nome, nome_plataforma) == 0) {
                        insere_podcast(&temp->podcasts, nome_podcast, entrevistado);
                        encontrou_plataforma = 1;
                    }
                    temp = temp->proximo;
                }
                if (!encontrou_plataforma) {
                    printf("Plataforma '%s' nao encontrada.\n", nome_plataforma);
                }
                break;
            }
            case 3: {
                plataforma *temp = plataformas;
                while (temp != NULL) {
                    printf("\nPlataforma: %s\n", temp->nome);
                    exibe_podcasts(temp->podcasts);
                    temp = temp->proximo;
                }
                break;
            }
            case 4: {
                plataforma *plataformaBuscada = NULL;
                podcast *podcastBuscada = NULL;

                plataformaBuscada = buscar_plataforma(plataformas, "Plataforma Y");
                if (plataformaBuscada == NULL){
                    printf("Plataforma nao encontrada.\n");
                } else {
                    podcastBuscada = buscar_podcast(plataformaBuscada->podcasts, "Podcast D");
                    if (podcastBuscada == NULL) {
                        printf("Podcast nao encontrado na plataforma.\n");
                    } else {
                        imprimirOsTemas(podcastBuscada->temas);
                    }
                }
                break;
            }
            case 0: {
                printf("Encerrando o programa...\n");
                break;
            }
            default: {
                printf("Opcao invalida! Tente novamente.\n");
            }
        }
    } while (opcao != 0);

    limparMemoria_Plataforma(plataformas);

    return 0;
}



// Função para criar uma nova plataforma
void cria_plataforma(plataforma **p) {
    *p = NULL;
}


void insere_plataforma(struct plataforma **p, char nome[100]) {
    int plataforma_existente = 0;
    struct plataforma *temp = *p;
    while (temp != NULL && !plataforma_existente) {
        if (strcmp(temp->nome, nome) == 0) {
            printf("A plataforma '%s' ja esta cadastrada.\n", nome);
            plataforma_existente = 1;
        }
        temp = temp->proximo;
    }

    if (!plataforma_existente) {
        struct plataforma *novo = (struct plataforma *)malloc(sizeof(plataforma));
        if (novo != NULL) {
            strcpy(novo->nome, nome);
            novo->podcasts = NULL; 
            novo->proximo = NULL; 
            if (*p == NULL) {
                *p = novo;
            } else {
                temp = *p;
                while (temp->proximo != NULL) {
                    temp = temp->proximo;
                }
                temp->proximo = novo;
            }
        }
        printf("Plataforma '%s' cadastrada com sucesso!\n", nome);
    }
}


plataforma *buscar_plataforma(plataforma *plataformas, const char nome_plataforma[]) {
    plataforma *encontrou = NULL; // Inicializa a variável encontrou como NULL

    // Caso base: se chegarmos ao final da lista ou se a lista estiver vazia, retornamos NULL
   if (plataformas != NULL) {
      // Verifica se o nome da plataforma atual é o que estamos procurando
      if (strcmp(plataformas->nome, nome_plataforma) == 0) {
         encontrou = plataformas; // Atualiza a variável encontrou com o ponteiro para a plataforma atual
      } else {
         // Chamada recursiva para procurar na próxima plataforma
         encontrou = buscar_plataforma(plataformas->proximo, nome_plataforma);
      }

   }

   return encontrou; // Retorna o resultado encontrado
}



// Função para alocar memória para um novo podcast
struct podcast *cria_podcast(char nome[100], char entrevistado[100]) {
    struct podcast *novo = (struct podcast *)malloc(sizeof(podcast));
    if (novo != NULL) {
        strcpy(novo->nome, nome);
        strcpy(novo->entrevistado, entrevistado);
        novo->temas = NULL;
        novo->esquerda = NULL;
        novo->direita = NULL;
    }
    return novo;
}

//Função para inserir um podcast na arvore
void insere_podcast(struct podcast **raiz, char nome[100], char entrevistado[100]) {
    if (*raiz == NULL) {
        *raiz = cria_podcast(nome, entrevistado);
        printf("Podcast '%s' cadastrado com sucesso!\n", nome);
    } else {
        int comparacao = strcmp(nome, (*raiz)->nome);
        if (comparacao < 0) {
            insere_podcast(&(*raiz)->esquerda, nome, entrevistado);
        } else if (comparacao > 0) {
            insere_podcast(&(*raiz)->direita, nome, entrevistado);
        } else {
            // Caso o nome já exista, imprime uma mensagem
            printf("Nao e possivel cadastrar o podcast '%s' novamente na mesma plataforma.\n", nome);
        }
    }
}

// Função para buscar um podcast em uma árvore binária de podcasts
struct podcast *buscar_podcast(struct podcast *raiz, const char nome_podcast[]) {
    struct podcast *encontrou = NULL; // Inicializa a variável encontrou como NULL

    if (raiz != NULL) {

        if (strcmp(raiz->nome, nome_podcast) == 0) {
            encontrou = raiz;
        } else if (strcmp(nome_podcast, raiz->nome) < 0) {
            encontrou = buscar_podcast(raiz->esquerda, nome_podcast);
        } else {
            encontrou = buscar_podcast(raiz->direita, nome_podcast);
        }
    }

    return encontrou; // Retorna o resultado encontrado
}


void limparMemoria_Podcast(podcast *raiz) {
    if (raiz != NULL) {
        limparMemoria_Podcast(raiz->esquerda);
        limparMemoria_Podcast(raiz->direita);
        free(raiz);
    }
}

void limparMemoria_Plataforma(plataforma *plataformas) {
    while (plataformas != NULL) {
        limparMemoria_Podcast(plataformas->podcasts);
        plataforma *temp_plataforma = plataformas;
        plataformas = plataformas->proximo;
        free(temp_plataforma);
    }
}

void exibe_podcasts(podcast *raiz) {
    if (raiz != NULL) {
        exibe_podcasts(raiz->esquerda);
        printf(" - Podcast: %s, Entrevistado: %s\n", raiz->nome, raiz->entrevistado);
        exibe_podcasts(raiz->direita);
    }
}

void imprimir_Plataformas(plataforma *plataforma_atual) {

   if (plataforma_atual != NULL) {

      printf("\nPlataforma: %s\n", plataforma_atual->nome);

      imprimir_Plataformas(plataforma_atual->proximo);
   }
    
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
    } else {
      if (strcmp(tema,(*raiz)->nome) < 0)
         (*raiz)->esq = inserirTema(&((*raiz)->esq), tema);
      else if (strcmp(tema, (*raiz)->nome) > 0)
         (*raiz)->dir = inserirTema(&((*raiz)->dir), tema);
        
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

void exibir_menu() {
    printf("\n=== Menu de Cadastro ===\n");
    printf("1. Cadastrar plataforma\n");
    printf("2. Cadastrar podcast\n");
    printf("3. Exibir plataformas e podcasts cadastrados\n");
    printf("0. Sair\n");
    printf("Digite a opcao desejada: ");
}