#include <stdio.h>

void print_bits(char read_buffer[], int bytes_to_read) {
    int i;
    int bit;
    char char_to_print;

    printf("bytes to read: %d. Printing in big-endian format.\n", bytes_to_read);

    for (i = 0; i < bytes_to_read; i++) {
        char_to_print = read_buffer[i];

        for (bit = 7; bit >= 0; bit--) {
            printf("bit #%d: %d\n", bit, char_to_print >> bit & 1);
        }
        printf("\n");
    }
}
