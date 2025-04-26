#include <stdio.h>
#include "frequency.h"
#include "debug_func.h"
#include <string.h>


typedef unsigned char CodePage;
typedef unsigned char Debug;


void PrintDetectedCodePage(CodePage coding){
    switch (coding)
    {
    case NOCODING:
        puts("Не получилось определить кодировку");
        break;
    case UTF8:
        puts("utf8");
        break;
    case UTF16:
        puts("utf16");
        break;
    case UTF32:
        puts("utf32");
        break;
    case MACCIR:
        puts("maccyrillic");
        break;
    case WIN1251:
        puts("windows1251");
        break;
    case DOS:
        puts("dos");
        break;
    case ISO:
        puts("iso");
        break;
    case KOI:
        puts("koi8r");
        break;

    default:
    puts("ЧТО?");
        break;
    }
}

CodePage TryToGetUTFCoding( unsigned ByteCountTable[] , unsigned long TotalBytesCount){
    CodePage coding = NOCODING;
    unsigned most[MOST_PREFERRED_ARRAY_SZ_FOR_MOST_FREQUENCE];
    GetMostFrequence(ByteCountTable , most , MOST_PREFERRED_ARRAY_SZ_FOR_MOST_FREQUENCE , 0x00 , 0xff);
    // fe and ff - two last bytes in array in UTF32 == 1 both
    if(UTF_16_INTERVAL(most[0]) && UTF_16_INTERVAL(most[1]) && ByteCountTable[0xfe] == 1 && ByteCountTable[0xff] == 1){
        coding = UTF32;
    }
    else if(UTF_16_INTERVAL(most[0]) && UTF_16_INTERVAL(most[1])){
        coding = UTF16;
    }
    else if(TotalBytesCount <= STABLE_DETECTION_LEVEL && (UTF_8_INTERVAl(most[0]) || UTF_8_INTERVAl(most[1])) ){
        coding = UTF8;
    }
    else if(UTF_8_INTERVAl(most[0]) && UTF_8_INTERVAl(most[1])){
        coding = UTF8;
    }
    return coding;
}

CodePage GetMiniCoding(unsigned long *sums){
    CodePage result = NOCODING;

    unsigned long max = 0;
    int ind = 0;

    for (int i = 0; i < 5; ++i)
    {
        if(max < sums[i]){
            max = sums[i];
            ind = i;
        } 

    }
    result = ind;
    return result;

}

void GetCoincidences(unsigned ByteCountTable[] , unsigned result[]){
    unsigned most[MOST_PREFERRED_ARRAY_SZ_FOR_MOST_FREQUENCE];
    //unsigned least[3];
    GetMostFrequence(ByteCountTable , most ,MOST_PREFERRED_ARRAY_SZ_FOR_MOST_FREQUENCE , 0x80 , 0xff);

    for (size_t i = 0; i < MOST_PREFERRED_ARRAY_SZ_FOR_MOST_FREQUENCE; ++i)
    {
        if (MAC_MOST_FREQUENCY_VALUE(most[i]))
        {
            result[MACCIR]++;
        }
        if (WINDOWS_MOST_FREQUENCY_VALUE(most[i]))
        {
            result[WIN1251]++;
        }
        if (ISO_MOST_FREQUENCY_VALUE(most[i]))
        {
            result[ISO]++;
        }
        if (KOI8R_MOST_FREQUENCY_VALUE(most[i]))
        {
            result[KOI]++;
        }
        if (DOS_MOST_FREQUENCY_VALUE(most[i]))
        {
            result[DOS]++;
        }   
    }
}


CodePage GetCodingByCoincidences(unsigned ByteCountTable[]){
    CodePage coding = NOCODING;
    
    unsigned Coincidences[NUMBER_OF_ONE_BYTE_RU_CODE_PAGES] = {0};
    GetCoincidences(ByteCountTable , Coincidences);
    unsigned max = GetMaxFromArr(Coincidences , 5);
    if (max == Coincidences[MACCIR] && max == Coincidences[WIN1251])
    {
        if (ByteCountTable[0xdf] > ByteCountTable[0xff]) return MACCIR;
        else return WIN1251;
    }
    else if(max == Coincidences[ISO]) return ISO;
    else if(max == Coincidences[KOI]) return KOI;
    else if(max == Coincidences[DOS]) return DOS;
    
    return coding;
}

void ProcessInputFile(unsigned ByteCountTable[] ,unsigned long OneBytesCodePages[],unsigned long *TotalBytesCount,FILE *input){
    int c = 0;
    while ((c = fgetc(input)) != EOF)
    {
        ++ByteCountTable[c];
        ++(*TotalBytesCount);

        if (FULL_MAC_INTERVAL(c)) ++OneBytesCodePages[MACCIR];
        if (FULL_WINDOWS_INTERVAL(c)) ++OneBytesCodePages[WIN1251];
        if (FULL_DOS_INTERVAL(c)) ++OneBytesCodePages[DOS];
        if (FULL_ISO_INTERVAL(c)) ++OneBytesCodePages[ISO];
        if (FULL_KOI_INTERVAl(c)) ++OneBytesCodePages[KOI];
    }
}

void DetectCodePage(unsigned ByteCountTable[],unsigned long OneBytesCodePages[],unsigned long *TotalBytesCount,CodePage *result){
    //Значение 300 обозначает количество байт чуть большее чем в алфавите(когда частотность бесполезна)
    //Получил значением путем опытов 

    *result = TryToGetUTFCoding(ByteCountTable , *TotalBytesCount);

    if (*result != NOCODING) return;
    

    if(*TotalBytesCount > STABLE_DETECTION_LEVEL) {
        *result = GetCodingByCoincidences(ByteCountTable);
    }
    else if (*TotalBytesCount <= STABLE_DETECTION_LEVEL){
        // Try to determine anyway even if input text is too short
        *result = GetMiniCoding(OneBytesCodePages);
    }
}

void GetAndPrintDetectedCodePage(Options *options , CodePage *coding){

    unsigned long TotalBytesCount = 0; 
    unsigned ByteCountTable[256] = {0};
    unsigned long OneBytesCodePages[NUMBER_OF_ONE_BYTE_RU_CODE_PAGES] = {0};

    ProcessInputFile(ByteCountTable, OneBytesCodePages, &TotalBytesCount, options->input_f);
    DetectCodePage(ByteCountTable, OneBytesCodePages, &TotalBytesCount, coding);
    PrintDetectedCodePage(*coding);

    if (options->debug){
        PrintStatistic(ByteCountTable);
        PrintMostFrequenceBytes(ByteCountTable);
        PrintLeastFrequenceBytes(ByteCountTable);
        PrintCounts(OneBytesCodePages,TotalBytesCount);
    }
}