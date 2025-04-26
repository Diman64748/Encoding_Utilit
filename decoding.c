#include <stdio.h>
#include "other_funcs.h"

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




