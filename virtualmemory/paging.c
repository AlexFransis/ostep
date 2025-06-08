#include <time.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define PHYSICAL_MEMORY_SIZE 64
#define ADDRESS_SPACE 16
#define PAGE_SIZE 4
#define FRAME_SIZE 4
#define NUM_PAGES (ADDRESS_SPACE / PAGE_SIZE)
#define NUM_FRAMES (PHYSICAL_MEMORY_SIZE / FRAME_SIZE)
#define VPN_MASK 12 // 0b1100 - using top 2 bits for the number of pages
#define VPN_SHIFT 2 // number of bits in offset
#define OFFSET_MASK 3 // 0b0011

typedef struct {
        bool is_valid;
        unsigned page_frame_number;
} PageTableEntry;

typedef struct {
        PageTableEntry entries[NUM_PAGES];
} PageTable;


void allocate_page_frame(int* memory, int page_frame)
{
        if (page_frame > NUM_FRAMES) {
                fprintf(stderr, "Invalid page frame: %d", page_frame);
                exit(EXIT_FAILURE);
        }

        for (int i = 0; i < FRAME_SIZE; ++i) {
                int addr = page_frame * FRAME_SIZE + i;
                memory[addr] = 1;
        }
}

void init_process(PageTable* page_table, int* physical_memory)
{
        // allocate code page
        int random_page_frame = rand() % NUM_FRAMES;
        allocate_page_frame(physical_memory, random_page_frame);
        page_table->entries[0].is_valid = true;
        page_table->entries[0].page_frame_number = random_page_frame;

        int last_page_frame = random_page_frame;
        while (random_page_frame == last_page_frame) {
                random_page_frame = rand() % NUM_FRAMES;
        }

        allocate_page_frame(physical_memory, random_page_frame);
        page_table->entries[3].is_valid = true;
        page_table->entries[3].page_frame_number = random_page_frame;
}

void dump_physical_memory(int* memory) {
        printf("\nPhysical Memory (Frame Usage):\n");
        for (int i = 0; i < PHYSICAL_MEMORY_SIZE; ++i) {
                if ((i + 1) % FRAME_SIZE == 1) printf(" FRAME (%d) ", i / FRAME_SIZE);
                printf("%d", memory[i]);
                if ((i + 1) % FRAME_SIZE == 0) printf(" | ");
        }
        printf("\n");
}

int translate_address(PageTable* page_table, unsigned char vaddr)
{
        // extract the virtual page number from vaddr
        unsigned char vpn = (vaddr & VPN_MASK) >> VPN_SHIFT;
        PageTableEntry pte = page_table->entries[vpn];
        if (!pte.is_valid) {
                printf("Segmentation fault: virtual address: %d\n", vaddr);
                return -1;
        }

        int pfn = pte.page_frame_number;
        unsigned char offset = vaddr & OFFSET_MASK;
        unsigned char paddr = (pfn << VPN_SHIFT) | offset;

        printf("Logical Address %d [VPN: %d, Offset: %d] -> Physical Address: %d [PFN: %d, Offset: %d]\n",
               vaddr, vpn, offset, paddr, pfn, offset);

        return paddr;
}

int main(int argc, char** argv)
{
        srand(time(NULL));
        int physical_memory[PHYSICAL_MEMORY_SIZE] = {0};
        PageTable process_page_table = {
                .entries = {
                        [0] = {.is_valid = false, .page_frame_number = -1 },
                        [1] = {.is_valid = false, .page_frame_number = -1 },
                        [2] = {.is_valid = false, .page_frame_number = -1 },
                        [3] = {.is_valid = false, .page_frame_number = -1 }
                }
        };

        init_process(&process_page_table, physical_memory);
        unsigned char vaddr1 = 15;
        unsigned char vaddr2 = 1;
        unsigned char vaddr3 = 6;

        int paddr1 = translate_address(&process_page_table, vaddr1);
        int paddr2 = translate_address(&process_page_table, vaddr2);
        int paddr3 = translate_address(&process_page_table, vaddr3);

        dump_physical_memory(physical_memory);
        return 0;
}
