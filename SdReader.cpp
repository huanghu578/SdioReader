#include "SdReader.h"
#include "mbed.h"
#include "SDBlockDevice.h"
#include "FATFileSystem.h"
//for WeActStudio.STM32F446RE_CoreBoard
#define MOSI PD_2
#define MISO PC_8
#define SCK  PC_12
#define CS   PC_11
SDBlockDevice bd(MOSI, MISO, SCK, CS);
FATFileSystem fs("fs");
/* 
对Micro SD卡，金手指管脚定义：
SDIO模式         SPI模式
1 --- DAT2       RSV
2 --- CD/DAT3    SPI_CS
3 --- CMD        SPI_MOSI
4 --- VDD        VDD
5 --- CLK        SPI_CLK
6 --- VSS        VSS
7 --- DAT0       SPI_MISO
8 --- DAT1       RSV 
*/
int read_file(const char* file_name,flex_array_t& value) {    
    if (0 != bd.init()) {
        printf("init err. \n");
        return -1;
    }
    if (0 != bd.frequency(5000000)) {
        printf("setting frequency err. \n");
        return -1;
    }        
    if (0!=fs.mount(&bd)) {        
        printf("mounting filesystem err. \n");
        return -1;
    }
    FILE *file;
    long length;
    char *content;
    file = fopen(file_name, "r");
    if (file == NULL) {
        printf("opening file err.\n");
        return -1;
    }
    fseek(file, 0, SEEK_END);
    value.length = ftell(file);
    fseek(file, 0, SEEK_SET);    
    value.content = (char *)malloc(value.length * sizeof(char) + 1);    
    fread(value.content, 1, value.length, file);    
    value.content[value.length] = '\0';
    printf("File contents: %s\n", value.content);    
    fclose(file);
    fs.unmount();
    return 0;
}