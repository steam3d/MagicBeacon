
#pragma once
#include <furi.h>

void furi_string_toupper(FuriString* string);
void furi_string_tolower(FuriString* string);
int hex_char_to_int(char c);
int hex_string_to_bytes(const char* hex_str, uint8_t** out_bytes, size_t* out_len);
void reverse_bytes(uint8_t* data, size_t length);