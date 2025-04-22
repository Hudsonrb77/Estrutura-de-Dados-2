#include <stdio.h>
#include "albuns.h"  // Inclui o cabeçalho com todas as declarações


typedef struct Library {
   ArvAlbum *album;   // Árvore de playlists
} Library;

// Protótipos das funções
void initializeLibrary(Library **library);
void liberaLibrary(Library **library);


int main() {
    Library *myLibrary = NULL;
    initializeLibrary(&myLibrary);

    if (myLibrary->album == NULL) {
        printf("Library initialized successfully! Trees are empty.\n");
    } else {
        printf("Error initializing the library.\n");
    }

    insertAlbum(&myLibrary->album, "Divide", 2017, 12);
    insertAlbum(&myLibrary->album, "Folklore", 2020, 16);
    insertAlbum(&myLibrary->album, "Evermore", 2020, 15);
    insertAlbum(&myLibrary->album, "Future Nostalgia", 2020, 11);

    printf("\nÁlbuns na biblioteca:\n");
    printAlbums(myLibrary->album);

    // Removendo um álbum
    int test;
    printf("\nRemovendo 'Evermore'...\n");
    test = removeAlbum(&myLibrary->album, "Evermore");
    printf("A remocao: %d\n", test);

    
    printf("\nÁlbuns após remoção:\n");

    test = removeAlbum(&myLibrary->album, "Evermore");
    printf("A remocao: %d\n", test);
    printAlbums(myLibrary->album);

    // Liberando memória
    liberaLibrary(&myLibrary);

    return 0;
}

void initializeLibrary(Library **library) {
   *library = (Library *)malloc(sizeof(Library));
   if (*library == NULL) {
       printf("Memory allocation failed.\n");
       exit(1);
   }

   (*library)->album = NULL;
}

// Função para liberar a memória da biblioteca
void liberaLibrary(Library **library) {
   if (*library != NULL) {
       liberaArvAlbum(&(*library)->album);
       // Adicione funções para liberar playlists e outras estruturas
       free(*library);
       *library = NULL; // Define o ponteiro como NULL após liberar a memória
   }
}