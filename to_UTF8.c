#include <stdio.h>
#include "frequency.h"
#include "other_funcs.h"

typedef unsigned char CodePage;

typedef struct utf_struct_for_decoding{
    unsigned char left;
    unsigned char right;
}UTF8Struct;

typedef struct utf32_struct_for_decoding{
    unsigned char first;
    unsigned char second;
    unsigned char third;
    unsigned char fourth;
}UTF32Struct;

UTF8Struct unicode_to_UTF(void* unicode){
    UTF8Struct st;
    unsigned char* byte = (unsigned char*)unicode;

    st.left = byte[1];
    st.right = byte[0];

    unsigned char left_two_bytes_in_right = st.right & 0xc0;
    
    switch (left_two_bytes_in_right)
    {
    case 0x00:
        st.left <<= 2;
        st.left += 0xc0;
        break;
    case 0x80:
        st.left <<= 2;
        st.left += 0xc0;
        st.left += 0x02;
        break;
    case 0x40:
        st.left <<= 2;
        st.left += 0xc0;
        st.left += 0x01;
        break;
    case 0xc0:
        st.left <<= 2;
        st.left += 0xc0;
        st.left += 0x03;
        break;
    default:
        break;
    }

    st.right &= 0x3f; //operations with bits
    st.right += 0x80;

    return st;

}

UTF8Struct unicode_to_UTF_for_UTF16(UTF8Struct st){
    unsigned char left_two_bytes_in_right = st.right & 0xc0;
    
    switch (left_two_bytes_in_right)
    {
    case 0x00:
        st.left <<= 2;
        st.left += 0xc0;
        break;
    case 0x80:
        st.left <<= 2;
        st.left += 0xc0;
        st.left += 0x02;
        break;
    case 0x40:
        st.left <<= 2;
        st.left += 0xc0;
        st.left += 0x01;
        break;
    case 0xc0:
        st.left <<= 2;
        st.left += 0xc0;
        st.left += 0x03;
        break;
    default:
        break;
    }

    st.right &= 0x3f; //operations with bits
    st.right += 0x80;

    return st;

}

UTF8Struct unicode_to_UTF_for_UTF32(UTF32Struct st_32){

    UTF8Struct st;

    st.left = st_32.third;
    st.right = st_32.fourth;

    unsigned char left_two_bytes_in_right = st.right & 0xc0;
    
    switch (left_two_bytes_in_right)
    {
    case 0x00:
        st.left <<= 2;
        st.left += 0xc0;
        break;
    case 0x80:
        st.left <<= 2;
        st.left += 0xc0;
        st.left += 0x02;
        break;
    case 0x40:
        st.left <<= 2;
        st.left += 0xc0;
        st.left += 0x01;
        break;
    case 0xc0:
        st.left <<= 2;
        st.left += 0xc0;
        st.left += 0x03;
        break;
    default:
        break;
    }

    st.right &= 0x3f; //operations with bits
    st.right += 0x80;

    return st;
}



