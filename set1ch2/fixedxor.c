#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utils/hexutils.h"
#include "../utils/bits.h"

int main(int argc, char *argv[]) {
    char *hex_string1 = argv[1];
    char *hex_string2 = argv[2];
    printf("Input hex strings are\n%s\n%s\n", hex_string1, hex_string2);
    validate_hex_str(hex_string1);
    validate_hex_str(hex_string2);
    int len = strlen(hex_string1);

    if (len != strlen(hex_string2)) {
        fprintf(stderr, "Both input hex strings must be of equal length.\n");
        exit(1);
    }

    int buffer_len = (len + 1) / 2 + 1; // add one for null terminator
    char *buffer1 = calloc(buffer_len, sizeof(char));
    char *buffer2 = calloc(buffer_len, sizeof(char));
    char *result = calloc(buffer_len, sizeof(char));
    char *output = calloc((buffer_len - 1) * 2 + 1, sizeof(char));

    fill_buffer_with_bits_from_hex_string(buffer1, hex_string1);
    fill_buffer_with_bits_from_hex_string(buffer2, hex_string2);

    /* print_bits(buffer1, buffer_len - 1); */
    /* print_bits(buffer2, buffer_len - 1); */

    int i, j;
    for (i = 0; i < buffer_len - 1; i++) {
        result[i] = *(buffer1 + i) ^ *(buffer2 + i);
    }

    /* print_bits(result, buffer_len - 1); */

    char_array_to_hex_string(result, output);
    fprintf(stdout, "\nFinal output:\n%s\n", output);

    return 0;
}
