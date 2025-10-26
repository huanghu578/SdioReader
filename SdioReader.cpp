#include "SdioReader.h"
#include "mbed.h"
#include "SDIOBlockDevice.h"
#include "FATFileSystem.h"
SDIOBlockDevice sd;
FATFileSystem fs("sd");
int read_file(const char* file_name,std::vector<char>& content,int& length){    
    if (0 != sd.init()) {
        printf("init err. \n");
        return -1;
    }
    if (0!=fs.mount(&sd)) {
        printf("mounting filesystem err. \n");
        return -2;
    }
    FILE *file;    
    file = fopen(file_name, "r");
    if (file == NULL) {
        printf("opening file err.\n");
        return -3;
    }
    fseek(file, 0, SEEK_END);
    length = ftell(file);
    rewind(file); // 移动回文件开头
    content.resize(length);
    size_t itemsRead =fread(content.data(), 1, length, file);
    if (itemsRead != static_cast<size_t>(length)) {
        printf("fread file err.\n");
        return -4;
    }
    content[length] = '\0';
    fclose(file);
    fs.unmount();
    sd.deinit();    
    return 0;
}
