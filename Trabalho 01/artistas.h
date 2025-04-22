#ifndef ARTISTA_H
#define ARTISTA_H

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

typedef struct ArvAlbum {
   Artist info;
   struct ArvAlbum *left, *right;
} ArvAlbum;


// Protótipos das funções
ArvAlbum *criaNo_Artist(char name[], char type[], char genre[], int album_count);
int insere(ArvAlbum **rt, char name[], char type[], char genre[], int album_count);
void mostrarArtistas(ArvAlbum *rt);
int verificarFolha(ArvAlbum *rt);
ArvAlbum *obterUnicoFilho(ArvAlbum *rt);
ArvAlbum *encontrarMaiorDireita(ArvAlbum *rt);
int removerArtista(ArvAlbum **rt, char tituloEntrevista[]) ;
void liberaArvArtist(ArvAlbum **rt);


#endif 