void GetCodePageTableWindows(unsigned short WindCode[]){
    for (int  i = 0; i < 0x80; ++i)
    {
        WindCode[i] = i;
    }
    WindCode[0x80] = 0x0402;
    WindCode[0x81] = 0x0403;
    WindCode[0x82] = 0x201A;
    WindCode[0x83] = 0x0453;
    WindCode[0x84] = 0x201E;
    WindCode[0x85] = 0x2026;
    WindCode[0x86] = 0x2020;
    WindCode[0x87] = 0x2021;
    WindCode[0x88] = 0x20AC;
    WindCode[0x89] = 0x2030;
    WindCode[0x8a] = 0x0409;
    WindCode[0x8b] = 0x2039;
    WindCode[0x8c] = 0x040A;
    WindCode[0x8d] = 0x040C;
    WindCode[0x8e] = 0x040B;
    WindCode[0x8f] = 0x040F;
    WindCode[0x90] = 0x0452;
    WindCode[0x91] = 0x2018;
    WindCode[0x92] = 0x2019;
    WindCode[0x93] = 0x201C;
    WindCode[0x94] = 0x201D;
    WindCode[0x95] = 0x2022;
    WindCode[0x96] = 0x2013;
    WindCode[0x97] = 0x2014;
    WindCode[0x98] = 0x0000;
    WindCode[0x99] = 0x2122;
    WindCode[0x9a] = 0x0459;
    WindCode[0x9b] = 0x203A;
    WindCode[0x9c] = 0x045A;
    WindCode[0x9d] = 0x045C;
    WindCode[0x9e] = 0x045B;
    WindCode[0x9f] = 0x045F;
    WindCode[0xa0] = 0x00A0;
    WindCode[0xa1] = 0x040E;
    WindCode[0xa2] = 0x045E;
    WindCode[0xa3] = 0x0408;
    WindCode[0xa4] = 0x00A4;
    WindCode[0xa5] = 0x0490;
    WindCode[0xa6] = 0x00A6;
    WindCode[0xa7] = 0x00A7;
    WindCode[0xa8] = 0x0401;
    WindCode[0xa9] = 0x00A9;
    WindCode[0xaa] = 0x0404;
    WindCode[0xab] = 0x00AB;
    WindCode[0xac] = 0x00AC;
    WindCode[0xad] = 0x00AD;
    WindCode[0xae] = 0x00AE;
    WindCode[0xaf] = 0x0407;
    WindCode[0xb0] = 0x00B0;
    WindCode[0xb1] = 0x00B1;
    WindCode[0xb2] = 0x0406;
    WindCode[0xb3] = 0x0456;
    WindCode[0xb4] = 0x0491;
    WindCode[0xb5] = 0x00B5;
    WindCode[0xb6] = 0x00B6;
    WindCode[0xb7] = 0x00B7;
    WindCode[0xb8] = 0x0451;
    WindCode[0xb9] = 0x2116;
    WindCode[0xba] = 0x0454;
    WindCode[0xbb] = 0x00BB;
    WindCode[0xbc] = 0x0458;
    WindCode[0xbd] = 0x0405;
    WindCode[0xbe] = 0x0455;
    WindCode[0xbf] = 0x0457;

    WindCode[0xC0] = 0x0410;
    for (int i = 0xC1; i <= 0xff; ++i)
    {
        WindCode[i] = 0x0410 + (i - 0xc0);
    }

}

void GetCodePageTableISO(unsigned short ISOCode[]){
    for (int i = 0; i <= 0xa0; i++)
    {
        ISOCode[i] = i;
    }

    for (int i = 0xa1; i <= 0xff; i++)
    {
        ISOCode[i] = 0x0401 + (i - 0xa1);
    }
    
    

}


