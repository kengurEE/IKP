#include <stdio.h>
#include <stdlib.h>

#define NUM_HEAPS 5
#define MAX_NUM_FREE_BLOCKS 10
struct Block {
    size_t size;
    struct Block* next;
};

struct Heap {
    size_t totalSize;
    int numFreeBlocks;
    int numheaps;
    struct Block freeBlocks[MAX_NUM_FREE_BLOCKS];
    struct Block nsb[10];
};

int NUM_HEAPS1 = 0;
struct Heap heaps[NUM_HEAPS];
int Niz[100];
int currentHeap = 0;
int brojac=0;
int Sum_slobodni_blokovi=0;
//struct Block alocirana_mem[100];
struct Heap *h;

void ahm_initialize() {
    for(int  i=0; i<NUM_HEAPS; i++){
    printf("Unesite broj slobodnih blokova za hip %d (do %d slobodnih blokova): \n",i+1, MAX_NUM_FREE_BLOCKS);
    scanf("%d", &heaps[i].numFreeBlocks);

    if(heaps[i].numFreeBlocks > 10){
        Sum_slobodni_blokovi = Sum_slobodni_blokovi + 10;
        Niz[i] = 10;
    }else
    {
        Sum_slobodni_blokovi = Sum_slobodni_blokovi + heaps[i].numFreeBlocks;
        Niz[i] = heaps[i].numFreeBlocks;
    }


        if (heaps[i].numFreeBlocks > MAX_NUM_FREE_BLOCKS) {
        printf("Premasen maksimalni broj slobodnih blokova, postavljam na maksimum.\n");
        heaps[i].numFreeBlocks = MAX_NUM_FREE_BLOCKS;
        }
        printf("Unesite velicinu bloka: ");
        scanf("%d", &heaps[i].totalSize);
            for (int j = 0; j < heaps[i].numFreeBlocks; j++) {
               // heaps[i].freeBlocks[j].size = heaps[i].totalSize / heaps[i].numFreeBlocks;
               // heaps[i].freeBlocks[j].next = j < heaps[i].numFreeBlocks - 1 ? &heaps[i].freeBlocks[j + 1] : NULL;
                heaps[i].nsb[j].size = heaps[i].totalSize * heaps[i].numFreeBlocks;
                heaps[i].nsb[j].next = j < heaps[i].numFreeBlocks - 1 ? &heaps[i].nsb[j + 1] : NULL;
                printf("Slobodni blok velicine: %d, hipa: %d \n", heaps[i].nsb[j].size, i+1);
               //printf("Samo j: %d \n",j);
            }
    }

}

void Ipsi(){
for(int i=0; i<NUM_HEAPS;i++){
for(int j=0; j<Niz[i]; j++){
    printf("Jel ovo dobro: %d\n",i+1);
}
}

}



void* Malloc(){
    struct Heap* currentHeapPtr=&heaps[0];
    struct Block* currentBlock=&currentHeapPtr->nsb[0];
    struct Block* allociranaMemorija=&currentHeapPtr->nsb[0];
    void* allocatedMemory;
        //printf("d\n");
        for(int i=0; i<NUM_HEAPS;i++){
                    //printf("c\n");
            printf("Hip: %d\n", i+1);
            currentHeapPtr= &heaps[i];
            currentBlock = &currentHeapPtr->nsb[i-i];
                for(int j=0; j<Niz[i]; j++){
                   //currentBlock = &currentHeapPtr->nsb[j];
                    printf("Blok za alokaciju: %d\n", currentBlock);
                    allocatedMemory = (void*)((char*)currentBlock + currentBlock->size);
                    printf("Trenutno zauzet memorijski prostor: %p\n", (void*)allocatedMemory);
                    struct Block *blok = (struct Block*)allocatedMemory;
                    //printf("J: %d",j);
                    //printf("Niz[%d]: %d\n",i,Niz[i]);
                    if(j+1!=Niz[i]){
                            //printf("koliko puta odes na sledeci:%d\n",j+1);
                    currentBlock = currentBlock->next;
                    }
                    //printf("Naredni blok: %d\n", currentBlock->size);

                }

                }
                return allociranaMemorija;

}

/*
void* Malloc(size_t requestedSize) {
    // Čuvaj originalni hip
    size_t originalHeap = currentHeap;
    void* pusiga;

    // Iteriraj kroz sve hipove
    for (size_t i = 0; i < NUM_HEAPS; ++i) {
        struct Heap* currentHeapPtr = &heaps[i];
        struct Block* currentBlock = currentHeapPtr->freeBlocks;

        // Iteriraj kroz slobodne blokove trenutnog hipa
        for(int j=0; j< Niz[i]; j++) {
                printf("Brate poceo si sa hipom\n");
            if (currentBlock->size >= requestedSize) {
                printf("Jel moguce da si veci\n");
                // Alocirajte blok memorije
                void* allocatedMemory = (void*)((char*)currentBlock + sizeof(struct Block));

                // Ažurirajte slobodni blok i broj slobodnih blokova u hipu
                currentBlock->size -= requestedSize;
                currentHeapPtr->numFreeBlocks--;

                // Vrati se na početak originalnog hipa i vrati alociranu memoriju
                currentHeap = originalHeap;
                pusiga=&allocatedMemory;
            }

            currentBlock = currentBlock->next;

        }
        return pusiga;
    }

    // Ako smo prošli kroz sve hipove i nijedan nije imao dovoljno slobodnog prostora
    fprintf(stderr, "Nema dovoljno slobodnog prostora u svim hipovima.\n");
    return NULL;
}
*/

