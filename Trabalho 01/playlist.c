#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definindo tipos com typedef para simplificar
typedef struct Playlist {
    char name[100];
    struct Music *tracks;  
}Playlist;

typedef struct ArvPlaylist {
    Playlist info;
    struct ArvPlaylist *left, *right;
} ArvPlaylist;


typedef struct Library {
    ArvPlaylist *playlists;   // Árvore de playlists
} Library;

// Protótipos das funções
void initializeLibrary(Library **library);
ArvPlaylist *criaNo_Playlist(char title[]);
int insertPlaylist
(ArvPlaylist **rt, char title[]);
void printPlaylists(ArvPlaylist *rt);
ArvPlaylist* searchPlaylist(ArvPlaylist *rt, char nameBusc[]);
int isPlaylistLeaf(ArvPlaylist *rt);
ArvPlaylist *getPlaylistSingleChild(ArvPlaylist *rt);
ArvPlaylist *findPlaylistMaxRight(ArvPlaylist *rt);
int removePlaylist(ArvPlaylist **rt, char playlistTitle[]) ;

void liberaArvPlaylist(ArvPlaylist **rt);

void liberaLibrary(Library **library);

int main() {
    Library *myLibrary = NULL;
    initializeLibrary(&myLibrary);

    insertPlaylist(&(myLibrary->playlists), "Rock Classics");
    insertPlaylist(&(myLibrary->playlists), "Pop Hits");
    insertPlaylist(&(myLibrary->playlists), "Indie Vibes");
    insertPlaylist(&(myLibrary->playlists), "Jazz Essentials");

    printf("\nPlaylists na Biblioteca (em ordem):\n");
    printPlaylists(myLibrary->playlists);

    // Buscando uma playlist
    char busca[] = "Indie Vibes";
    ArvPlaylist *encontrada = searchPlaylist(myLibrary->playlists, busca);
    if (encontrada) {
        printf("\nPlaylist encontrada: %s\n", encontrada->info.name);
    } else {
        printf("\nPlaylist '%s' não encontrada.\n", busca);
    }

    // Removendo uma playlist
    char remover[] = "Pop Hits";
    printf("\nRemovendo a playlist: %s\n", remover);
    if (removePlaylist(&(myLibrary->playlists), remover)) {
        printf("Playlist removida com sucesso.\n");
    } else {
        printf("Falha ao remover playlist.\n");
    }

    printf("\nPlaylists após remoção:\n");
    printPlaylists(myLibrary->playlists);

    // Liberando memória
    liberaLibrary(&myLibrary);


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

    (*library)->playlists = NULL;
}

// Função para criar um nó de artista
ArvPlaylist *criaNo_Playlist(char title[]) {
    ArvPlaylist *novo_no = (ArvPlaylist *)malloc(sizeof(ArvPlaylist));
    if (novo_no == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    strncpy(novo_no->info.name, title, sizeof(novo_no->info.name) - 1);
    novo_no->info.name[sizeof(novo_no->info.name) - 1] = '\0'; // Garantir terminação.

    novo_no->left = NULL;
    novo_no->right = NULL;

    return novo_no;
}

// Função para inserir um artista na árvore
int insertPlaylist(ArvPlaylist **rt, char title[]) {
    int inseriu = 1;
    
    if (*rt == NULL) {
        *rt = criaNo_Playlist(title);
    }else if (strcmp((*rt)->info.name, title) > 0) {
        inseriu = insertPlaylist
        (&((*rt))->left, title);
    }else if (strcmp((*rt)->info.name, title) < 0) {
        inseriu = insertPlaylist
        (&((*rt))->right, title);
    } else {
        inseriu = 0;
    }

    return inseriu;
}

// Função para mostrar os artistas (em-ordem)
void printPlaylists(ArvPlaylist *rt) {
    if (rt != NULL) {
        printPlaylists(rt->left);
        printf("Music title: %s\n", rt->info.name);
        printPlaylists(rt->right);
    }
}


ArvPlaylist* searchPlaylist(ArvPlaylist *rt, char nameBusc[]) {
    ArvPlaylist *encontrou;
    encontrou = NULL;

    if (rt != NULL) {
        int cmp = strcmp(rt->info.name, nameBusc);
        if(cmp == 0){
            encontrou = rt;
        } else if (cmp > 0){
            encontrou = searchPlaylist(rt->left, nameBusc);
        } else {
            encontrou = searchPlaylist(rt->right, nameBusc);
        }
    }

    return encontrou;
}


int isPlaylistLeaf(ArvPlaylist *rt) {
    return (rt->left == NULL && rt->right == NULL);
}


ArvPlaylist *getPlaylistSingleChild(ArvPlaylist *rt) {
    if (rt->left != NULL && rt->right == NULL)
        return rt->left;
    else if (rt->right != NULL && rt->left == NULL)
        return rt->right;
    else
        return NULL;
}
ArvPlaylist *findPlaylistMaxRight(ArvPlaylist *rt) {
    // Se não houver um filho à direita, este nó é o maior
    if (rt->right == NULL)
        return rt;

    // Chamada recursiva para o filho à direita
    return findPlaylistMaxRight(rt->right);
}


int removePlaylist(ArvPlaylist **rt, char playlistTitle[]) {
    int remove = 1;
    ArvPlaylist *maior = NULL;

    if (*rt != NULL) {

        if (strcmp((*rt)->info.name, playlistTitle) == 0) {
            ArvPlaylist *Aux, *filho;

            Aux = *rt;
            if (isPlaylistLeaf(*rt)) {
                *rt = NULL;
            } else if ((filho = getPlaylistSingleChild(*rt)) != NULL) {
                // OBS: Se a função tiver dois filhos ela tem que retornar NULL.
                *rt = filho;
            } else {
                maior = findPlaylistMaxRight((*rt)->left);
                strcpy((*rt)->info.name, maior->info.name);
                removePlaylist(&((*rt)->left), maior->info.name);
                
            }
            free(Aux);
        } else if (strcmp(playlistTitle, (*rt)->info.name) < 0) {
            remove = removePlaylist(&((*rt)->left), playlistTitle);
        } else {
            remove = removePlaylist(&((*rt)->right), playlistTitle);
        }

    } else {
        remove = 0;
    }
    return remove;
}

void liberaArvPlaylist(ArvPlaylist **rt) {
    if (*rt != NULL) {
        liberaArvPlaylist(&(*rt)->left);
        liberaArvPlaylist(&(*rt)->right);
        free(*rt);
        *rt = NULL; // Define o ponteiro como NULL após liberar a memória
    }
}

// Função para liberar a memória da biblioteca

void liberaLibrary(Library **library) {
    if (*library != NULL) {
        liberaArvPlaylist(&(*library)->playlists);
        // Adicione funções para liberar playlists e outras estruturas
        free(*library);
        *library = NULL; // Define o ponteiro como NULL após liberar a memória
    }
}