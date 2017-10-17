int hex_to_int(char hex_char);

// Convert an array of chars to hexademical string.
// Returns -1 if unsuccessful.
int char_array_to_hex_string(char *input, char *output);

char convert_two_hex_chars_to_eight_bits(char hex_char1, char hex_char2);

void validate_hex_str(char *hex_string);

void fill_buffer_with_bits_from_hex_string(char *buffer, char *hex_string);
