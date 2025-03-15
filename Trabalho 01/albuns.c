#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definindo tipos com typedef para simplificar

typedef struct Album {
    char title[100];
    int year;
    int track_count;
   // Arv_Music *tracks;  // Árvore de músicas
    struct Album *left, *right;
} Album;


typedef struct ArvAlbum {
    Album info;
    struct ArvAlbum *left, *right;
} ArvAlbum;


typedef struct Playlist {
    char name[100];
    //Arv_Song *tracks;  // Árvore de músicas
    struct Playlist *left, *right;
} Playlist;

typedef struct Library {
    ArvAlbum *albuns;    // Árvore de artistas
    Playlist *playlists;   // Árvore de playlists
} Library;

// Protótipos das funções
void initializeLibrary(Library **library);
ArvAlbum *criaNo_Album(char title[], int year, int track_count);
int insertAlbum
(ArvAlbum **rt, char title[], int year, int track_count);
void printAlbums(ArvAlbum *rt);

int isAlbumLeaf(ArvAlbum *rt);
ArvAlbum *getAlbumSingleChild(ArvAlbum *rt);
ArvAlbum *findAlbumMaxRight(ArvAlbum *rt);
int removeAlbum(ArvAlbum **rt, char albumTitle[]) ;
void liberaArvAlbum(ArvAlbum **rt);
void liberaLibrary(Library **library);

int main() {
    Library *myLibrary = NULL;
    initializeLibrary(&myLibrary);

    if (myLibrary->albuns == NULL && myLibrary->playlists == NULL) {
        printf("Library initialized successfully! Trees are empty.\n");
    } else {
        printf("Error initializing the library.\n");
    }

    insertAlbum(&myLibrary->albuns, "Divide", 2017, 12);
    insertAlbum(&myLibrary->albuns, "Folklore", 2020, 16);
    insertAlbum(&myLibrary->albuns, "Evermore", 2020, 15);
    insertAlbum(&myLibrary->albuns, "Future Nostalgia", 2020, 11);

    printf("\nÁlbuns na biblioteca:\n");
    printAlbums(myLibrary->albuns);

    // Removendo um álbum
    int test;
    printf("\nRemovendo 'Evermore'...\n");
    test = removeAlbum(&myLibrary->albuns, "Evermore");
    printf("A remocao: %d\n", test);

    
    printf("\nÁlbuns após remoção:\n");

    test = removeAlbum(&myLibrary->albuns, "Evermore");
    printf("A remocao: %d\n", test);
    printAlbums(myLibrary->albuns);

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

    (*library)->albuns = NULL;
    (*library)->playlists = NULL;
}

// Função para criar um nó de artista
ArvAlbum *criaNo_Album(char title[], int year, int track_count) {
    ArvAlbum *novo_no = (ArvAlbum *)malloc(sizeof(ArvAlbum));
    if (novo_no == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    strncpy(novo_no->info.title, title, sizeof(novo_no->info.title) - 1);
    novo_no->info.title[sizeof(novo_no->info.title) - 1] = '\0'; // Garantir terminação.

    novo_no->info.year = year;
    novo_no->info.track_count = track_count;

    novo_no->left = NULL;
    novo_no->right = NULL;

    return novo_no;
}

// Função para inserir um artista na árvore
int insertAlbum(ArvAlbum **rt, char title[], int year, int track_count) {
    int inseriu = 1;
    
    if (*rt == NULL) {
        *rt = criaNo_Album(title, year, track_count);
    }else if (strcmp((*rt)->info.title, title) > 0) {
        inseriu = insertAlbum
        (&((*rt))->left, title, year, track_count);
    }else if (strcmp((*rt)->info.title, title) < 0) {
        inseriu = insertAlbum
        (&((*rt))->right, title, year, track_count);
    } else {
        inseriu = 0;
    }

    return inseriu;
}

// Função para mostrar os artistas (em-ordem)
void printAlbums(ArvAlbum *rt) {
    if (rt != NULL) {
        printAlbums(rt->left);
        printf("Album title: %s, Year: %d, Track count: %d\n", rt->info.title, rt->info.year, rt->info.track_count);
        printAlbums(rt->right);
    }
}

ArvAlbum* buscarArtistas(ArvAlbum *rt, char nameBusc[]) {
    ArvAlbum *encontrou;
    encontrou = NULL;

    if (rt != NULL) {
        int cmp = strcmp(rt->info.title, nameBusc);
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


int isAlbumLeaf(ArvAlbum *rt) {
    return (rt->left == NULL && rt->right == NULL);
}


ArvAlbum *getAlbumSingleChild(ArvAlbum *rt) {
    if (rt->left != NULL && rt->right == NULL)
        return rt->left;
    else if (rt->right != NULL && rt->left == NULL)
        return rt->right;
    else
        return NULL;
}
ArvAlbum *findAlbumMaxRight(ArvAlbum *rt) {
    // Se não houver um filho à direita, este nó é o maior
    if (rt->right == NULL)
        return rt;
    
    // Chamada recursiva para o filho à direita
    return findAlbumMaxRight(rt->right);
}


int removeAlbum(ArvAlbum **rt, char albumTitle[]) {
    int remove = 1;
    ArvAlbum *maior = NULL;

    if (*rt != NULL) {

        if (strcmp((*rt)->info.title, albumTitle) == 0) {
            ArvAlbum *Aux, *filho;

            Aux = *rt;
            if (isAlbumLeaf(*rt)) {
                *rt = NULL;
            } else if ((filho = getAlbumSingleChild(*rt)) != NULL) {
                // OBS: Se a função tiver dois filhos ela tem que retornar NULL.
                *rt = filho;
            } else {
                maior = findAlbumMaxRight((*rt)->left);
                strcpy((*rt)->info.title, maior->info.title);
                removeAlbum(&((*rt)->left), maior->info.title);
                
            }
            free(Aux);
        } else if (strcmp(albumTitle, (*rt)->info.title) < 0) {
            remove = removeAlbum(&((*rt)->left), albumTitle);
        } else {
            remove = removeAlbum(&((*rt)->right), albumTitle);
        }

    } else {
        remove = 0;
    }
    return remove;
}


// Função para liberar a memória da árvore de artistas
void liberaArvAlbum(ArvAlbum **rt) {
    if (*rt != NULL) {
        liberaArvAlbum(&(*rt)->left);
        liberaArvAlbum(&(*rt)->right);
        free(*rt);
        *rt = NULL; // Define o ponteiro como NULL após liberar a memória
    }
}

// Função para liberar a memória da biblioteca
void liberaLibrary(Library **library) {
    if (*library != NULL) {
        liberaArvAlbum(&(*library)->albuns);
        // Adicione funções para liberar playlists e outras estruturas
        free(*library);
        *library = NULL; // Define o ponteiro como NULL após liberar a memória
    }
}