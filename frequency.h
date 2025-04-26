#pragma once
typedef unsigned char CodePage;
typedef unsigned char Debug;
typedef unsigned char Mode;

#define MAC_MOST_FREQUENCY_VALUE(x) (x==0xee||x==0xe5||x==0xe0||x==0xe8||x==0xed||x==0xf2||x==0xf1||x==0xf0||x==0xe2||x==0xeb)
#define WINDOWS_MOST_FREQUENCY_VALUE(x) (x==0xee||x==0xe5||x==0xe0||x==0xe8||x==0xed||x==0xf2||x==0xf1||x==0xf0||x==0xe2||x==0xeb)
#define DOS_MOST_FREQUENCY_VALUE(x) (x==0xae||x==0xa5||x==0xa0||x==0xa8||x==0xad||x==0xe2||x==0xe1||x==0xe0||x==0xa2||x==0xab)
#define ISO_MOST_FREQUENCY_VALUE(x) (x==0xde||x==0xd5||x==0xd0||x==0xd8||x==0xdd||x==0xe2||x==0xe1||x==0xe0||x==0xd2||x==0xdb)
#define KOI8R_MOST_FREQUENCY_VALUE(x) (x==0xcf||x==0xc5||x==0xc1||x==0xc9||x==0xce||x==0xd4||x==0xd3||x==0xd2||x==0xd7||x==0xcc)

#define MOST_PREFERRED_ARRAY_SZ_FOR_LEAST_FREQUENCE 10
#define MOST_PREFERRED_ARRAY_SZ_FOR_MOST_FREQUENCE 10
#define NUMBER_OF_ONE_BYTE_RU_CODE_PAGES 5
#define STABLE_DETECTION_LEVEL 300

#define UTF_16_INTERVAL(x) (x == 0x00 || x == 0x04)
#define UTF_8_INTERVAl(x) (x == 0xd0 || x == 0xd1 )


#define FULL_MAC_INTERVAL(x) ((0x80 <= x && x <= 0x9f) || (0xdd <= x && x <= 0xfe))
#define FULL_WINDOWS_INTERVAL(x) ((0xc0 <= x && x <= 0xff) || x == 0xb8 || x == 0xa8)
#define FULL_DOS_INTERVAL(x) ((0x80 <= x && x <= 0xaf) || (0xe0 <= x && x <= 0xf1))
#define FULL_ISO_INTERVAL(x) ((0xb0 <= x && x <= 0xef) || x == 0xa1 || x == 0xf1) 
#define FULL_KOI_INTERVAl(x) ((0xc0 <= x && x <= 0xff) || x == 0xa3 || x == 0xb3)


#define NOCODING 8
#define MACCIR 0
#define WIN1251 1
#define DOS 2
#define ISO 3
#define KOI 4
#define UTF8 5
#define UTF16 6
#define UTF32 7

#define MAX_FILE_NAME_SZ 200

void PrintTextInHexFormatUTF8Coding(CodePage *coding , FILE *input, FILE *output);

typedef struct Start_options
{
    Debug debug;

    FILE* input_f;
    FILE* output_f;

    // input_file???
    char input[MAX_FILE_NAME_SZ]; /// А если я хочу указать полный путь к файлу????
    // output_file???   
    char output[MAX_FILE_NAME_SZ];

    char coding[10];
    char mode_str[20];
    
}Options;

void GetAndPrintDetectedCodePage(Options *options , CodePage *coding);