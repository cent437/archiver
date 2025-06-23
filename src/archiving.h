#include <stdio.h>
#include <stdbool.h>

bool isDigit(char symbol);
long long get_filesize(FILE *f);
void compress(FILE *f, long long file_size);
void decompress(FILE *f_compressed, FILE *f_decompressed, long long compressed_size);