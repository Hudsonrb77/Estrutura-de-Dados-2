#include <stdio.h>
#include "musicas.h"  // Inclui o cabeçalho com todas as declarações


// Definindo tipos com typedef para simplificar



typedef struct Library {
   ArvMusic *musicas;   // Árvore de playlists
} Library;

// Protótipos das funções
void initializeLibrary(Library **library);
void liberaLibrary(Library **library);

int main() {
    // 1. Inicializa a biblioteca
    Library *minhaBiblioteca = NULL;
    initializeLibrary(&minhaBiblioteca);
    
    printf("Biblioteca inicializada!\n");

    // 2. Insere músicas
    insertMusic(&(minhaBiblioteca->musicas), "Bohemian Rhapsody", 5.55);
    insertMusic(&(minhaBiblioteca->musicas), "Imagine", 3.04);
    insertMusic(&(minhaBiblioteca->musicas), "Shape of You", 3.53);

    // 3. Lista todas as músicas (em ordem alfabética)
    printf("\n=== Músicas na Biblioteca ===\n");
    printMusic(minhaBiblioteca->musicas);

    // 4. Busca uma música específica
    char musicaProcurada[] = "Imagine";
    ArvMusic *musicaEncontrada = buscarMusicas(minhaBiblioteca->musicas, musicaProcurada);
    
    if (musicaEncontrada != NULL) {
        printf("\nMúsica encontrada: %s (Duração: %.2f minutos)\n", 
               musicaEncontrada->info.titleMusic, 
               musicaEncontrada->info.duration);
    } else {
        printf("\nMúsica '%s' não encontrada.\n", musicaProcurada);
    }

    // 5. Remove uma música
    char musicaRemover[] = "Shape of You";
    if (removeMusic(&(minhaBiblioteca->musicas), musicaRemover)) {
        printf("\nMúsica '%s' removida com sucesso!\n", musicaRemover);
    } else {
        printf("\nFalha ao remover '%s'.\n", musicaRemover);
    }

    // 6. Lista novamente após remoção
    printf("\n=== Músicas após remoção ===\n");
    printMusic(minhaBiblioteca->musicas);

    // 7. Libera a memória alocada
    liberaLibrary(&minhaBiblioteca);
    printf("\nMemória liberada. Fim do programa.\n");

    return 0;
}

void initializeLibrary(Library **library) {
   *library = (Library *)malloc(sizeof(Library));
   if (*library == NULL) {
       printf("Memory allocation failed.\n");
       exit(1);
   }

   (*library)->musicas = NULL;
}

// Função para liberar a memória da biblioteca
void liberaLibrary(Library **library) {
   if (*library != NULL) {
       liberaArvMusic(&(*library)->musicas);
       // Adicione funções para liberar playlists e outras estruturas
       free(*library);
       *library = NULL; // Define o ponteiro como NULL após liberar a memória
   }
}