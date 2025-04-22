#include "artistas.h"

typedef struct Playlist {
    char name[100];
    //Arv_Music *tracks;   Árvore de músicas
    struct Playlist *left, *right;
} Playlist;


// Protótipos das funções
ArvAlbum *criaNo_Artist(char name[], char type[], char genre[], int album_count);
int insere(ArvAlbum **rt, char name[], char type[], char genre[], int album_count);
void mostrarArtistas(ArvAlbum *rt);
int verificarFolha(ArvAlbum *rt);
ArvAlbum *obterUnicoFilho(ArvAlbum *rt);
ArvAlbum *encontrarMaiorDireita(ArvAlbum *rt);
int removerArtista(ArvAlbum **rt, char tituloEntrevista[]) ;
void liberaArvArtist(ArvAlbum **rt);

// Função para criar um nó de artista
ArvAlbum *criaNo_Artist(char name[], char type[], char genre[], int album_count) {
    ArvAlbum *novo_no = (ArvAlbum *)malloc(sizeof(ArvAlbum));
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
int insere(ArvAlbum **rt, char name[], char type[], char genre[], int album_count) {
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
void mostrarArtistas(ArvAlbum *rt) {
    if (rt != NULL) {
        mostrarArtistas(rt->left);
        printf("Artist: %s, Type: %s, Genre: %s, Albums: %d\n",
               rt->info.name, rt->info.type, rt->info.genre, rt->info.album_count);
        mostrarArtistas(rt->right);
    }
}

ArvAlbum* buscarArtistas(ArvAlbum *rt, char nameBusc[]) {
    ArvAlbum *encontrou;
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


int verificarFolha(ArvAlbum *rt) {
    return (rt->left == NULL && rt->right == NULL);
}


ArvAlbum *obterUnicoFilho(ArvAlbum *rt) {
    if (rt->left != NULL && rt->right == NULL)
        return rt->left;
    else if (rt->right != NULL && rt->left == NULL)
        return rt->right;
    else
        return NULL;
}
ArvAlbum *encontrarMaiorDireita(ArvAlbum *rt) {
    // Se não houver um filho à direita, este nó é o maior
    if (rt->right == NULL)
        return rt;
    
    // Chamada recursiva para o filho à direita
    return encontrarMaiorDireita(rt->right);
}


int removerArtista(ArvAlbum **rt, char tituloEntrevista[]) {
    int remove = 1;
    ArvAlbum *maior = NULL;

    if (*rt != NULL) {

        if (strcmp((*rt)->info.name, tituloEntrevista) == 0) {
            ArvAlbum *Aux, *filho;

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
void liberaArvArtist(ArvAlbum **rt) {
    if (*rt != NULL) {
        liberaArvArtist(&(*rt)->left);
        liberaArvArtist(&(*rt)->right);
        free(*rt);
        *rt = NULL; // Define o ponteiro como NULL após liberar a memória
    }
}

