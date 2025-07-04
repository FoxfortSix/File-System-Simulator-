/*Saya Mochammad Azka Basria dengan Nim 2405170 mengerjakan tugas
TP 5 dalam mata kuliah Struktur Data
untuk keberkahan-Nya maka saya tidak akan melakukan kecurangan seperti yang telah di spesifikasikan*/

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

// --------------------------------------------------------------------------------------------------------------------------------------------------------

// MESIN ABSTRAK - MESIN KATA
/*Bagian ini berisikan semua variabel global maupun function yang dibutuhkan untuk membuaat mesin kata*/

// Variabel global untuk mesin kata
extern int idx, strLength; // `idx` sebagai indeks pita, `strLength` untuk panjang kata "saat ini"
extern char cKata[50]; // Menyimpan kata "saat ini"

// Mengecek apakah pita telah mencapai EOP atau belum
int EOP(char pita[]);
// Memulai pembacaan kata pertama dari pita
void START(char pita[]);
// Mengatur ulang kata "saat ini"
void RESET();
// Membaca kata berikutnya pada pita
void INC(char pita[]);
// return kata "saat ini"
char* GETCW();
// return panjang kata "saat ini"
int GETLEN();
int EOPCHECCKER(char tape[]);
// --------------------------------------------------------------------------------------------------------------------------------------------------------
// MESIN ABSTRAK - MESIN KATA

typedef struct
{
    char type[100], name[100];
    int size;

} data_inside_node;

typedef struct smp *alamatsimpul;
typedef struct smp {
    data_inside_node data;
    alamatsimpul sibling;
    alamatsimpul child;
} simpul;

typedef struct {
    simpul *root;
} tree;

void makeTree(data_inside_node temp, tree *T);
/*
    Fungsi Menambahkan Anak:
        - Menambahkan node baru sebagai anak dari root tertentu
        - Mengatur linked list untuk sibling (circular linked list)
*/
void addChild(data_inside_node temp, simpul *root);
/* 
    Fungsi Menghapus Seluruh Pohon:
        - Rekursif menghapus dari daun ke root (post-order)
        - Membebaskan memori secara sistemastis
*/

 void delAll(simpul *root);
// BUAT ALGO DEL CHILD DENGAN ISI YANG SAMA

 void delChild(char target[], simpul *root);
simpul* findSimpul(char target[], simpul *root);
// --------------------------------------------------------------------------------------------------------------------------------------------------------

// QUEUE

typedef struct elm *alamatelmt;

typedef struct elm {
    simpul* data;
    alamatelmt next;
} elemen;

typedef struct {
    elemen *first;
    elemen *last;
} queue;

void createEmpty(queue *Q);
int isEmpty(queue Q);
int countElement(queue Q);
void add(simpul* temp, queue *Q );
void del(queue *Q);
// --------------------------------------------------------------------------------------------------------------------------------------------------------
// MAIN FUNCTION

void print_levelOrderTraversal(simpul* root);
simpul* find_levelOrderTraversal(char target[], simpul* root);
simpul* find_directory_that_contains_target_as_a_child_levelOrderTraversal(char target[], simpul* root);
int directoryCounter(char target[], simpul* root);
void printTreePreOrder(simpul *node, simpul* rootTree, simpul* parent);
int hitungTotalUkuran(simpul* root);
void updateSeluruhUkuranDirektori(simpul* root);
void modify_data(char tape[], tree *T, simpul** toMove);