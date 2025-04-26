#include <stdio.h>

#include "debug_func.h"
#include "frequency.h"





void PrintCounts(unsigned long OneBytesCodePages[] , unsigned long TotalBytesCount){
    
    printf("Dos %lu\tIso %lu\tKoi %lu\nMac %lu\tWind %lu\n",OneBytesCodePages[DOS] , OneBytesCodePages[ISO] , OneBytesCodePages[KOI] , OneBytesCodePages[MACCIR] , OneBytesCodePages[WIN1251]);
    printf("%lu\n\n",TotalBytesCount);

}

void PrintStatistic(unsigned PossibleBytes[]){
    // print("Count of byte values found in input")
    puts("\n");
    for(int i = 0 ; i < 256 ; ++i){
        printf("%02x\t%08b\t%u\n",i ,i, PossibleBytes[i]);
    }
}


void GetMostFrequence(unsigned Table[],unsigned  most[] ,int sz_of_most ,int start ,int end){
    for (int i = 0; i < sz_of_most; i++)
    {
        most[i] = start + i;
    }
    

    for (int i = start ; i <= end ; ++i)
    {
        for (int j = 0; j < sz_of_most; ++j)
        {
            if (Table[i] > Table[most[j]]){
                RightShift(most , i , j , sz_of_most - 1);
                break;
            }
        }
    }    
}

int GetLeastFrequence(unsigned Table[],unsigned least[],int sz_of_least,int start,int end ){
    int return_count = 0;
    for (int i = start ,j = 0; i <= end && j < sz_of_least; ++i)
    {

        if (Table[i] > 0){
            least[j] = i;
            ++j;
            ++return_count;
        }
    }
    if (return_count != sz_of_least) return return_count;
    

    for (int i = start ; i <= end ; ++i)
    {
        for (int j = 0; j < sz_of_least; ++j)
        {
            if (Table[i] < Table[least[j]] && Table[i] != 0){
                RightShift(least , i , j , sz_of_least - 1);
                break;
            }
        }
    }
    return return_count;    
}

void RightShift(unsigned arr[] ,unsigned new_start ,int start , int end){
    for (int i = end; i > start; --i)
    {
        arr[i] = arr[i - 1];
    }
    arr[start] = new_start;
    
}


unsigned GetMaxFromArr(unsigned arr[] , unsigned sz){
    unsigned max = 0;
    for (unsigned i = 0; i < sz; i++)
    {
        if (max < arr[i]) max = arr[i]; 
    }
    return max;
    
}

void PrintMostFrequenceBytes(unsigned Table[]){
    unsigned most_all[MOST_PREFERRED_ARRAY_SZ_FOR_MOST_FREQUENCE];
    puts("\nНаиболее частые байты во всем массиве:");
    GetMostFrequence(Table ,most_all,MOST_PREFERRED_ARRAY_SZ_FOR_MOST_FREQUENCE , 0x00 , 0xff);
    for (int i = 0; i < MOST_PREFERRED_ARRAY_SZ_FOR_MOST_FREQUENCE; i++)
    {
        printf("%02x ",most_all[i]);
    }
    
    puts("\nНаиболее частые байты в массиве после ascii символов:");
    GetMostFrequence(Table ,most_all,MOST_PREFERRED_ARRAY_SZ_FOR_MOST_FREQUENCE , 0x80 , 0xff);
    for (int i = 0; i < MOST_PREFERRED_ARRAY_SZ_FOR_MOST_FREQUENCE; i++)
    {
        printf("%02x ",most_all[i]);
    }
    puts("\n");


}

void PrintLeastFrequenceBytes(unsigned Table[]){
    unsigned least_all[MOST_PREFERRED_ARRAY_SZ_FOR_LEAST_FREQUENCE];
    puts("\nНаименее частые байты во всем массиве:");
    GetLeastFrequence(Table ,least_all,MOST_PREFERRED_ARRAY_SZ_FOR_LEAST_FREQUENCE , 0x00 , 0xff);
    for (int i = 0; i < MOST_PREFERRED_ARRAY_SZ_FOR_LEAST_FREQUENCE; i++)
    {
        printf("%02x ",least_all[i]);
    }
    
    puts("\nНаименее частые байты в массиве после ascii символов:");
    GetLeastFrequence(Table ,least_all,MOST_PREFERRED_ARRAY_SZ_FOR_LEAST_FREQUENCE , 0x80 , 0xff);
    for (int i = 0; i < MOST_PREFERRED_ARRAY_SZ_FOR_LEAST_FREQUENCE; i++)
    {
        printf("%02x ",least_all[i]);
    }
    puts("\n");


}