#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "other_funcs.h"
#include "frequency.h"
#include "debug_func.h"

typedef unsigned char CodePage;
typedef unsigned char Debug;
typedef unsigned char Mode;


void InitializeDefaultOptions(Options* options){
    options->debug = 0;
    options->input_f = stdin;
    options->output_f = stdout;
    sprintf(options->input,"%c",'\0');
    sprintf(options->output,"%c",'\0');
    sprintf(options->coding,"%c",'\0');
    sprintf(options->mode_str,"%c",'\0');
}

void SetUserOptions(Options *options, Mode *mode , CodePage *code_page){
    if (options->input[0] != 0){
        if ((options->input_f = fopen(options->input , "rb")) == NULL){
            printf("\nCannot open input file\n");
            exit(1);
        }
    }
    if (options->output[0] != 0){
        if ((options->output_f = fopen(options->output , "rb")) == NULL){
            printf("\nCannot open output file\n");
            exit(1);
        }
    }

    if (!strcmp(options->coding , "UTF8") || !strcmp(options->coding , "utf8")) *code_page = UTF8;
    else if(!strcmp(options->coding , "UTF16") || !strcmp(options->coding , "utf16")) *code_page = UTF16;
    else if(!strcmp(options->coding , "UTF32") || !strcmp(options->coding , "utf32")) *code_page = UTF32;
    else if(!strcmp(options->coding , "MACCIR") || !strcmp(options->coding , "maccir")) *code_page = MACCIR;
    else if(!strcmp(options->coding , "WIN1251") || !strcmp(options->coding , "win1251")) *code_page = WIN1251;
    else if(!strcmp(options->coding , "ISO") || !strcmp(options->coding , "iso")) *code_page = ISO;
    else if(!strcmp(options->coding , "DOS") || !strcmp(options->coding , "dos")) *code_page = DOS;
    else if(!strcmp(options->coding , "KOI") || !strcmp(options->coding , "koi")) *code_page = KOI;

    if (!strcmp(options->mode_str , "DETECT") || !strcmp(options->mode_str , "detect")) *mode = DETECT;
    else if(!strcmp(options->mode_str , "TO_HEX") || !strcmp(options->mode_str , "hex")) *mode = TO_HEX;
    else if(!strcmp(options->mode_str , "TO_BINARY") || !strcmp(options->mode_str , "bin")) *mode = TO_BINARY;
    else if(!strcmp(options->mode_str , "TO_UTF8") || !strcmp(options->mode_str , "to_utf8")) *mode = TO_UTF8_HEX;
    else if(!strcmp(options->mode_str , "DECODE") || !strcmp(options->mode_str , "decode")) *mode = DECODE;

}

void PrintUsage(){
    printf("Usage:\n\t[program] [ad settings] [set setting]\n");
    printf("Options:\n\t-h | -help\t\tprint this message\n");
    printf("\t-d | -debug\t\tprint text byte statictic. Only for detect mode.\n");
    printf("\t-i | -input file\tyour input file. Default stdin.\n");
    printf("\t-o | -output file\tyour output file. Default stdout.\n");
    printf("\t-m | -mode mode\t\tdetect(coding), hex(print hex), bin(print binary), to_utf8(hex), decode. Default detect.\n");
    printf("\t-c | -coding code_page\tUTF8, UTF16, UTF32, maccir, win1251, iso, dos, koi.\n");
}

void ParseArguments(int argc, char *argv[] , Options *options){
    if(argc <= 1){
        printf("Launched %s without parameters \n", argv[0]);
        printf("For Help use -help or -h in first argument \n\n");
    }
    if(argc == 2 && (!strcmp(argv[1],"-help") || !strcmp(argv[1],"-h"))){
        PrintUsage();
        exit(1);
    }
    for(int i = 1; i < argc;){
        if(!strcmp(argv[i] , "-debug") || !strcmp(argv[i] , "-d")){
            options->debug = 1;
            ++i;
        } 
        else if(!strcmp(argv[i] , "-input") || !strcmp(argv[i] , "-i")){
            if (i + 1 != argc)
            {
                snprintf(options->input,MAX_FILE_NAME_SZ,"%s",argv[i + 1]);
                i+=2;
            }
            else{
                printf("\nIncorrect operation with parameter input file\n");
                exit(1);
            }
        }
        else if(!strcmp(argv[i] , "-output") || !strcmp(argv[i] , "-o")){
            if (i + 1 != argc)
            {
                snprintf(options->output,MAX_FILE_NAME_SZ,"%s",argv[i + 1]);
                i+=2;
            }
            else{
                printf("\nIncorrect operation with parameter output file\n");
                exit(1);
            }
        }
        else if(!strcmp(argv[i] , "-mode") || !strcmp(argv[i] , "-m")){
            if (i + 1 != argc)
            {
                snprintf(options->mode_str,20,"%s",argv[i + 1]);
                i+=2;
            }
            else{
                printf("\nIncorrect operation with parameter mode\n");
                exit(1);
            }
        }
        else if(!strcmp(argv[i] , "-coding") || !strcmp(argv[i] , "-c")){
            if (i + 1 != argc)
            {
                snprintf(options->coding,10,"%s",argv[i + 1]);
                i+=2;
            }
            else{
                printf("\nIncorrect operation with parameter coding\n");
                exit(1);
            }


        }
    }

}

int main(int argc, char* argv[]){
    size_t r12;
    Options options;
    InitializeDefaultOptions(&options);

    CodePage coding = NOCODING;
    Mode mode = DEFAULT;

    ParseArguments(argc , argv , &options);
    SetUserOptions(&options , &mode , &coding);

    switch (mode)
    {
    case DEFAULT:
        puts("Вы не выбрали режим в ручную, по умолчанию программа определит кодировку текста");
        puts("Запускаем программу на определение кодировки русского текста\n");
        GetAndPrintDetectedCodePage(&options,&coding);
        break;
    case DETECT:
        puts("Запускаем программу на определение кодировки русского текста\n");
        GetAndPrintDetectedCodePage(&options,&coding);
        break;
    case TO_UTF8_HEX:
        puts("Запускаем программу на перевод файла в hex-формат кодировки UTF-8\n");
        PrintTextInHexFormatUTF8Coding(&coding, options.input_f, options.output_f);
        break;
    case DECODE:
        puts("Запускаем программу на перевод файла в буквенный формат UTF-8\n");
        Decoding(options.input_f , options.output_f);
        break;
    case TO_HEX:
        puts("Запускаем программу на вывод файла в hex-формате\n");
        PrintHexFormat(options.input_f,options.output_f,16);
        break;
    case TO_BINARY:
        puts("Запускаем программу на вывод файла в bin-формате\n");
        PrintBinaryFormat(options.input_f , options.output_f, 8);
        break;
    default:
        puts("Укажите корректный режим для утилиты\n");
        break;
    }

    fclose(options.output_f);
    fclose(options.input_f);
} 