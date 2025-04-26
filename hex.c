#include <stdio.h>
void PrintHexFormat(FILE *input_f , FILE *output_f , unsigned count_of_bytes_in_str){
    unsigned counter = 0;
    int c = 0;
        while((c = fgetc(input_f)) != EOF){
            fprintf(output_f , "%02x ", c);
            ++counter;
            if (counter == count_of_bytes_in_str)
            {
                fprintf(output_f , "\n");
                counter = 0;
            }
        
        }
}

void PrintBinaryFormat(FILE *input_f , FILE *output_f , unsigned count_of_bytes_in_str){
    unsigned counter = 0;
    int c = 0;
        while((c = fgetc(input_f)) != EOF){
            fprintf(output_f , "%08b ", c);
            ++counter;
            if (counter == count_of_bytes_in_str)
            {
                fprintf(output_f , "\n");
                counter = 0;
            }
        
        }
}