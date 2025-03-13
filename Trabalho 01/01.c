#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Music Structure
struct Music {
    char title[100];
    float duration;
    struct Music *left, *right;
};

// Album Structure
struct Album {
    char title[100];
    int year;
    int track_count;
    struct Music *tracks;  // Binary tree of tracks
    struct Album *left, *right;
};

// Artist Structure
struct Artist {
    char name[100];
    char type[50];   // Singer, duo, band, etc.
    char genre[50];
    int album_count;
    //struct Album *albums;   // Binary tree of albums
    struct Artist *left, *right;
};

// Playlist Structure
struct Playlist {
    char name[100];
    struct Music *tracks;  // Binary tree of tracks
    struct Playlist *left, *right;
};

// General Structure (Library)
struct Library {
    struct Artist *artists;    // Binary tree of artists
    struct Playlist *playlists; // Binary tree of playlists
};

void initializeLibrary(struct Library **library);

int main() {
    struct Library *myLibrary;
    myLibrary = NULL;
    
    printf("%p %p\n", myLibrary, &myLibrary);
    initializeLibrary(&myLibrary);

    

    if (myLibrary->artists == NULL && myLibrary->playlists == NULL) {
        printf("Library initialized successfully! Trees are empty.\n");
    } else {
        printf("Error initializing the library.\n");
    }



    return 0;
}


// Function to initialize the library
void initializeLibrary(struct Library **library) {

   *library = (struct Library *)malloc(sizeof(struct Library)); // Aloca memória para a estrutura
    if (*library == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }


    (*library)->artists = NULL;
    (*library)->playlists = NULL;
}

struct Artist {
   char name[100];
   char type[50];   // Singer, duo, band, etc.
   char genre[50];
   int album_count;
   struct Album *albums;   // Binary tree of albums
   struct Artist *left, *right;

struct Artist *criaNo_Artist(char name[100], char type[50], char genre[50], int album_count){
   struct Artist *novo_no = (struct Artist *)malloc(sizeof(struct Artist));

   //Copiando de forma que evite estouro de buffer ao copiar strings.
   strncpy(novo_no->name, name, sizeof(novo_no->name) - 1);
   novo_no->name[sizeof(novo_no->name) - 1] = '\0'; // Garantir terminação.

   strncpy(novo_no->type, type, sizeof(novo_no->type) - 1);
   novo_no->type[sizeof(novo_no->type) - 1] = '\0';

   strncpy(novo_no->genre, genre, sizeof(novo_no->genre) - 1);
   novo_no->genre[sizeof(novo_no->genre) - 1] = '\0';
    
   novo_no->album_count = album_count;

   return novo_no;
}


int insere(struct Artist **rt, int info) {
      int inseriu = -1;
      if ((*bt) == NULL)
      {
         (*bt) = aloca(info);
         inseriu = 1;
      }
      else
      {
         if ((*bt)->info > info)
         {

            inseriu = insere(&(*bt)->esq, info);
         }
         else if ((*bt)->info < info)
         {

            inseriu = insere(&(*bt)->dir, info);
         }
         else
            inseriu = -1;
      }
      return inseriu;
}   