/*
void* Malloc() {
    // Čuvaj originalni hip
    size_t originalHeap = currentHeap;
    struct Heap *pocetni = &heaps[currentHeap];

    // Iteriraj kroz sve hipove
    for (size_t i = 0; i < NUM_HEAPS; ++i) {
        struct Heap* currentHeapPtr = &heaps[i];
        struct Block* currentBlock = currentHeapPtr->freeBlocks;
        struct Block* prevBlock = NULL;
        printf("Sta je ovo syari\n");
        // Iteriraj kroz slobodne blokove trenutnog hipa
        for(int j=0; j< currentHeapPtr->numFreeBlocks; j++){
                printf("zastooooo %d\n",Niz[i]);
            if (currentBlock->size > sizeof(struct Block)) {
                // Alocirajte blok memorije
                printf("dodjes dovde\n");
                void* allocatedMemory = (void*)((char*)currentBlock + sizeof(struct Block));

                // Ažurirajte slobodni blok i broj slobodnih blokova u hipu
                currentBlock->size -= sizeof(struct Block);
                currentHeapPtr->numFreeBlocks--;

                // Vrati se na početak originalnog hipa
                currentHeap = originalHeap;
            }

            prevBlock = currentBlock;
            currentBlock = currentBlock->next;
            printf("jel odje puknes\n");
        }

        // Idi na sljedeći hip
        //currentHeap = (currentHeap + 1) % NUM_HEAPS;
    }

    // Ako smo prošli kroz sve hipove i nijedan nije imao dovoljno slobodnog prostora
    fprintf(stderr, "Nema dovoljno slobodnog prostora u svim hipovima.\n");
    return NULL;
}
*/

/*
void* Malloc() {
    int originalHeap = currentHeap;

    struct Heap* currentHeapPtr = &heaps[currentHeap];
    struct Block* currentBlock = currentHeapPtr->freeBlocks;
    struct Block* prevBlock = NULL;
    do {

            if (currentBlock->size > sizeof(struct Block)) {
                // Alocirajte blok memorije
                void* allocatedMemory = (void*)((char*)currentBlock + sizeof(struct Block));

                // Ažurirajte slobodni blok i broj slobodnih blokova u hipu
                currentBlock->size -= sizeof(struct Block); //cijeli hip(sastavljen od blokova)- jedan zauzet blok
                currentHeapPtr->numFreeBlocks--;

                // Ako je preostali prostor u bloku dovoljno velik, stvorite novi slobodni blok
                if (currentBlock->size > sizeof(struct Block)) {
                    struct Block* newFreeBlock = (struct Block*)((char*)currentBlock + sizeof(struct Block) + currentBlock->size - sizeof(struct Block));
                    newFreeBlock->size = currentBlock->size - sizeof(struct Block);
                    newFreeBlock->next = currentBlock->next;
                    currentBlock->size = sizeof(struct Block); // Ažuriranje veličine originalnog bloka
                    currentBlock->next = newFreeBlock;
                    printf("EEE\n");
                }
                printf("TUTU?");

                return allocatedMemory;
            }

            prevBlock = currentBlock;
            currentBlock = currentBlock ? currentBlock->next : NULL;


    } while (currentBlock || (currentHeap = (currentHeap + 1) % NUM_HEAPS) != originalHeap);

    fprintf(stderr, "Nema dovoljno slobodnog prostora u svim hipovima.\n");
    return NULL;
}

*/

void Free(void *pokazivac){
    struct Heap* currentHeapPtr=&heaps[0];
    struct Block* currentBlock=&currentHeapPtr->nsb[0];
    struct Block* currentBlockNull=&currentHeapPtr->nsb[0];
    if(pokazivac==currentBlock){
        for(int i=0; i<NUM_HEAPS; i++){
            currentHeapPtr= &heaps[i];
            currentBlock = &currentHeapPtr->nsb[i-i];
            for(int j=0; j<Niz[i]; j++){
                currentBlockNull = currentBlock;
                printf("Dealokacija memorije za blok: %d, velicine: %d -> ", currentBlock, currentBlock->size);

                if(j+1!=Niz[i]){
                    currentBlock=currentBlock->next;
                }
                currentBlockNull = NULL;

                printf("%d\n", currentBlockNull);

            }
        }
    }
}

/*
void ahm_terminate() {
    for (int i = 0; i < NUM_HEAPS; ++i) {
        struct Block* currentBlock = heaps[i].freeBlocks;
        struct Block* nextBlock = NULL;

        // Oslobodi svaki blok u hipu
        while (currentBlock) {
            nextBlock = currentBlock->next;
            free(currentBlock);
            currentBlock = nextBlock;
            printf("Upanes li odje bez mene?");
        }
    }
    printf("KRAJ?");
}
*/


int main() {

    ahm_initialize();
//printf("sa se radi\n");
//Ipsi();
    void* memory1 = Malloc();
    printf("\n\n");
    Free(memory1);


    return 0;
}
