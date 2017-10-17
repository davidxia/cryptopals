#include <stdio.h>
#include <stdlib.h>
#include <string.h>


const char HEX_LOOKUP[] = "0123456789abcdef";

int hex_to_int(char hex_char) {
    const char *loc = strchr(HEX_LOOKUP, hex_char);
    if (loc) {
        return loc - HEX_LOOKUP;
    }

    return -1;
}

int char_array_to_hex_string(char *input, char *output) {
    int len = strlen(input);

    int i;
    for (i = 0; i < strlen(input); i++) {
        output[2 * i] = HEX_LOOKUP[input[i] >> 4];
        output[2 * i + 1] = HEX_LOOKUP[input[i] & 0b00001111];
    }

    return 0;
}

char convert_two_hex_chars_to_eight_bits(char hex_char1, char hex_char2) {
    char c = (hex_to_int(hex_char1) << 4) | (hex_to_int(hex_char2));
    return c;
}

void validate_hex_str(char *hex_string) {
    int len = strlen(hex_string);
    if (len % 2 != 0) {
        printf("Hexadecimal string must have an even number of characters.\n");
        exit(1);
    }

    int i;
    for (i = 0; i < len; i++) {
        char c = *(hex_string + i);
        if (strchr(HEX_LOOKUP, c) == NULL) {
            printf("Input hex string contains invalid char '%c'\n", c);
            exit(1);
        }
    }
}

void fill_buffer_with_bits_from_hex_string(char *buffer, char *hex_string) {
    char *hex_char;
    int i = 0;
    for (hex_char = hex_string; *hex_char != '\0'; hex_char += 2) {
        buffer[i] = convert_two_hex_chars_to_eight_bits(*hex_char, *(hex_char + 1));
        i++;
        if (*(hex_char + 1) == '\0') {
            break;
        }
    }
}
