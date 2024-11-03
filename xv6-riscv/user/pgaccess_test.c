#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/riscv.h" // For PGSIZE

int main(int argc, char *argv[]) {
    char *pageTester;
    uint64 accessBitmap = 0;
    int num_pages = 5; // Number of pages to test

    pageTester = sbrk(num_pages * PGSIZE);

    // Access some pages
    for (int i = 0; i < num_pages; ++i) {
        if (i % 2 == 0) {
            pageTester[i * PGSIZE] = 'A'; // Access even-indexed pages
        }
    }

    if (pgaccess(pageTester, num_pages, &accessBitmap) < 0) {
        printf("error in pgaccess\n");
    } else {
        for (int i = 0; i < num_pages; ++i) {
            int accessed = (accessBitmap & (1UL << i)) != 0;
            printf("Page %d, accessed: %d\n", i, accessed);
        }
    }

    exit(0);
}
