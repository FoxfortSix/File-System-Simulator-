/*Saya Mochammad Azka Basria dengan Nim 2405170 mengerjakan tugas
TP 5 dalam mata kuliah Struktur Data
untuk keberkahan-Nya maka saya tidak akan melakukan kecurangan seperti yang telah di spesifikasikan*/

#include "header.h"

// --------------------------------------------------------------------------------------------------------------------------------------------------------

// MESIN ABSTRAK - MESIN KATA
/*Bagian ini berisikan semua variabel global maupun function yang dibutuhkan untuk membuaat mesin kata*/

// Mengecek apakah pita telah mencapai EOP atau belum
int EOP(char pita[]){
    if (pita[idx] == ';') return 1; // EOP ditandai karakter ';'
    else return 0; // Belum EOP
}

// Memulai pembacaan kata pertama dari pita
void START(char pita[]){
    idx = 0; // Inisialisasi indeks pita
    strLength = 0; // Panjang kata awal adalah nol

    // Skip spasi awal pada pita
    while (pita[idx] == ' '){
        idx++;
    }

    // Membaca karakter hingga menemukan spasi atau akhir pita
    while ((pita[idx] != ' ') && (pita[idx] != ';')){
        cKata[strLength] = pita[idx];
        idx++;
        strLength++;
    }
    cKata[strLength] = '\0'; // Menutup kata dengan null character
}

// Mengatur ulang kata "saat ini"
void RESET(){
    strLength = 0; // Reset panjang kata
    cKata[strLength] = '\0'; // Mengosongkan kata "saat ini"
}

// Membaca kata berikutnya pada pita
void INC(char pita[]){
    strLength = 0; // Reset panjang kata "saat ini"

    // Skip spasi antar kata
    while (pita[idx] == ' '){
        idx++;
    }

    // Membaca karakter hingga spasi atau akhir pita
    while ((pita[idx] != ' ') && (pita[idx] != ';')){
        cKata[strLength] = pita[idx];
        idx++;
        strLength++;
    }
    cKata[strLength] = '\0'; // Menutup kata dengan null character
}

// return kata "saat ini"
char* GETCW(){
    return cKata;
}

// return panjang kata "saat ini"
int GETLEN(){
    return strLength;
}

