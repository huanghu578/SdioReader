#include "SD.h"
SDBlockDevice bd(MOSI, MISO, SCK, CS);
FATFileSystem fs("fs");


int read_file(const char* file_name,flex_array_t* value) {    
    if (0 != bd.init()) {
        printf("Init failed \n");
        return -1;
    }
    if (0 != bd.frequency(5000000)) {
        printf("Error setting frequency \n");
        return -1;
    }        
    if (0!=fs.mount(&bd)) {        
        fs.reformat(&bd);
        return -1;
    }

    FILE *file;
    long length;
    char *content;
    file = fopen(file_name, "r"); // 打开文件
    if (file == NULL) {
        printf("Error opening file");
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
    flex_array_t* n=(flex_array_t*)malloc(sizeof(flex_array_t) + length * sizeof(char));
    n->length=length;
    memcpy(n->content, content, length);
    value=n;    
    free(content);
    return 0;
}
