#ifndef PLAYLIST_H
#define PLAYLIST_H

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

// Protótipos das funções
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
#endif