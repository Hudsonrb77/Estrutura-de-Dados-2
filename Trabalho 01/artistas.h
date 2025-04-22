#ifndef ARTISTA_H
#define ARTISTA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "albuns.h"


// Definindo tipos com typedef para simplificar
typedef struct Artist {
   char name[100];
   char type[50];   // Singer, duo, band, etc.
   char genre[50];
   int album_count;
   ArvAlbum albuns;

} Artist;

typedef struct ArvArtist {
   Artist info;
   struct ArvArtist *left, *right;
} ArvArtist;


// Protótipos das funções
ArvArtist *criaNo_Artist(char name[], char type[], char genre[], int album_count);
int insere(ArvArtist **rt, char name[], char type[], char genre[], int album_count);
void mostrarArtistas(ArvArtist *rt);
int verificarFolha(ArvArtist *rt);
ArvArtist *obterUnicoFilho(ArvArtist *rt);
ArvArtist *encontrarMaiorDireita(ArvArtist *rt);
int removerArtista(ArvArtist **rt, char tituloEntrevista[]) ;
void liberaArvArtist(ArvArtist **rt);


#endif 