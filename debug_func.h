#pragma once

typedef struct utf_struct StructForUTF;
typedef struct not_utf_struct StructForNotUTF;

//void PrintBytes(StructForUTF res , StructForNotUTF res1);

void PrintCounts(unsigned long OneBytesCodePages[] , unsigned long TotalBytesCount);

void PrintStatistic(unsigned PossibleBytes[]);
void PrintMostFrequenceBytes(unsigned Table[]);
void PrintLeastFrequenceBytes(unsigned Table[]);

void GetMostFrequence(unsigned Table[],unsigned  most[] , int sz_of_most,int start ,int end);
int GetLeastFrequence(unsigned Table[],unsigned least[],int sz_of_least,int start,int end );

void RightShift(unsigned arr[] ,unsigned new_start ,int start , int end);
unsigned GetMaxFromArr(unsigned arr[] , unsigned sz);