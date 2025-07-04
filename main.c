#include "header.h"

int idx, strLength; // `idx` sebagai indeks pita, `strLength` untuk panjang kata "saat ini"
char cKata[50]; // Menyimpan kata "saat ini"

int main(){
    tree T;
    data_inside_node root;
    strcpy(root.type, "directory");
    strcpy(root.name, "root");
    root.size = 0;
    makeTree(root, &T);

    int flag = 1;
    char tape[501]; // Array yang digunakan untuk menyimpan inputan user

    simpul* toMove = T.root;
    while (flag == 1) // Program akan berjalan selama flag bernilai 1
    {
        // Inputan user
        scanf(" %500[^\n]s", tape);
        if (EOPCHECCKER(tape) == 0) // Jika inputan tidak diakhiri dengan tanda ';' maka akan terjadi error
        {
            printf("[ERROR] gunakan eop diakhir kalimat! Silahkan masukan inputan baru\n");
        } else{
            // Memasukan inputan menjadi perintah untuk dbms
            modify_data(tape, &T, &toMove);
            if(strcmp(tape, "exit;") == 0) // Quit
            {
                flag = 0;
            }
            
        }
    }
    return 0;
}