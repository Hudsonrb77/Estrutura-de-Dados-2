#ifndef ALBUM_H
#define ALBUM_H

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


typedef struct ArvArtist {
    Album info;
    struct ArvArtist *left, *right;
} ArvArtist;

// Protótipos das funções
// Função para inicializar a biblioteca

// Função para criar um nó de artista
ArvArtist *criaNo_Album(char title[], int year, int track_count) {
    ArvArtist *novo_no = (ArvArtist *)malloc(sizeof(ArvArtist));
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
int insertAlbum(ArvArtist **rt, char title[], int year, int track_count) {
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
void printAlbums(ArvArtist *rt) {
    if (rt != NULL) {
        printAlbums(rt->left);
        printf("Album title: %s, Year: %d, Track count: %d\n", rt->info.title, rt->info.year, rt->info.track_count);
        printAlbums(rt->right);
    }
}

ArvArtist* buscarArtistas(ArvArtist *rt, char nameBusc[]) {
    ArvArtist *encontrou;
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


int isAlbumLeaf(ArvArtist *rt) {
    return (rt->left == NULL && rt->right == NULL);
}


ArvArtist *getAlbumSingleChild(ArvArtist *rt) {
    if (rt->left != NULL && rt->right == NULL)
        return rt->left;
    else if (rt->right != NULL && rt->left == NULL)
        return rt->right;
    else
        return NULL;
}
ArvArtist *findAlbumMaxRight(ArvArtist *rt) {
    // Se não houver um filho à direita, este nó é o maior
    if (rt->right == NULL)
        return rt;
    
    // Chamada recursiva para o filho à direita
    return findAlbumMaxRight(rt->right);
}


int removeAlbum(ArvArtist **rt, char albumTitle[]) {
    int remove = 1;
    ArvArtist *maior = NULL;

    if (*rt != NULL) {

        if (strcmp((*rt)->info.title, albumTitle) == 0) {
            ArvArtist *Aux, *filho;

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
void liberaArvAlbum(ArvArtist **rt) {
    if (*rt != NULL) {
        liberaArvAlbum(&(*rt)->left);
        liberaArvAlbum(&(*rt)->right);
        free(*rt);
        *rt = NULL; // Define o ponteiro como NULL após liberar a memória
    }
}

#endif