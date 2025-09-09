#include "mbed.h"
#include "SDBlockDevice.h"
SDBlockDevice bd(PA_7, PA_6, PA_5, PA_4);
#include "FATFileSystem.h"
FATFileSystem fs("fs");
int main() {   
    if (0 != bd.init()) {
        printf("Init failed \n");
        return -1;
    }
    if (0 != bd.frequency(5000000)) {
        printf("Error setting frequency \n");
    }
    int err = fs.mount(&bd);    
    if (err) {        
        err = fs.reformat(&bd);
    }

    FILE *file;
    long length;
    char *content;
 
    file = fopen("example.txt", "r"); // 打开文件
    if (file == NULL) {
        perror("Error opening file");
        return -1;
    }
 
    // 获取文件长度
    fseek(file, 0, SEEK_END);
    length = ftell(file);
    fseek(file, 0, SEEK_SET);
 
    // 分配足够的空间来存储文件内容
    content = (char *)malloc(length * sizeof(char) + 1); 
    // 读取并保存文件内容到字符串
    fread(content, 1, length, file); 
    // 在content字符串末尾添加一个空字符以构成字符串
    content[length] = '\0'; 
    printf("File contents: %s\n", content); 
    // 关闭文件并释放内存
    fclose(file);
    free(content); 
    return 0;
}

