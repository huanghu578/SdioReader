#include "mbed.h"
#include "USBSerial.h"
#include "SdReader.h"
#include <string>
USBSerial u(true,10,1,2);
DigitalOut led(PB_2);
int i;
int main(){
    //std::string content;
    int length;
    std::vector<char> content;
    auto r=read_file("/sd/hh.txt",content,length);
    while (true) {
        i++;
        u.printf("i:%d ,content:%s,length:%d,result:%d\n",i,content.data(),length,r);
        led = !led;
        ThisThread::sleep_for(2s);
    }
}
