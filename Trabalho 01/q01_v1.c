#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura da plataforma dos podcasts (lista simples encadeada)
typedef struct Plataforma {
    char nome[100];
    struct Podcast *podcasts;
    struct Plataforma *proximo;
} Plataforma;

// Estrutura para organizar os podcasts (árvore binária de pesquisa)
typedef struct Podcast {
    char nome[100];
    char entrevistado[100];
    struct ArvMatricula *temas;
    struct Podcast *esq, *dir;
} Podcast;


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


typedef struct ArvMatricula {
    char nome[50]; 
    Entrevista *entrevistas;
    struct ArvMatricula *esq, *dir;
} ArvMatricula;








//PLATAFORMA
void cria_plataforma(Plataforma **p);
void insere_plataforma(struct Plataforma **p, char nome[100]);
void imprimir_Plataformas(Plataforma *plataforma_atual);
Plataforma *buscar_plataforma(Plataforma *plataformas, const char nome_plataforma[]);


//PODCAST
struct Podcast *cria_podcast(char nome[100], char entrevistado[100]);
void insere_Podcast(struct Podcast **raiz, char nome[100], char entrevistado[100]);
void imprimir_Podcasts(Podcast *raiz);
Podcast *buscar_Podcast(struct Podcast *raiz, const char nome_podcast[]);


//TEMA
ArvMatricula *criaNo_Tema(const char tema[]);
ArvMatricula *inserirTema(ArvMatricula **raiz, const char tema[]);
void imprimir_Matriculas(ArvMatricula *raiz);
ArvMatricula *buscar_Tema(struct ArvMatricula *raiz, const char nome_tema[]);


int verificarFolhaMatricula(ArvMatricula *no);
ArvMatricula *obterUnicoFilhoMatricula(ArvMatricula *node);
ArvMatricula *encontrarMaiorDireitaMatricula(ArvMatricula *no);
int removerTemas(ArvMatricula **raiz, const char tema[]);


//ENTREVISTA
void preencherData(Data *data, const char dia[], const char mes[], const char ano[]);

Entrevista *criaNo_Entrevistas(const char tituloEntrevista[], const char dia[], const char mes[], const char ano[], float duracao, const char nome_entrevistado[], const char especialidade_entrevistado[]);
Entrevista *inserirEntrevistas(Entrevista **raiz, const char tituloEntrevista[], const char dia[], const char mes[], const char ano[], float duracao, const char nome_entrevistado[], const char especialidade_entrevistado[]);

void imprimir_Entrevistas(Entrevista *raiz);
int verificarFolhaEntrevista(Entrevista *no);
Entrevista *obterUnicoFilhoEntrevista(Entrevista *node);
Entrevista *encontrarMaiorDireitaEntrevista(Entrevista *no);
int removerEntrevista(Entrevista **raiz, const char tituloEntrevista[]);


//LIBERAR MEMORIA
void limpa_temas(ArvMatricula *raiz);
void limparMemoria_Podcast(Podcast *raiz);
void limparMemoria_Plataforma(Plataforma *plataformas);
void limpa_entrevistas(Entrevista *raiz);
void limpaMemoria_entrevistas(Entrevista *raiz);



void exibir_menu();


