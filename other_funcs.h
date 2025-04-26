#include <stdio.h>
void PrintHexFormat(FILE *input_f , FILE *output_f , unsigned count_of_bytes_in_str);
void PrintBinaryFormat(FILE *input_f , FILE *output_f , unsigned count_of_bytes_in_str);

#define TO_HEX 5
#define TO_BINARY 4
#define TO_UTF8_HEX 3
#define DECODE 2
#define DETECT 1
#define DEFAULT 0

void Decoding(FILE *input , FILE *output);


