#ifndef MUSICA_H
#define MUSICA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Estrutura de uma música
typedef struct {
    char titleMusic[100];
    float duration;
} Music;

// Nó da árvore de músicas
typedef struct ArvMusic {
    Music info;
    struct ArvMusic *left, *right;
} ArvMusic;

// Protótipos das funções
ArvMusic *criaNo_Music(char title[], float duration);
int insertMusic(ArvMusic **rt, char title[], float duration);
void printMusic(ArvMusic *rt);
ArvMusic* buscarMusicas(ArvMusic *rt, char nameBusc[]);
int isMusicLeaf(ArvMusic *rt);
ArvMusic *getMusicSingleChild(ArvMusic *rt);
ArvMusic *findMusicMaxRight(ArvMusic *rt);
int removeMusic(ArvMusic **rt, char musicTitle[]);
void liberaArvMusic(ArvMusic **rt);

#endif // MUSICA_H