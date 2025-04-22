#ifndef ALBUM_H
#define ALBUM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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


ArvAlbum *criaNo_Album(char title[], int year, int track_count);
int insertAlbum
(ArvAlbum **rt, char title[], int year, int track_count);
void printAlbums(ArvAlbum *rt);

int isAlbumLeaf(ArvAlbum *rt);
ArvAlbum *getAlbumSingleChild(ArvAlbum *rt);
ArvAlbum *findAlbumMaxRight(ArvAlbum *rt);
int removeAlbum(ArvAlbum **rt, char albumTitle[]) ;
void liberaArvAlbum(ArvAlbum **rt);





#endif