void GetCodePageTableKoi8r(unsigned short KOICode[]){
    for (int i = 0; i <= 0x7f; i++)
    {
        KOICode[i] = i;
    }
    KOICode[0x80] = 0x2500;
    KOICode[0x81] = 0x2502;
    KOICode[0x82] = 0x250c;
    KOICode[0x83] = 0x2501;
    KOICode[0x84] = 0x2514;
    KOICode[0x85] = 0x2518;
    KOICode[0x86] = 0x251c;
    KOICode[0x87] = 0x2524;
    KOICode[0x88] = 0x252c;
    KOICode[0x89] = 0x2534;
    KOICode[0x8a] = 0x253c;
    KOICode[0x8b] = 0x2580;
    KOICode[0x8c] = 0x2584;
    KOICode[0x8d] = 0x2588;
    KOICode[0x8e] = 0x258c;
    KOICode[0x8f] = 0x2590;

    KOICode[0x90] = 0x2591;
    KOICode[0x91] = 0x2592;
    KOICode[0x92] = 0x2593;
    KOICode[0x93] = 0x2320;
    KOICode[0x94] = 0x25a0;
    KOICode[0x95] = 0x2219;
    KOICode[0x96] = 0x221a;
    KOICode[0x97] = 0x2248;
    KOICode[0x98] = 0x2264;
    KOICode[0x99] = 0x2265;
    KOICode[0x9a] = 0x00a0;
    KOICode[0x9b] = 0x2321;
    KOICode[0x9c] = 0x00b0;
    KOICode[0x9d] = 0x00b2;
    KOICode[0x9e] = 0x00b7;
    KOICode[0x9f] = 0x00f7;

    for (int i = 0xa0; i <= 0xa2; i++)
    {
        KOICode[i] = 0x2550 + (i - 0xa0);
    }
    KOICode[0xa3] = 0x0451;

    for (int i = 0xa4; i <= 0xb2; i++)
    {
        KOICode[i] = 0x2553 + (i - 0xa4);
    }

    KOICode[0xb3] = 0x0401;

    for (int i = 0xb4; i <= 0xbe; i++)
    {
        KOICode[i] = 0x2562 + (i - 0xb4);
    }
    KOICode[0xbf] = 0x00a9;

    KOICode[0xc0] = 0x044e;
    KOICode[0xc1] = 0x0430;
    KOICode[0xc2] = 0x0431;
    KOICode[0xc3] = 0x0446;
    KOICode[0xc4] = 0x0434;
    KOICode[0xc5] = 0x0435;
    KOICode[0xc6] = 0x0444;
    KOICode[0xc7] = 0x0433;
    KOICode[0xc8] = 0x0445;
    KOICode[0xc9] = 0x0438;
    KOICode[0xca] = 0x0439;
    KOICode[0xcb] = 0x043a;
    KOICode[0xcc] = 0x043b;
    KOICode[0xcd] = 0x043c;
    KOICode[0xce] = 0x043d;
    KOICode[0xcf] = 0x043e;

    KOICode[0xd0] = 0x043f;
    KOICode[0xd1] = 0x044f;
    KOICode[0xd2] = 0x0440;
    KOICode[0xd3] = 0x0441;
    KOICode[0xd4] = 0x0442;
    KOICode[0xd5] = 0x0443;
    KOICode[0xd6] = 0x0436;
    KOICode[0xd7] = 0x0432;
    KOICode[0xd8] = 0x044c;
    KOICode[0xd9] = 0x044b;
    KOICode[0xda] = 0x0437;
    KOICode[0xdb] = 0x0448;
    KOICode[0xdc] = 0x044d;
    KOICode[0xdd] = 0x0449;
    KOICode[0xde] = 0x0447;
    KOICode[0xdf] = 0x044a;

    KOICode[0xe0] = 0x042e;
    KOICode[0xe1] = 0x0410;
    KOICode[0xe2] = 0x0411;
    KOICode[0xe3] = 0x0426;
    KOICode[0xe4] = 0x0414;
    KOICode[0xe5] = 0x0415;
    KOICode[0xe6] = 0x0424;
    KOICode[0xe7] = 0x0413;
    KOICode[0xe8] = 0x0425;
    KOICode[0xe9] = 0x0418;
    KOICode[0xea] = 0x0419;
    KOICode[0xeb] = 0x041a;
    KOICode[0xec] = 0x041b;
    KOICode[0xed] = 0x041c;
    KOICode[0xee] = 0x041d;
    KOICode[0xef] = 0x041e;

    KOICode[0xf0] = 0x041f;
    KOICode[0xf1] = 0x042f;
    KOICode[0xf2] = 0x0420;
    KOICode[0xf3] = 0x0421;
    KOICode[0xf4] = 0x0422;
    KOICode[0xf5] = 0x0423;
    KOICode[0xf6] = 0x0416;
    KOICode[0xf7] = 0x0412;
    KOICode[0xf8] = 0x042c;
    KOICode[0xf9] = 0x042b;
    KOICode[0xfa] = 0x0417;
    KOICode[0xfb] = 0x0428;
    KOICode[0xfc] = 0x042d;
    KOICode[0xfd] = 0x0429;
    KOICode[0xfe] = 0x0427;
    KOICode[0xff] = 0x042a;

    
    
}

