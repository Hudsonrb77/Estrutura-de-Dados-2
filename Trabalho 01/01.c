#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definindo tipos com typedef para simplificar

typedef struct Artist {
    char name[100];
    char type[50];   // Singer, duo, band, etc.
    char genre[50];
    int album_count;
    struct Artist *left, *right;
} Artist;

typedef struct ArvArtist {
    Artist info;
    struct ArvArtist *left, *right;
} ArvArtist;

typedef struct Playlist {
    char name[100];
    //Arv_Music *tracks;   Árvore de músicas
    struct Playlist *left, *right;
} Playlist;

typedef struct Library {
    ArvArtist *artists;    // Árvore de artistas
    Playlist *playlists;   // Árvore de playlists
} Library;

// Protótipos das funções
void initializeLibrary(Library **library);
ArvArtist *criaNo_Artist(char name[], char type[], char genre[], int album_count);
int insere(ArvArtist **rt, char name[], char type[], char genre[], int album_count);
void mostrarArtistas(ArvArtist *rt);
int verificarFolha(ArvArtist *rt);
ArvArtist *obterUnicoFilho(ArvArtist *rt);
ArvArtist *encontrarMaiorDireita(ArvArtist *rt);
int removerArtista(ArvArtist **rt, char tituloEntrevista[]) ;
void liberaArvArtist(ArvArtist **rt);
void liberaLibrary(Library **library);

int main() {
    Library *myLibrary = NULL;
    initializeLibrary(&myLibrary);

    if (myLibrary->artists == NULL && myLibrary->playlists == NULL) {
        printf("Library initialized successfully! Trees are empty.\n");
    } else {
        printf("Error initializing the library.\n");
    }

    // Inserindo artistas
    insere(&myLibrary->artists, "Artist 1", "Singer", "Pop", 5);
    insere(&myLibrary->artists, "Artist 2", "Band", "Rock", 3);
    insere(&myLibrary->artists, "Artist 3", "Band", "Funk", 3);
    insere(&myLibrary->artists, "Skillet", "Band", "Rock", 7);

    // Mostrando artistas
    printf("\nArtists in the library:\n");
    mostrarArtistas(myLibrary->artists);

    removerArtista(&myLibrary->artists,"Artist 3");
    printf("\nApos remover o Artist 3\n");
    mostrarArtistas(myLibrary->artists);

    removerArtista(&myLibrary->artists,"Artist 2");
    printf("\nApos remover o Artist 2\n");
    mostrarArtistas(myLibrary->artists);

    removerArtista(&myLibrary->artists,"Artist 1");
    printf("\nApos remover o Artist 1\n");
    mostrarArtistas(myLibrary->artists);

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

    (*library)->artists = NULL;
    (*library)->playlists = NULL;
}

// Função para criar um nó de artista
ArvArtist *criaNo_Artist(char name[], char type[], char genre[], int album_count) {
    ArvArtist *novo_no = (ArvArtist *)malloc(sizeof(ArvArtist));
    if (novo_no == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    strncpy(novo_no->info.name, name, sizeof(novo_no->info.name) - 1);
    novo_no->info.name[sizeof(novo_no->info.name) - 1] = '\0'; // Garantir terminação.

    strncpy(novo_no->info.type, type, sizeof(novo_no->info.type) - 1);
    novo_no->info.type[sizeof(novo_no->info.type) - 1] = '\0';

    strncpy(novo_no->info.genre, genre, sizeof(novo_no->info.genre) - 1);
    novo_no->info.genre[sizeof(novo_no->info.genre) - 1] = '\0';

    novo_no->info.album_count = album_count;

    novo_no->left = NULL;
    novo_no->right = NULL;

    return novo_no;
}

// Função para inserir um artista na árvore
int insere(ArvArtist **rt, char name[], char type[], char genre[], int album_count) {
    int inseriu = 1;
    
    if (*rt == NULL) {
        *rt = criaNo_Artist(name, type, genre, album_count);
    }else if (strcmp((*rt)->info.name, name) > 0) {
        inseriu = insere(&((*rt))->left, name, type, genre, album_count);
    }else if (strcmp((*rt)->info.name, name) < 0) {
        inseriu = insere(&((*rt))->right, name, type, genre, album_count);
    } else {
        inseriu = 0;
    }

    return inseriu;
}

// Função para mostrar os artistas (em-ordem)
void mostrarArtistas(ArvArtist *rt) {
    if (rt != NULL) {
        mostrarArtistas(rt->left);
        printf("Artist: %s, Type: %s, Genre: %s, Albums: %d\n",
               rt->info.name, rt->info.type, rt->info.genre, rt->info.album_count);
        mostrarArtistas(rt->right);
    }
}

ArvArtist* buscarArtistas(ArvArtist *rt, char nameBusc[]) {
    ArvArtist *encontrou;
    encontrou = NULL;

    if (rt != NULL) {
        int cmp = strcmp(rt->info.name, nameBusc);
        if(cmp == 0){
            encontrou = rt;
        } else if (cmp > 0){
            encontrou = buscarArtistas(rt->left, nameBusc);
        } else {
            encontrou = buscarArtistas(rt->right, nameBusc);
        }
    }

    return encontrou;
}


int verificarFolha(ArvArtist *rt) {
    return (rt->left == NULL && rt->right == NULL);
}


ArvArtist *obterUnicoFilho(ArvArtist *rt) {
    if (rt->left != NULL && rt->right == NULL)
        return rt->left;
    else if (rt->right != NULL && rt->left == NULL)
        return rt->right;
    else
        return NULL;
}
ArvArtist *encontrarMaiorDireita(ArvArtist *rt) {
    // Se não houver um filho à direita, este nó é o maior
    if (rt->right == NULL)
        return rt;
    
    // Chamada recursiva para o filho à direita
    return encontrarMaiorDireita(rt->right);
}


int removerArtista(ArvArtist **rt, char tituloEntrevista[]) {
    int remove = 1;
    ArvArtist *maior = NULL;

    if (*rt != NULL) {

        if (strcmp((*rt)->info.name, tituloEntrevista) == 0) {
            ArvArtist *Aux, *filho;

            Aux = *rt;
            if (verificarFolha(*rt)) {
                *rt = NULL;
            } else if ((filho = obterUnicoFilho(*rt)) != NULL) {
                // OBS: Se a função tiver dois filhos ela tem que retornar NULL.
                *rt = filho;
            } else {
                maior = encontrarMaiorDireita((*rt)->left);
                strcpy((*rt)->info.name, maior->info.name);
                removerArtista(&((*rt)->left), maior->info.name);
                
            }
            free(Aux);
        } else if (strcmp(tituloEntrevista, (*rt)->info.name) < 0) {
            remove = removerArtista(&((*rt)->left), tituloEntrevista);
        } else {
            remove = removerArtista(&((*rt)->right), tituloEntrevista);
        }

    } else {
        remove = 0;
    }
    return remove;
}


// Função para liberar a memória da árvore de artistas
void liberaArvArtist(ArvArtist **rt) {
    if (*rt != NULL) {
        liberaArvArtist(&(*rt)->left);
        liberaArvArtist(&(*rt)->right);
        free(*rt);
        *rt = NULL; // Define o ponteiro como NULL após liberar a memória
    }
}

// Função para liberar a memória da biblioteca
void liberaLibrary(Library **library) {
    if (*library != NULL) {
        liberaArvArtist(&(*library)->artists);
        // Adicione funções para liberar playlists e outras estruturas
        free(*library);
        *library = NULL; // Define o ponteiro como NULL após liberar a memória
    }
}