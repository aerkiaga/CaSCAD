#include "strutils.h"
#include <libgen.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

char *get_empty_string() {
    char *r = (char *) malloc(1);
    r[0] = '\0';
    return r;
}

char *append_string(char *dst, const char *src) {
    return strcat(realloc(dst, strlen(dst) + strlen(src) + 1), src);
}

/**
 * Encode a code point using UTF-8
 * 
 * @author Ondřej Hruška <ondra@ondrovo.com>
 * @license MIT
 * 
 * @param out - output buffer (min 5 characters), will be 0-terminated
 * @param utf - code point 0-0x10FFFF
 * @return number of bytes on success, 0 on failure (also produces U+FFFD, which uses 3 bytes)
 */
int utf8_encode(char *out, uint32_t utf)
{
  if (utf <= 0x7F) {
    // Plain ASCII
    out[0] = (char) utf;
    out[1] = 0;
    return 1;
  }
  else if (utf <= 0x07FF) {
    // 2-byte unicode
    out[0] = (char) (((utf >> 6) & 0x1F) | 0xC0);
    out[1] = (char) (((utf >> 0) & 0x3F) | 0x80);
    out[2] = 0;
    return 2;
  }
  else if (utf <= 0xFFFF) {
    // 3-byte unicode
    out[0] = (char) (((utf >> 12) & 0x0F) | 0xE0);
    out[1] = (char) (((utf >>  6) & 0x3F) | 0x80);
    out[2] = (char) (((utf >>  0) & 0x3F) | 0x80);
    out[3] = 0;
    return 3;
  }
  else if (utf <= 0x10FFFF) {
    // 4-byte unicode
    out[0] = (char) (((utf >> 18) & 0x07) | 0xF0);
    out[1] = (char) (((utf >> 12) & 0x3F) | 0x80);
    out[2] = (char) (((utf >>  6) & 0x3F) | 0x80);
    out[3] = (char) (((utf >>  0) & 0x3F) | 0x80);
    out[4] = 0;
    return 4;
  }
  else { 
    // error - use replacement character
    out[0] = (char) 0xEF;  
    out[1] = (char) 0xBF;
    out[2] = (char) 0xBD;
    out[3] = 0;
    return 0;
  }
}

char *encode_utf8_escape(const char *escape) {
    size_t digit_count = escape[1] == 'x' ? 2 : escape[1] == 'u' ? 4 : 6;
    unsigned int value = 0;
    size_t i;
    for(i = 0; i < digit_count; i++) {
        value *= 16;
        unsigned int digit = escape[i + 2] - '0';
        if(digit > 9) digit = escape[i + 2] - 'A';
        if(digit > 9) digit = escape[i + 2] - 'a';
        value += digit;
    }
    char *r = (char *) malloc(5);
    size_t actual_size = utf8_encode(r, value);
    r[actual_size] = '\0';
    return r;
}

char *path_basename(const char *path) {
    char *path_copy = strdup(path);
    const char *base = basename(path_copy);
    char *base_copy = strdup(base);
    free(path_copy);
    return base_copy;
}

char *path_dirname(const char *path) {
    char *path_copy = strdup(path);
    const char *dir = dirname(path_copy);
    char *dir_copy = strdup(dir);
    free(path_copy);
    return dir_copy;
}

char *path_realpath(const char *path) {
    return realpath(path, NULL);
}

const char *path_extension(const char *path) {
    const char *dot = strrchr(path, '.');
    if(!dot) return "";
    const char *fail = strchr(dot, '/');
    if(fail) return "";
    return dot + 1;
}

