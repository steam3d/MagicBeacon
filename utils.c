#include "utils.h"

void furi_string_tolower(FuriString* string) {
    size_t len = furi_string_size(string);
    for(size_t i = 0; i < len; i++) {
        char c = furi_string_get_char(string, i);
        furi_string_set_char(string, i, (char)tolower((unsigned char)c));
    }
}

void furi_string_toupper(FuriString* string) {
    size_t len = furi_string_size(string);
    for(size_t i = 0; i < len; i++) {
        char c = furi_string_get_char(string, i);
        furi_string_set_char(string, i, (char)toupper((unsigned char)c));
    }
}

int hex_char_to_int(char c) {
    if('0' <= c && c <= '9') return c - '0';
    if('A' <= c && c <= 'F') return c - 'A' + 10;
    if('a' <= c && c <= 'f') return c - 'a' + 10;
    return -1;
}

int hex_string_to_bytes(const char* hex_str, uint8_t** out_bytes, size_t* out_len) {
    size_t len = strlen(hex_str);
    if(len % 2 != 0) return -1;

    size_t byte_count = len / 2;
    uint8_t* bytes = malloc(byte_count);
    if(!bytes) return -2;

    for(size_t i = 0; i < byte_count; i++) {
        int high = hex_char_to_int(hex_str[2 * i]);
        int low = hex_char_to_int(hex_str[2 * i + 1]);
        if(high < 0 || low < 0) {
            free(bytes);
            return -3;
        }
        bytes[i] = (high << 4) | low;
    }

    *out_bytes = bytes;

    *out_len = byte_count;
    return 0;
}

void reverse_bytes(uint8_t* data, size_t length) {
    for(size_t i = 0; i < length / 2; i++) {
        uint8_t tmp = data[i];
        data[i] = data[length - 1 - i];
        data[length - 1 - i] = tmp;
    }
}