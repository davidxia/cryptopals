#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../utils/hexutils.h"
#include "../utils/bits.h"

const int CHAR_SIZE = sizeof(char);
const int LONG_SIZE = sizeof(long);
const char BASE64_LOOKUP[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";


int main(int argc, char *argv[]) {
    char *hex_string = argv[1];
    printf("Input hex string is '%s'\n", hex_string);

    validate_hex_str(hex_string);

    // Figure out how many bytes we need to convert to base64.
    // Each hexadecimal char is 4 bits. We store bits in an array of chars.
    // Each char holds 8 bits or 1 byte. Each base64 char is 6 bits.
    // The fewest number of bytes that will divide evenly by 6 bits is
    // the lcm(8, 6) / 8 = 3. So we always need a multiple of 3 bytes to hold all
    // the bits to convert into base64.
    //
    // Subtract one from hex_string to remove null terminator.
    // Add 6 and divide by 6 to map 1-6 to 1, 7-12 to 2, etc.
    // Multiply by 3 to get multiples of 3.
    int buffer_size = (6 + strlen(hex_string) - 1) / 6 * 3;
    /* printf("Buffer size: %d\n", buffer_size); */

    int base64_size = 8 * buffer_size / 6 + 1;
    char base64_string[base64_size];
    base64_string[base64_size - 1] = '\0';

    int padding = strlen(hex_string) % 3;

    char buffer[buffer_size];

    fill_buffer_with_bits_from_hex_string(buffer, hex_string);
    /* print_bits(buffer, 3); */

    int i;
    for (i = 0; i < buffer_size / 3; i++) {
        char c = *(buffer + i);
        // There are four base64 chars per 3 bytes
        // First base64 char is the first six bits of the first byte.
        char first_base64 = (*(buffer + i * 3) & 0b11111100) >> 2;
        /* print_bits(&first_base64, 1); */
        /* printf("%c\n", BASE64_LOOKUP[first_base64]); */
        char second_base64 = (*(buffer + i * 3) & 0b00000011) << 4 | (*(buffer + 1 + i * 3) & 0b11110000) >> 4;
        /* print_bits(&second_base64, 1); */
        /* printf("%c\n", BASE64_LOOKUP[second_base64]); */
        char third_base64 = (*(buffer + 1 + i * 3) & 0b00001111) << 2 | (*(buffer + 2 + i * 3) & 0b11000000) >> 6;
        /* print_bits(&third_base64, 1); */
        /* printf("%c\n", BASE64_LOOKUP[third_base64]); */
        char fourth_base64 = (*(buffer + 2 + i * 3) & 0b00111111);
        /* print_bits(&fourth_base64, 1); */
        /* printf("%c\n", BASE64_LOOKUP[fourth_base64]); */

        base64_string[i * 4] = BASE64_LOOKUP[first_base64];
        base64_string[i * 4 + 1] = BASE64_LOOKUP[second_base64];
        base64_string[i * 4 + 2] = BASE64_LOOKUP[third_base64];
        base64_string[i * 4 + 3] = BASE64_LOOKUP[fourth_base64];
    }

    for (i = 0; i < padding; i++) {
        base64_string[base64_size - 2 - i] = '=';
    }
    printf("base64 string %s\n", base64_string);

    return 0;
}