void GetCodePageTableMac(unsigned short MACCode[]){
    for (int i = 0; i <= 0x7f; i++)
    {
        MACCode[i] = i;
    }

    for (int i = 0x80; i <= 0x9f; i++)
    {
        MACCode[i] = 0x0410 + (i - 0x80);
    }
    MACCode[0xa0] = 0x2020;
    MACCode[0xa1] = 0x00b0;
    MACCode[0xa2] = 0x00a2;
    MACCode[0xa3] = 0x00a3;
    MACCode[0xa4] = 0x00a7;
    MACCode[0xa5] = 0x2022;
    MACCode[0xa6] = 0x00b6;
    MACCode[0xa7] = 0x0406;
    MACCode[0xa8] = 0x00ae;
    MACCode[0xa9] = 0x00a9;
    MACCode[0xaa] = 0x2122;
    MACCode[0xab] = 0x0402;
    MACCode[0xac] = 0x0452;
    MACCode[0xad] = 0x2260;
    MACCode[0xae] = 0x0403;
    MACCode[0xaf] = 0x0453;
    
    MACCode[0xb0] = 0x221e;
    MACCode[0xb1] = 0x00b1;
    MACCode[0xb2] = 0x2264;
    MACCode[0xb3] = 0x2265;
    MACCode[0xb4] = 0x0456;
    MACCode[0xb5] = 0x00b5;
    MACCode[0xb6] = 0x2202;
    MACCode[0xb7] = 0x0408;
    MACCode[0xb8] = 0x0404;
    MACCode[0xb9] = 0x0454;
    MACCode[0xba] = 0x0407;
    MACCode[0xbb] = 0x0457;
    MACCode[0xbc] = 0x0409;
    MACCode[0xbd] = 0x0459;
    MACCode[0xbe] = 0x040A;
    MACCode[0xbf] = 0x045a;
    
    MACCode[0xc0] = 0x0458;
    MACCode[0xc1] = 0x0405;
    MACCode[0xc2] = 0x00ac;
    MACCode[0xc3] = 0x221a;
    MACCode[0xc4] = 0x0192;
    MACCode[0xc5] = 0x2248;
    MACCode[0xc6] = 0x2206;
    MACCode[0xc7] = 0x00ab;
    MACCode[0xc8] = 0x00bb;
    MACCode[0xc9] = 0x2026;
    MACCode[0xca] = 0x00a0;
    MACCode[0xcb] = 0x040b;
    MACCode[0xcc] = 0x045b;
    MACCode[0xcd] = 0x040c;
    MACCode[0xce] = 0x045c;
    MACCode[0xcf] = 0x0455;
    
    MACCode[0xd0] = 0x2013;
    MACCode[0xd1] = 0x2014;
    MACCode[0xd2] = 0x201c;
    MACCode[0xd3] = 0x201d;
    MACCode[0xd4] = 0x2018;
    MACCode[0xd5] = 0x2019;
    MACCode[0xd6] = 0x00f7;
    MACCode[0xd7] = 0x201e;
    MACCode[0xd8] = 0x040e;
    MACCode[0xd9] = 0x045e;
    MACCode[0xda] = 0x040f;
    MACCode[0xdb] = 0x045f;
    MACCode[0xdc] = 0x2116;
    MACCode[0xdd] = 0x0401;
    MACCode[0xde] = 0x0451;
    MACCode[0xdf] = 0x044f;
    
    for (int i = 0xe0; i <= 0xfe; i++)
    {
        MACCode[i] = 0x0430 + (i - 0xe0);
    }

    MACCode[0xff] = 0x00a4;
    
    
    


}

