#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definindo tipos com typedef para simplificar

// Music Structure
typedef struct Music {
    char titleMusic[100];
    float duration;
}Music;

typedef struct ArvMusic {
    Music info;
    struct ArvMusic *left, *right;
} ArvMusic;


typedef struct Playlist {
    char name[100];
    //Arv_Song *tracks;  // Árvore de músicas
    struct Playlist *left, *right;
} Playlist;

typedef struct Library {
    ArvMusic *musicas;    // Árvore de artistas
    Playlist *playlists;   // Árvore de playlists
} Library;

// Protótipos das funções
void initializeLibrary(Library **library);
ArvMusic *criaNo_Music(char title[], float duration);
int insertMusic
(ArvMusic **rt, char title[], float duration);
void printMusic(ArvMusic *rt);
ArvMusic* buscarMusicas(ArvMusic *rt, char nameBusc[]);
int isMusicLeaf(ArvMusic *rt);
ArvMusic *getMusicSingleChild(ArvMusic *rt);
ArvMusic *findMusicMaxRight(ArvMusic *rt);
int removeMusic(ArvMusic **rt, char musicTitle[]) ;
void liberaArvMusic(ArvMusic **rt);
void liberaLibrary(Library **library);

int main() {
    Library *myLibrary = NULL;
    initializeLibrary(&myLibrary);

    if (myLibrary == NULL) {
        printf("Falha ao inicializar a biblioteca.\n");
        return 1;
    }

    printf("Library inicializada com sucesso!\n");

    // Inserindo músicas reais na árvore
    insertMusic(&(myLibrary->musicas), "Shivers", 3.27);  // Ed Sheeran
    insertMusic(&(myLibrary->musicas), "Drivers License", 4.02);  // Olivia Rodrigo
    insertMusic(&(myLibrary->musicas), "Blinding Lights", 3.20);  // The Weeknd
    insertMusic(&(myLibrary->musicas), "Peaches", 3.18);  // Justin Bieber

    printf("\nLista de músicas após inserção:\n");
    printMusic(myLibrary->musicas);

    // Testando busca por uma música existente
    char searchTitle[] = "Blinding Lights";
    ArvMusic *found = buscarMusicas(myLibrary->musicas, searchTitle);
    if (found != NULL) {
        printf("\nMúsica encontrada: %s, Duração: %.2f minutos\n", found->info.titleMusic, found->info.duration);
    } else {
        printf("\nMúsica '%s' não encontrada.\n", searchTitle);
    }

    // Testando remoção de uma música
    char removeTitle[] = "Pesaches";
    if (removeMusic(&(myLibrary->musicas), removeTitle)) {
        printf("\nMúsica '%s' removida com sucesso!\n", removeTitle);
    } else {
        printf("\nFalha ao remover '%s', música não encontrada.\n", removeTitle);
    }

    // Imprimindo novamente após remoção
    printf("\nLista de músicas após remoção:\n");
    printMusic(myLibrary->musicas);

    // Liberando memória
    liberaLibrary(&myLibrary);

    return 0;
}

// Função para inicializar a biblioteca
void initializeLibrary(Library **library) {
    *library = (Library *)malloc(sizeof(Library));
    if (*library == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    (*library)->musicas = NULL;
    (*library)->playlists = NULL;
}

// Função para criar um nó de artista
ArvMusic *criaNo_Music(char title[], float duration) {
    ArvMusic *novo_no = (ArvMusic *)malloc(sizeof(ArvMusic));
    if (novo_no == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    strncpy(novo_no->info.titleMusic, title, sizeof(novo_no->info.titleMusic) - 1);
    novo_no->info.titleMusic[sizeof(novo_no->info.titleMusic) - 1] = '\0'; // Garantir terminação.

    novo_no->info.duration = duration;

    novo_no->left = NULL;
    novo_no->right = NULL;

    return novo_no;
}

// Função para inserir um artista na árvore
int insertMusic(ArvMusic **rt, char title[], float duration) {
    int inseriu = 1;
    
    if (*rt == NULL) {
        *rt = criaNo_Music(title, duration);
    }else if (strcmp((*rt)->info.titleMusic, title) > 0) {
        inseriu = insertMusic
        (&((*rt))->left, title, duration);
    }else if (strcmp((*rt)->info.titleMusic, title) < 0) {
        inseriu = insertMusic
        (&((*rt))->right, title, duration);
    } else {
        inseriu = 0;
    }

    return inseriu;
}

// Função para mostrar os artistas (em-ordem)
void printMusic(ArvMusic *rt) {
    if (rt != NULL) {
        printMusic(rt->left);
        printf("Music title: %s, Duration: %.2f\n", rt->info.titleMusic, rt->info.duration);
        printMusic(rt->right);
    }
}

ArvMusic* buscarMusicas(ArvMusic *rt, char nameBusc[]) {
    ArvMusic *encontrou;
    encontrou = NULL;

    if (rt != NULL) {
        int cmp = strcmp(rt->info.titleMusic, nameBusc);
        if(cmp == 0){
            encontrou = rt;
        } else if (cmp > 0){
            encontrou = buscarMusicas(rt->left, nameBusc);
        } else {
            encontrou = buscarMusicas(rt->right, nameBusc);
        }
    }

    return encontrou;
}


int isMusicLeaf(ArvMusic *rt) {
    return (rt->left == NULL && rt->right == NULL);
}


ArvMusic *getMusicSingleChild(ArvMusic *rt) {
    if (rt->left != NULL && rt->right == NULL)
        return rt->left;
    else if (rt->right != NULL && rt->left == NULL)
        return rt->right;
    else
        return NULL;
}
ArvMusic *findMusicMaxRight(ArvMusic *rt) {
    // Se não houver um filho à direita, este nó é o maior
    if (rt->right == NULL)
        return rt;
    
    // Chamada recursiva para o filho à direita
    return findMusicMaxRight(rt->right);
}


int removeMusic(ArvMusic **rt, char musicTitle[]) {
    int remove = 1;
    ArvMusic *maior = NULL;

    if (*rt != NULL) {

        if (strcmp((*rt)->info.titleMusic, musicTitle) == 0) {
            ArvMusic *Aux, *filho;

            Aux = *rt;
            if (isMusicLeaf(*rt)) {
                *rt = NULL;
            } else if ((filho = getMusicSingleChild(*rt)) != NULL) {
                // OBS: Se a função tiver dois filhos ela tem que retornar NULL.
                *rt = filho;
            } else {
                maior = findMusicMaxRight((*rt)->left);
                strcpy((*rt)->info.titleMusic, maior->info.titleMusic);
                removeMusic(&((*rt)->left), maior->info.titleMusic);
                
            }
            free(Aux);
        } else if (strcmp(musicTitle, (*rt)->info.titleMusic) < 0) {
            remove = removeMusic(&((*rt)->left), musicTitle);
        } else {
            remove = removeMusic(&((*rt)->right), musicTitle);
        }

    } else {
        remove = 0;
    }
    return remove;
}


// Função para liberar a memória da árvore de artistas
void liberaArvMusic(ArvMusic **rt) {
    if (*rt != NULL) {
        liberaArvMusic(&(*rt)->left);
        liberaArvMusic(&(*rt)->right);
        free(*rt);
        *rt = NULL; // Define o ponteiro como NULL após liberar a memória
    }
}

// Função para liberar a memória da biblioteca
void liberaLibrary(Library **library) {
    if (*library != NULL) {
        liberaArvMusic(&(*library)->musicas);
        // Adicione funções para liberar playlists e outras estruturas
        free(*library);
        *library = NULL; // Define o ponteiro como NULL após liberar a memória
    }
}