int main() {
    Plataforma *plataformas = NULL;
    Plataforma *aux = NULL;
    char nome_plataforma[3][100] = {"Plataforma X", "Plataforma Y", "Plataforma Z"};
    char nome_entrevistado[3][100] = {"Entrevistado X", "Entrevistado Y", "Entrevistado Z"};
    char nome_podcast[9][100] = {"Podcast A", "Podcast B", "Podcast C", "Podcast D", "Podcast E", "Podcast F", "Podcast G", "Podcast H", "Podcast I"};
    char nome_tema[3][50] = {"Musica", "Arte", "Gastronomia"};

    
   int contPod =0;
    for (int i = 0; i < 3; i++) {
        insere_plataforma(&plataformas, nome_plataforma[i]);
    }

    Podcast *auxPodcast = NULL;

    for (int i = 0; i < 3; i++) {
        aux = buscar_plataforma(plataformas, nome_plataforma[i]);

        for (int j = 0; j < 3; j++) {
            insere_Podcast(&(aux->podcasts), nome_podcast[contPod], nome_entrevistado[i]);
            contPod++;


        }
    }
    int contPodcast = 0;

    for (int i = 0; i < 3; i++) {
        printf("\n-----PLATAFORMA-----\n");
        aux = buscar_plataforma(plataformas, nome_plataforma[i]);
        printf("%s\n", aux->nome);
        
        for (int j = 0; j < 3; j++) {

            printf("\n--------Podcast----\n");
            auxPodcast = buscar_Podcast(aux->podcasts, nome_podcast[contPodcast]);
            contPodcast++;

            if (auxPodcast != NULL){
                printf("%s\n", auxPodcast->nome);
                for (int k = 0; k < 3; k++) {
                    ArvMatricula *auxTema = inserirTema(&(auxPodcast->temas), nome_tema[k]);
                    inserirEntrevistas(&(auxTema->entrevistas), "Literatura", "10", "08", "2021", 20.8, "J.K. Rowling", "Escritora");
                    inserirEntrevistas(&(auxTema->entrevistas), "Historias de Vida", "15", "03", "2022", 60.0, "Nelson Mandela", "Político");
                    inserirEntrevistas(&(auxTema->entrevistas), "Cie        ncia", "19", "04", "2024", 30.5, "Albert Einstein", "Físico");
                    inserirEntrevistas(&(auxTema->entrevistas), "Gastronomia", "20", "05", "2023", 45.2, "Gordon Ramsay", "Chef");
                }
            }
            
        }
    }


    
    int opcao;
    do {
        exibir_menu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {

                Plataforma *plataformaBuscada = NULL;
                plataformaBuscada = buscar_plataforma(plataformas, "Plataforma X");
                if (plataformaBuscada == NULL){
                    printf("Plataforma nao encontrada.\n");
                } else{
                    imprimir_Podcasts(plataformaBuscada->podcasts);
                }
                printf("---------------xxxxxxxxxxxx-------\n\n");
                plataformaBuscada = buscar_plataforma(plataformas, "Plataforma Y");
                if (plataformaBuscada == NULL){
                   printf("Plataforma nao encontrada.\n");
                } else{
                   imprimir_Podcasts(plataformaBuscada->podcasts);
                }
                printf("---------------xxxxxxxxxxxx-------\n\n");
                plataformaBuscada = buscar_plataforma(plataformas, "Plataforma Z");
                if (plataformaBuscada == NULL){
                   printf("Plataforma nao encontrada.\n");
                } else{
                   imprimir_Podcasts(plataformaBuscada->podcasts);
                }

               printf("---------------Podcasts Imprimidos-------\n\n");

               break;
            }
            case 2: {
                printf("Entrou no caso 2. \n");
                break;
            }
            case 3: {

                // QUESTAO 01
                Plataforma *plataformaBuscada = NULL;
                Podcast *podcastBuscada = NULL;
                char buscarPlataforma[20];

                printf("Digite a plataforma para mostrar os podcasts em Ordem Alfabetica:");
                scanf(" %[^\n]", buscarPlataforma);


                plataformaBuscada = buscar_plataforma(plataformas, buscarPlataforma);
                if (plataformaBuscada == NULL){
                    printf("Plataforma nao encontrada.\n");
                } else{
                    imprimir_Podcasts(plataformaBuscada->podcasts);
                }
                break;
            }
            case 4: {
                //QUESTAO 2
                Plataforma *plataformaBuscada = NULL;
                char buscarPlataforma[20];

                printf("\n-----Mostrar na tela todos os temas de um PodCast de uma plataforma.----\n");


                printf("Digite a plataforma: ");
                scanf(" %[^\n]", buscarPlataforma);


                plataformaBuscada = buscar_plataforma(plataformas, buscarPlataforma);
                if (plataformaBuscada == NULL){

                    printf("Plataforma nao encontrada.\n");

                } else {
                    Podcast *podcastBuscado = NULL;
                    char buscarPodcast[20];

                    imprimir_Podcasts(plataformaBuscada->podcasts);
                    
                    printf("Digite o nome do Podcast para buscar os temas:\n");
                    scanf(" %[^\n]", buscarPodcast);

                    podcastBuscado = buscar_Podcast(plataformaBuscada->podcasts, buscarPodcast);
                   
                    if (podcastBuscado == NULL) {
                        printf("Podcast nao encontrado na plataforma.\n");
                    } else {
                        imprimir_Matriculas(podcastBuscado->temas);
                    }
                }
                break;
            }
            case 5: {
                //QUESTAO 3
                Plataforma *plataformaBuscada = NULL;
                char buscarPlataforma[20];

                printf("\n-----Mostrar na tela todos os temas de um PodCast de uma plataforma.----\n");


                printf("Digite a plataforma: ");
                scanf(" %[^\n]", buscarPlataforma);


                plataformaBuscada = buscar_plataforma(plataformas, buscarPlataforma);
                if (plataformaBuscada == NULL){

                    printf("Plataforma nao encontrada.\n");

                } else {
                    Podcast *podcastBuscado = NULL;
                    char buscarPodcast[20];
                    
                    imprimir_Podcasts(plataformaBuscada->podcasts);
                    printf("Digite o nome do Podcast para buscar os temas:\n");
                    scanf(" %[^\n]", buscarPodcast);
                    

                    podcastBuscado = buscar_Podcast(plataformaBuscada->podcasts, buscarPodcast);
                   
                    if (podcastBuscado == NULL) {
                        printf("Podcast nao encontrado na plataforma.\n");
                    } else {
                        ArvMatricula *temaBuscado = NULL;
                        char buscarTema[20];

                        imprimir_Matriculas(podcastBuscado->temas);
                        printf("Digite o nome do Tema para buscar os nomes das entrevistas:\n");
                        scanf(" %[^\n]", buscarTema);

                        //Depois testa isso: Tema *temaBuscado = buscar_tema();
                        temaBuscado = buscar_Tema(podcastBuscado->temas, buscarTema);

                        if (temaBuscado == NULL)
                            printf("Tema nao encontrado na plataforma.\n");
                        else
                            imprimir_Entrevistas(temaBuscado->entrevistas);
                    }
                }
                break;
            }
            case 0: {
                printf("\nEncerrando o programa...\n");
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
void cria_plataforma(Plataforma **p) {
    *p = NULL;
}


void insere_plataforma(struct Plataforma **p, char nome[100]) {
    int plataforma_existente = 0;
    struct Plataforma *temp = *p;
    while (temp != NULL && !plataforma_existente) {
        if (strcmp(temp->nome, nome) == 0) {
            printf("A plataforma '%s' ja esta cadastrada.\n", nome);
            plataforma_existente = 1;
        }
        temp = temp->proximo;
    }

    if (!plataforma_existente) {
        struct Plataforma *novo = (struct Plataforma *)malloc(sizeof(Plataforma));
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


Plataforma *buscar_plataforma(Plataforma *plataformas, const char nome_plataforma[]) {
    Plataforma *encontrou = NULL; // Inicializa a variável encontrou como NULL

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
struct Podcast *cria_podcast(char nome[100], char entrevistado[100]) {
    struct Podcast *novo = (struct Podcast *)malloc(sizeof(Podcast));
    if (novo != NULL) {
        strcpy(novo->nome, nome);
        strcpy(novo->entrevistado, entrevistado);
        novo->temas = NULL;
        novo->esq = NULL;
        novo->dir = NULL;
    }
    return novo;
}

//Função para inserir um podcast na arvore
void insere_Podcast(struct Podcast **raiz, char nome[100], char entrevistado[100]) {
    if (*raiz == NULL) {
        *raiz = cria_podcast(nome, entrevistado);
        printf("Podcast '%s' cadastrado com sucesso!\n", nome);
    } else {
        int comparacao = strcmp(nome, (*raiz)->nome);
        if (comparacao < 0) {
            insere_Podcast(&(*raiz)->esq, nome, entrevistado);
        } else if (comparacao > 0) {
            insere_Podcast(&(*raiz)->dir, nome, entrevistado);
        } else {
            // Caso o nome já exista, imprime uma mensagem
            printf("Nao e possivel cadastrar o podcast '%s' novamente na mesma plataforma.\n", nome);
        }
    }
}

// Função para buscar um podcast em uma árvore binária de podcasts
struct Podcast *buscar_Podcast(struct Podcast *raiz, const char nome_podcast[]) {
    struct Podcast *encontrou = NULL; // Inicializa a variável encontrou como NULL

    if (raiz != NULL) {

        if (strcmp(raiz->nome, nome_podcast) == 0) {
            encontrou = raiz;
        } else if (strcmp(nome_podcast, raiz->nome) < 0) {
            encontrou = buscar_Podcast(raiz->esq, nome_podcast);
        } else {
            encontrou = buscar_Podcast(raiz->dir, nome_podcast);
        }
    }

    return encontrou; // Retorna o resultado encontrado
}


void limparMemoria_Podcast(Podcast *raiz) {
    if (raiz != NULL) {
        limparMemoria_Podcast(raiz->esq);
        limparMemoria_Podcast(raiz->dir);
        free(raiz);
    }
}

void limparMemoria_Plataforma(Plataforma *plataformas) {
    while (plataformas != NULL) {
        limparMemoria_Podcast(plataformas->podcasts);
        Plataforma *temp_plataforma = plataformas;
        plataformas = plataformas->proximo;
        free(temp_plataforma);
    }
}

void imprimir_Podcasts(Podcast *raiz) {
    if (raiz != NULL) {
        imprimir_Podcasts(raiz->esq);
        printf(" - Podcast: %s, Entrevistado: %s\n", raiz->nome, raiz->entrevistado);
        imprimir_Podcasts(raiz->dir);
    }
}

void imprimir_Plataformas(Plataforma *plataforma_atual) {

   if (plataforma_atual != NULL) {

      printf("\nPlataforma: %s\n", plataforma_atual->nome);

      imprimir_Plataformas(plataforma_atual->proximo);
   }
    
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
    } else {
      if (strcmp(tema,(*raiz)->nome) < 0)
         (*raiz)->esq = inserirTema(&((*raiz)->esq), tema);
      else if (strcmp(tema, (*raiz)->nome) > 0)
         (*raiz)->dir = inserirTema(&((*raiz)->dir), tema);
        
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

ArvMatricula *buscar_Tema(struct ArvMatricula *raiz, const char nome_tema[]){
    struct ArvMatricula *encontrou = NULL; // Inicializa a variável encontrou como NULL

    if (raiz != NULL) {

        if (strcmp(raiz->nome, nome_tema) == 0) {
            encontrou = raiz;
        } else if (strcmp(nome_tema, raiz->nome) < 0) {
            encontrou = buscar_Tema(raiz->esq, nome_tema);
        } else {
            encontrou = buscar_Tema(raiz->dir, nome_tema);
        }
    }

    return encontrou; // Retorna o resultado encontrado
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
        printf("Entrevista '%s' cadastrado com sucesso!\n", tituloEntrevista);
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


int verificarFolhaEntrevista(Entrevista *no) {
    return (no->esq == NULL && no->dir == NULL);
}


Entrevista *obterUnicoFilhoEntrevista(Entrevista *no) {
    if (no->esq != NULL && no->dir == NULL)
        return no->esq;
    else if (no->dir != NULL && no->esq == NULL)
        return no->dir;
    else
        return NULL;
}


Entrevista *encontrarMaiorDireitaEntrevista(Entrevista *no) {
    // Se não houver um filho à direita, este nó é o maior
    if (no->dir == NULL)
        return no;
    
    // Chamada recursiva para o filho à direita
    return encontrarMaiorDireitaEntrevista(no->dir);
}


int removerEntrevista(Entrevista **raiz, const char tituloEntrevista[]) {
    int remove = 0;
    Entrevista *maior = NULL;

    if (*raiz != NULL) {

        if (strcmp((*raiz)->titulo_da_entrevista, tituloEntrevista) == 0) {
            Entrevista *Aux, *filho;

            if (verificarFolhaEntrevista(*raiz)) {
                Aux = *raiz;
                *raiz = NULL;
                free(Aux);
            } else if ((filho = obterUnicoFilhoEntrevista(*raiz)) != NULL) {
                // OBS: Se a função tiver dois filhos ela tem que retornar NULL.
                Aux = *raiz;
                *raiz = filho;
                free(Aux);
            } else {
                Aux = *raiz;
                maior = encontrarMaiorDireitaEntrevista((*raiz)->esq);
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


void limpa_temas(ArvMatricula *raiz) {
    if (raiz != NULL) {
        limpa_temas(raiz->esq);
        limpa_temas(raiz->dir);
        free(raiz);
    }
}

void limpaMemoria_entrevistas(Entrevista *raiz) {
    if (raiz != NULL) {
        limpaMemoria_entrevistas(raiz->esq);
        limpaMemoria_entrevistas(raiz->dir);
        free(raiz);
    }
}



void exibir_menu() {
    printf("\n=== Menu de Cadastro ===\n");
    printf("1. Cadastrar plataforma\n");
    printf("2. Cadastrar podcast\n");
    printf("3. Exibir plataformas e podcasts cadastrados.\n");
    printf("4. Mostrar todos os temas de um PodCast de uma plataforma.\n");
    printf("5. Mostrar todos os títulos das entrevistas de um PodCast de uma plataforma dado o tema.\n");
    
    printf("0. Sair\n");
    printf("Digite a opcao desejada: ");
}