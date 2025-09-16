#include "mbed.h"
#include "SDBlockDevice.h"
#include "FATFileSystem.h"

/* 对Micro SD卡，金手指管脚定义：
SDIO模式         SPI模式
1 --- DAT2       RSV
2 --- CD/DAT3    SPI_CS
3 --- CMD        SPI_MOSI
4 --- VDD        VDD
5 --- CLK        SPI_CLK
6 --- VSS        VSS
7 --- DAT0       SPI_MISO
8 --- DAT1       RSV */

//for WeActStudio.STM32F446RE_CoreBoard
#define MOSI PD_2
#define MISO PC_8
#define SCK  PC_12
#define CS   PC_11

typedef struct{
    int length;
    char content[];
}flex_array_t;

int read_file(const char* file_name,flex_array_t* value);