void GetCodePageTableDOS(unsigned short DOSCode[]){
    DOSCode[0x00] = 0x0000;
    DOSCode[0x01] = 0x263a;
    DOSCode[0x02] = 0x263b;
    DOSCode[0x03] = 0x2665;
    DOSCode[0x04] = 0x2666;
    DOSCode[0x05] = 0x2663;
    DOSCode[0x06] = 0x2660;
    DOSCode[0x07] = 0x2022;
    DOSCode[0x08] = 0x25d8;
    DOSCode[0x09] = 0x25cb;
    DOSCode[0x0a] = 0x0a;
    DOSCode[0x0b] = 0x2642;
    DOSCode[0x0c] = 0x2640;
    DOSCode[0x0d] = 0x266a;
    DOSCode[0x0e] = 0x266b;
    DOSCode[0x0f] = 0x263c;
    
    DOSCode[0x10] = 0x25ba;
    DOSCode[0x11] = 0x25c4;
    DOSCode[0x12] = 0x2195;
    DOSCode[0x13] = 0x203c;
    DOSCode[0x14] = 0x00b6;
    DOSCode[0x15] = 0x00a7;
    DOSCode[0x16] = 0x25ac;
    DOSCode[0x17] = 0x21a8;
    DOSCode[0x18] = 0x2191;
    DOSCode[0x19] = 0x2193;
    DOSCode[0x1a] = 0x2192;
    DOSCode[0x1b] = 0x2190;
    DOSCode[0x1c] = 0x221f;
    DOSCode[0x1d] = 0x2194;
    DOSCode[0x1e] = 0x25b2;
    DOSCode[0x1f] = 0x25bc;
    
    for (int i = 0x20; i <= 0x7e; i++)
    {
        DOSCode[i] = i;
    }
    
    DOSCode[0x7f] = 0x2302;

    for (int i = 0x80; i <= 0xaf; i++)
    {
        DOSCode[i] = 0x0410 + (i - 0x80); 
    }

    DOSCode[0xb0] = 0x2591;
    DOSCode[0xb1] = 0x2592;
    DOSCode[0xb2] = 0x2593;
    DOSCode[0xb3] = 0x2502;
    DOSCode[0xb4] = 0x2524;
    DOSCode[0xb5] = 0x2561;
    DOSCode[0xb6] = 0x2562;
    DOSCode[0xb7] = 0x2556;
    DOSCode[0xb8] = 0x2555;
    DOSCode[0xb9] = 0x2563;
    DOSCode[0xba] = 0x2551;
    DOSCode[0xbb] = 0x2557;
    DOSCode[0xbc] = 0x255d;
    DOSCode[0xbd] = 0x255c;
    DOSCode[0xbe] = 0x255b;
    DOSCode[0xbf] = 0x2510;
    
    DOSCode[0xc0] = 0x2514;
    DOSCode[0xc1] = 0x2534;
    DOSCode[0xc2] = 0x252c;
    DOSCode[0xc3] = 0x251c;
    DOSCode[0xc4] = 0x2500;
    DOSCode[0xc5] = 0x253c;
    DOSCode[0xc6] = 0x255e;
    DOSCode[0xc7] = 0x255f;
    DOSCode[0xc8] = 0x255a;
    DOSCode[0xc9] = 0x2554;
    DOSCode[0xca] = 0x2569;
    DOSCode[0xcb] = 0x2566;
    DOSCode[0xcc] = 0x2560;
    DOSCode[0xcd] = 0x2550;
    DOSCode[0xce] = 0x256c;
    DOSCode[0xcf] = 0x2567;
    
    DOSCode[0xd0] = 0x2568;
    DOSCode[0xd1] = 0x2564;
    DOSCode[0xd2] = 0x2565;
    DOSCode[0xd3] = 0x2559;
    DOSCode[0xd4] = 0x2558;
    DOSCode[0xd5] = 0x2552;
    DOSCode[0xd6] = 0x2553;
    DOSCode[0xd7] = 0x256b;
    DOSCode[0xd8] = 0x256a;
    DOSCode[0xd9] = 0x2518;
    DOSCode[0xda] = 0x250c;
    DOSCode[0xdb] = 0x2588;
    DOSCode[0xdc] = 0x2584;
    DOSCode[0xdd] = 0x258c;
    DOSCode[0xde] = 0x2590;
    DOSCode[0xdf] = 0x2580;
    
    for (int i = 0xe0; i <= 0xef; i++)
    {
        DOSCode[i] = 0x0440 + (i - 0xe0);
    }

    DOSCode[0xf0] = 0x0401;
    DOSCode[0xf1] = 0x0451;
    DOSCode[0xf2] = 0x0404;
    DOSCode[0xf3] = 0x0454;
    DOSCode[0xf4] = 0x0407;
    DOSCode[0xf5] = 0x0457;
    DOSCode[0xf6] = 0x040e;
    DOSCode[0xf7] = 0x045e;
    DOSCode[0xf8] = 0x00b0;
    DOSCode[0xf9] = 0x2219;
    DOSCode[0xfa] = 0x00b7;
    DOSCode[0xfb] = 0x221a;
    DOSCode[0xfc] = 0x2116;
    DOSCode[0xfd] = 0x00a4;
    DOSCode[0xfe] = 0x25a0;
    DOSCode[0xff] = 0x25d9;          
    
    

}

