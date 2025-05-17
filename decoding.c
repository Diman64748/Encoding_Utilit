#include <stdio.h>

void Decoding(FILE *input , FILE *output){
    int c;
    unsigned char ru_c[3] = {0xd0 , 0x90 , 0x00};

    int count_bytes = 0;

    while(fscanf(input,"%x",&c) != EOF){
        if (c >= 0x80)
        {
            ru_c[count_bytes++] = c;
        }
        else if(c < 0x80)fprintf(output,"%c",c);

        if (count_bytes >= 2){
            fprintf(output,"%s",ru_c);

            count_bytes = 0;
        } 

    }
      
    
}

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




