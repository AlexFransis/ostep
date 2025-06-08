#include <stdio.h>
#include <stdbool.h>

#define NUM_SEGMENTS 3
#define PHYSICAL_MEMORY_SIZE 64;
#define ADDRESS_SPACE 16;

enum SegmentType {
        CODE = 0,
        HEAP = 1,
        STACK = 2
};

typedef struct {
        unsigned base;
        unsigned size;
        bool grows_backwards;
} Segment;

typedef struct {
        int segment;
        int offset;
} VirtualAddress;

Segment segment_table[NUM_SEGMENTS] = {
        [CODE] = {.base = 0, .size = 6, .grows_backwards = false}, // 0-5 in physical memory
        [HEAP] = {.base = 20, .size = 6, .grows_backwards = false}, // 20-25 in physical memory
        [STACK] = {.base = 48, .size = 4, .grows_backwards = true} // 48-45 in physical memory
};

int translate_address(Segment segment_table[], VirtualAddress* vaddr)
{
        if (vaddr->segment < 0 || vaddr->segment > NUM_SEGMENTS) {
                printf("Invalid segment\n");
                return -1;
        }


        if (vaddr->offset > segment_table[vaddr->segment].size) {
                printf("Segmentation fault: offset %d out of bounds in segment %d\n", vaddr->offset, vaddr->segment);
                return -1;
        }

        Segment seg = segment_table[vaddr->segment];
        int offset = vaddr->offset;
        if (seg.grows_backwards) {
                offset = -offset;
        }
        int paddr =  seg.base + offset;
        printf("Logical Address [Segment %d, Offset %d] -> Physical Address: %d\n", vaddr->segment, vaddr->offset, paddr);

        return paddr;
}


int main(int argc, char** argv)
{
        VirtualAddress vaddr1 = {.segment = CODE, .offset = 3 };
        VirtualAddress vaddr2 = {.segment = HEAP, .offset = 5 };
        VirtualAddress vaddr3 = {.segment = STACK, .offset = 9 };
        VirtualAddress vaddr4 = {.segment = STACK, .offset = 3 };

        int paddr1 = translate_address(segment_table, &vaddr1);
        int paddr2 = translate_address(segment_table, &vaddr2);
        int paddr3 = translate_address(segment_table, &vaddr3);
        int paddr4 = translate_address(segment_table, &vaddr4);

        return 0;
}