void PrintUTF16(FILE *input , FILE *output){
    UTF8Struct st;
    int c = 0;
    int counter = 0;
    int byte_count = 0;

    while ((c = fgetc(input)) != EOF)
    {

        if (byte_count == 0)
        {
            st.right = c;
            ++byte_count;
        }
        else if(byte_count == 1){
            st.left = c;
            if (st.left == 0)
            {
                fprintf(output," %02x ",st.right);
            }
            else{
                UTF8Struct tmp = unicode_to_UTF_for_UTF16(st);
                fprintf(output," %02x %02x ",tmp.left , tmp.right);
            }
            byte_count = 0;
            ++counter;
            
        }
        
        if (counter == 8){
            counter = 0;
            fprintf(output,"\n");
        } 

        
    }

}

void PrintUTF32(FILE *input , FILE *output){

    UTF32Struct st;
    int c = 0;
    int counter = 0;
    int byte_count = 0;

    while ((c = fgetc(input)) != EOF)
    {       
        if (byte_count == 0)
        {
            st.fourth = c;
            ++byte_count;
        }
        else if(byte_count == 1){
            st.third = c;
            ++byte_count;
        }
        else if(byte_count == 2){
            st.second = c;
            ++byte_count;
        }
        else if(byte_count == 3){
            st.first = c;

            //printf("4 byte: %hhx %hhx %hhx %hhx\n",st.first , st.second , st.third , st.fourth);
            if (st.fourth == 0xff)
            {
                goto exit;
            }
            
            if (st.third == 0)
            {
                fprintf(output,"%02x ",st.fourth);
                ++counter;
                
            }
            else{
                UTF8Struct tmp = unicode_to_UTF_for_UTF32(st);
                fprintf(output,"%02x %02x ",tmp.left , tmp.right);
                counter += 2;
            }
        exit:
            byte_count = 0;
        }
        
        if (counter >= 8){
            counter = 0;
            fprintf(output,"\n");
        } 

        
    }


}

void PrintOneByteCode(unsigned short EmptyTable[],FILE *input , FILE *output){
    int c;
    int counter = 0;
    while ((c = fgetc(input)) != EOF)
    {
        if(c < 0x80){
            fprintf(output, "%02x ",EmptyTable[c]);
            ++counter;
        }
        else {
            UTF8Struct tmp = unicode_to_UTF(EmptyTable + c);
            fprintf(output,"%02x %02x ",tmp.left , tmp.right);
            ++counter;
        }
        if (counter == 8){
            counter = 0;
            fprintf(output,"\n");
        } 

        
    }
    


}

void PrintTextInHexFormatUTF8Coding(CodePage *coding , FILE *input , FILE *output){

    unsigned short EmptyTable[256];
    switch (*coding)
    {
    case MACCIR:
        GetCodePageTableMac(EmptyTable);
        PrintOneByteCode(EmptyTable , input , output);
        break;
    case KOI:
        GetCodePageTableKoi8r(EmptyTable);
        PrintOneByteCode(EmptyTable , input , output);
        break;
    case ISO:
        GetCodePageTableISO(EmptyTable);
        PrintOneByteCode(EmptyTable , input , output);
        break;
    case WIN1251:
        GetCodePageTableWindows(EmptyTable);
        PrintOneByteCode(EmptyTable , input , output);
        break;
    case DOS:
        GetCodePageTableDOS(EmptyTable);
        PrintOneByteCode(EmptyTable , input , output);
        break;
    case UTF16:
        PrintUTF16(input ,output);
        break;
    case UTF32:
        PrintUTF32(input,output);
        break;
    case UTF8:
    default:
        PrintHexFormat(input , output , 16);
        break;
    }

}