int EOPCHECCKER(char tape[]){
    int len = strlen(tape) - 1;
    if(tape[len] != ';') return 0;
    else return 1;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------
// MESIN ABSTRAK - MESIN KATA

void makeTree(data_inside_node temp, tree *T){
    simpul *node;
    node = (simpul *) malloc(sizeof(simpul));
    node->data = temp;
    node->sibling = NULL;
    node->child = NULL;
    (*T).root = node;
}

/*
    Fungsi Menambahkan Anak:
        - Menambahkan node baru sebagai anak dari root tertentu
        - Mengatur linked list untuk sibling (circular linked list)
*/
void addChild(data_inside_node temp, simpul *root){
    if (root != NULL){
        simpul *baru;
        baru = (simpul *) malloc(sizeof(simpul));
        baru->data = temp;
        baru->child = NULL;

        if (root->child == NULL){
            baru->sibling = NULL;
            root->child = baru;
        } else {
            if (root->child->sibling == NULL){
                baru->sibling = root->child;
                root->child->sibling = baru;
            } else{
                simpul *last = root->child;
                while (last->sibling != root->child){
                    last = last->sibling;
                }
                baru->sibling = root->child;
                last->sibling = baru;
            }
        }
    }
}

/* 
    Fungsi Menghapus Seluruh Pohon:
        - Rekursif menghapus dari daun ke root (post-order)
        - Membebaskan memori secara sistemastis
*/

 void delAll(simpul *root){
    if(root != NULL){
        /* jika simpul root tidak kosong */
        if(root->child != NULL){
            if(root->child->sibling == NULL){
            /* jika hanya memiliki satu simpul anak */
            delAll(root->child);
            free(root);
            } else{
                simpul *bantu;
                simpul *proses;
                bantu = root->child;
                while(bantu->sibling != root->child){
                    proses = bantu;
                    bantu = bantu->sibling;
                    delAll(proses);
                }
                //proses anak terakhir
                if(bantu != NULL){
                    delAll(bantu);
                }
                free(root);
            }
        }
        else{
            free(root);
        }
    }
}

// BUAT ALGO DEL CHILD DENGAN ISI YANG SAMA

 void delChild(char target[], simpul *root){
    if(root != NULL){
        simpul *hapus = root->child;
        if(hapus != NULL){
            if(hapus->sibling == NULL){
                /*jika hanya mempunyai satu anak*/
                if(strcmp(root->child->data.name, target) == 0){
                    delAll(root->child);
                    root->child = NULL;
                } else{
                    printf("tidak ada simpul anak dengan kontainer karakter masukan\n");
                }
            } else {
                /*jika memiliki lebih dari satu simpul
                anak*/
                simpul *prev = NULL;
                /*mencari simpul yang akan dihapus*/
                int ketemu = 0;

                while((hapus->sibling != root->child) && (ketemu == 0)){
                    if(strcmp(hapus->data.name, target) == 0){
                        ketemu = 1;
                    } else{
                        prev = hapus;
                        hapus = hapus->sibling;
                    }
                }
                /*memproses simpul anak terakhir karena
                belum terproses dalam pengulangan*/
                if((ketemu == 0) && (strcmp(hapus->data.name, target) == 0)){
                    ketemu = 1;
                }

                if(ketemu == 1){
                    simpul *last = root->child;
                    /* mencari simpul anak terakhir untuk
                    membantu proses atau pemeriksaan jika yang
                    dihapus nantinya anak terakhir */
                    while(last->sibling != root->child){
                        last = last->sibling;
                    }
                    
                    if(prev == NULL){
                        /*jika simpul yang dihapus anak pertama*/
                        if((hapus->sibling == last)&& (last->sibling == root->child)){
                            /*jika hanya ada dua anak*/
                            root->child = last;
                            last->sibling = NULL;
                        } else{
                            /* jika memiliki simpul anak
                            lebih dari dua simpul */
                            root->child = hapus->sibling;
                            last->sibling = root->child;
                        }
                    } else{
                        if((prev == root->child) &&(hapus->sibling == root->child)){
                            /* jika hanya ada dua simpul
                            anak dan yang dihapus adalah simpul
                            anak kedua */
                            root->child->sibling = NULL;
                        } else{
                            /* jika yang dihapus bukan
                            simpul anak pertama dan simpul root
                            memiliki simpul anak lebih dari dua
                            simpul */
                            prev->sibling = hapus->sibling;
                            hapus->sibling = NULL;
                        }
                    }
                    delAll(hapus);
                } else{
                printf("tidak ada simpul anak dengan kontainer karakter masukan\n");
                }
            }
        }
    }
}

simpul* findSimpul(char target[], simpul *root){
    simpul *hasil = NULL;
    if (root != NULL){
        if (strcmp(root->data.name, target) == 0){
            hasil = root;
        } else {
            simpul *bantu = root->child;
            if (bantu != NULL){
                if (bantu->sibling == NULL){
                    hasil = findSimpul(target, bantu);
                } else {
                    int ketemu = 0;
                    while ((bantu->sibling != root->child) && (ketemu == 0)){
                        if (strcmp(root->data.name, target) == 0){
                            hasil = bantu;
                            ketemu = 1;
                        } else {
                            hasil = findSimpul(target, bantu);
                            if (hasil != NULL)
                            {
                                ketemu = 1;
                            } else{
                                bantu = bantu->sibling;
                            }
                            
                        }
                    }
                    if (ketemu == 0){
                        if (strcmp(root->data.name, target) == 0){
                            hasil = bantu;
                        } else {
                            hasil = findSimpul(target, bantu);
                        }
                    }
                }
            }
        }
    }
    return hasil;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------

// QUEUE
void createEmpty(queue *Q){
    (*Q).first = NULL;
    (*Q).last = NULL;
}

int isEmpty(queue Q){
    int hasil = 0;
    if(Q.first == NULL){
        hasil = 1;
    }
    return hasil;
}

int countElement(queue Q){
    int hasil = 0;
    if(Q.first != NULL){
        elemen* bantu;
        bantu = Q.first;
        while(bantu != NULL){
            hasil = hasil + 1;
            bantu = bantu->next;
        }
    }
    return hasil;
}

void add(simpul* temp, queue *Q ){
    elemen* baru;
    baru = (elemen *) malloc (sizeof (elemen));  

    baru->data = temp;
    baru->next = NULL;

    if((*Q).first == NULL){
        (*Q).first = baru;
    } else {     
        (*Q).last->next = baru;
    }

    (*Q).last = baru;
    baru = NULL; 
}

void del(queue *Q){
    if((*Q).first != NULL){
        elemen *hapus = (*Q).first;
        if(countElement(*Q) == 1){
            (*Q).first = NULL;
            (*Q).last = NULL;
        } else {
            (*Q).first = (*Q).first->next;
            hapus->next = NULL;
        }
        free(hapus);
    }
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------
// MAIN FUNCTION

void print_levelOrderTraversal(simpul* root){
    if (root != NULL)
    {
        queue Q;
        createEmpty(&Q);
        add(root, &Q);

        while (isEmpty(Q) != 1)
        {
            int n = countElement(Q);

            while (n > 0)
            {
                simpul* treePointer = Q.first->data;
                // printf("%c ", treePointer->data.c);
                del(&Q);

                simpul* rootChild = treePointer->child;
                if (rootChild != NULL){
                    if (rootChild->sibling == NULL)
                    {
                        add(rootChild, &Q);
                    } else{
                        while((rootChild->sibling != treePointer->child)){
                            add(rootChild, &Q);
                            rootChild = rootChild->sibling;
                        }
                        add(rootChild, &Q);
                    }
                }
                n--;
            }
            printf("\n");
        }
        
    }
    
}

simpul* find_levelOrderTraversal(char target[], simpul* root){
    simpul* result = NULL;
    if (root != NULL)
    {
        queue Q;
        createEmpty(&Q);
        add(root, &Q);

        while (isEmpty(Q) != 1)
        {
            int n = countElement(Q);

            while (n > 0 && result == NULL)
            {
                simpul* treePointer = Q.first->data;
                if (strcmp(target, treePointer->data.name) == 0)
                {
                    result = treePointer;
                }
                
                del(&Q);

                simpul* rootChild = treePointer->child;
                if (result == NULL && rootChild != NULL){
                    if (rootChild->sibling == NULL)
                    {
                        add(rootChild, &Q);
                    } else{
                        while((rootChild->sibling != treePointer->child)){
                            add(rootChild, &Q);
                            rootChild = rootChild->sibling;
                        }
                        add(rootChild, &Q);
                    }
                }
                n--;
            }

            if (result != NULL)
            {
                while (isEmpty(Q) != 1)
                {
                    del(&Q);
                }
            }
            
        }
    }
    return result;
}

simpul* find_directory_that_contains_target_as_a_child_levelOrderTraversal(char target[], simpul* root){
    simpul* result = NULL;
    if (root != NULL)
    {
        queue Q;
        createEmpty(&Q);
        add(root, &Q);

        while (isEmpty(Q) != 1)
        {
            int n = countElement(Q);

            while (n > 0 && result == NULL)
            {
                simpul* treePointer = Q.first->data;
                if (strcmp(treePointer->data.type, "directory") == 0 && treePointer->child != NULL)
                {
                    simpul* rootChild = treePointer->child;
                    if (rootChild->sibling == NULL){
                        if (strcmp(rootChild->data.name, target) == 0){
                            result = treePointer;
                        }
                    } else {
                        while ((rootChild->sibling != treePointer->child) && result == NULL){
                            if (strcmp(rootChild->data.name, target) == 0){
                                result = treePointer;
                            } else {
                                rootChild = rootChild->sibling;
                            }
                        }
                        if (strcmp(rootChild->data.name, target) == 0){
                            result = treePointer;
                        }
                    }
                }
                
                del(&Q);

                simpul* rootChild = treePointer->child;
                if (result == NULL && rootChild != NULL){
                    if (rootChild->sibling == NULL)
                    {
                        add(rootChild, &Q);
                    } else{
                        while((rootChild->sibling != treePointer->child)){
                            add(rootChild, &Q);
                            rootChild = rootChild->sibling;
                        }
                        add(rootChild, &Q);
                    }
                }
                n--;
            }

            if (result != NULL)
            {
                while (isEmpty(Q) != 1)
                {
                    del(&Q);
                }
            }
            
        }
    }
    return result;
}


int directoryCounter(char target[], simpul* root){
    int result = 0;
    int flag = 0;
    if (root != NULL)
    {
        queue Q;
        createEmpty(&Q);
        add(root, &Q);

        while (isEmpty(Q) != 1)
        {
            int n = countElement(Q);

            while (n > 0 && flag == 0)
            {
                simpul* treePointer = Q.first->data;
                if (strcmp(target, treePointer->data.name) == 0)
                {
                    flag++;
                }
                del(&Q);

                simpul* rootChild = treePointer->child;
                if (flag == 0 && rootChild != NULL){
                    if (rootChild->sibling == NULL)
                    {
                        add(rootChild, &Q);
                    } else{
                        while((rootChild->sibling != treePointer->child)){
                            add(rootChild, &Q);
                            rootChild = rootChild->sibling;
                        }
                        add(rootChild, &Q);
                    }
                }
                n--;
            }

            if (flag == 1)
            {
                while (isEmpty(Q) != 1)
                {
                    del(&Q);
                }
            } else{
                result++;
            }
            
        }
    }

    if (flag == 0)
    {
        result = -1;
    }
    
    return result;
}

void printTreePreOrder(simpul *node, simpul* rootTree, simpul* parent){
    if (node != NULL){
        int space = directoryCounter(node->data.name, rootTree);
        for (int i = 0; i < space; i++){
            if (i == 0) printf(" ");
            else printf("    ");
        }

        int isLast = 0;
        if (parent != NULL && parent->child != NULL){
            simpul *bantu = parent->child;

            if (bantu->sibling == NULL){
                if (bantu == node){
                    isLast = 1;
                }
            } else {
                while (bantu->sibling != parent->child){
                    bantu = bantu->sibling;
                }
                if (bantu == node){
                    isLast = 1;
                }
            }
        }

        
        if (strcmp(node->data.type, "directory") == 0){
            if (space != 0){
                if (isLast == 1){
                    printf("└──");
                } else {
                    printf("├──");
                }
            }

            printf("[d] %s (%dkB)\n", node->data.name, node->data.size);
        }
        else if(strcmp(node->data.type, "file") == 0){
            if (isLast == 1){
                printf("└──");
            } else {
                printf("├──");
            }

            printf("[f] %s (%dkB)\n", node->data.name, node->data.size);
        }
        simpul *bantu = node->child;
        if (bantu != NULL){
            if (bantu->sibling == NULL){
                printTreePreOrder(bantu, rootTree, node);
            } else {
                while (bantu->sibling != node->child){
                    printTreePreOrder(bantu, rootTree, node);
                    bantu = bantu->sibling;
                }
                printTreePreOrder(bantu, rootTree, node);
            }
        }
    }
}

int hitungTotalUkuran(simpul* root){
    int total = 0;
    if (root != NULL && root->child != NULL){
        simpul* bantu = root->child;

        if (bantu->sibling == NULL){
            if (strcmp(bantu->data.type, "file") == 0){
                total += bantu->data.size;
            } else if (strcmp(bantu->data.type, "directory") == 0){
                total += hitungTotalUkuran(bantu);
            }
        } else {
            while (bantu->sibling != root->child){
                if (strcmp(bantu->data.type, "file") == 0){
                    total += bantu->data.size;
                } else if (strcmp(bantu->data.type, "directory") == 0){
                    total += hitungTotalUkuran(bantu);
                }
                bantu = bantu->sibling;
            }
            if (strcmp(bantu->data.type, "file") == 0){
                total += bantu->data.size;
            } else if (strcmp(bantu->data.type, "directory") == 0){
                total += hitungTotalUkuran(bantu);
            }
        }
    }
    return total;
}

void updateSeluruhUkuranDirektori(simpul* root){
    if (root != NULL){
        queue Q;
        createEmpty(&Q);
        add(root, &Q);

        while (!isEmpty(Q)){
            simpul* node = Q.first->data;
            del(&Q);


            if (strcmp(node->data.type, "directory") == 0){
                node->data.size = hitungTotalUkuran(node);
            }

            simpul* child = node->child;
            if (child != NULL){
                if (child->sibling == NULL){
                    add(child, &Q);
                } else {
                    while (child->sibling != node->child){
                        add(child, &Q);
                        child = child->sibling;
                    }
                    add(child, &Q);
                }
            }
        }
    }
}


 void modify_data(char tape[], tree *T, simpul** toMove){
    data_inside_node temp;
    START(tape);

        if (strcmp(GETCW(), "tambah") == 0)
        {
            INC(tape);
            strcpy(temp.type, GETCW());
            INC(tape);
            strcpy(temp.name, GETCW());
            INC(tape);
            temp.size = atoi(GETCW());

            addChild(temp, *toMove);
            if (strcmp(temp.type, "file") == 0){
                updateSeluruhUkuranDirektori(T->root);
            }

        } else if (strcmp(GETCW(), "hapus") == 0)
        {
            INC(tape);
            strcpy(temp.name, GETCW());

            simpul* parent = find_directory_that_contains_target_as_a_child_levelOrderTraversal(temp.name, T->root);
            simpul* target = find_levelOrderTraversal(temp.name, T->root);

            if (parent != NULL && target != NULL){
                delChild(temp.name, parent);
                updateSeluruhUkuranDirektori(T->root);
            }
        } else if (strcmp(GETCW(), "list") == 0)
        {
            printf("----- list file di %s -----\n", (*toMove)->data.name);
            printTreePreOrder(*toMove, *toMove, *toMove);
            printf("\n");
        } else if (strcmp(GETCW(), "pindah_ke") == 0)
        {
            INC(tape);
            strcpy(temp.name, GETCW());

            simpul* sacrifice_node = find_levelOrderTraversal(temp.name, T->root);

            if (sacrifice_node == NULL)
            {
                printf("gagal pindah: direktori %s tidak ditemukan\n\n", temp.name);
            }
            else if (strcmp(sacrifice_node->data.type, "directory") != 0)
            {
                printf("gagal pindah: %s bukan direktori\n\n", temp.name);
            }
            else
            {
                *toMove = sacrifice_node;
            }
        } else if (strcmp(GETCW(), "cari") == 0)
        {
            INC(tape);
            strcpy(temp.name, GETCW());

            simpul* search = find_levelOrderTraversal(temp.name, *toMove);

            if (search != NULL)
            {
                printf("hasil pencarian: %s %s (%dkB) ditemukan! :3\n\n", search->data.type, search->data.name, search->data.size);
            } else{
                printf("hasil pencarian: file/direktori %s tidak ditemukan :(\n\n", temp.name);
            }
            
        } else if (strcmp(GETCW(), "reset") == 0)
        {
            delAll(T->root->child);
            T->root->child = NULL;
            *toMove = T->root;

            updateSeluruhUkuranDirektori(T->root); 
        } else if (strcmp(GETCW(), "exit") == 0)
        {
            printf("meoww, bye! ~bubu\n");
        }
        
    }
