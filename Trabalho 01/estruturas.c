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
    struct Album *albums;   // Binary tree of albums
    struct Artist *left, *right;
};

// Playlist Structure
struct Playlist {
    char name[100];
    struct Music *tracks;  // Binary tree of tracks
    struct Playlist *left, *right;
};

// General Structure
struct Library {
    struct Artist *artists;    // Binary tree of artists
    struct Playlist *playlists; // Binary tree of playlists
};