#include "mbed.h"
#include "SD.h"
int main() {
    flex_array_t* n;    
    if (read_file("example.txt",n)) {
        printf("Failed to read file\n");
        return -1;
    }
    printf("File contents:\n%s\n", n->content);
    while (1)
    {
        /* code */
    }
    
    return 0;
}
