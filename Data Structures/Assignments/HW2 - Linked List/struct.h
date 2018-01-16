#ifndef STRUCT_H
#define STRUCT_H
#define SNAME_LENGTH 50
#define LNAME_LENGTH 50
#define STYLE_LENGTH 30
#define SINGER_LENGTH 50

typedef struct song song;
typedef struct song_node song_node;
typedef struct playlist playlist;
typedef struct list list;


struct song {
    char* name; //= new char[SNAME_LENGTH];
    char* singer; //= new char[SINGER_LENGTH];
    char* style; //= new char[STYLE_LENGTH];
    int year;
};

struct song_node {
    song* data;
    song_node* next;
    song_node* prev;
    playlist* parent;
};

struct playlist {
    int songnumber;
    char* name; // = new char[LNAME_LENGTH];
    song_node* head;
    playlist* next;
    playlist* prev;
};
//add file definitions and functions as needed.
struct list {
    int playlist_count;
    playlist* head;
    FILE *database;
    void create();
    void createList();
    void writeToFile();
    void addSong();
    void removeSong();
    void deleteList();
    void play();
    void printList();
    void Exit();
};

#endif
