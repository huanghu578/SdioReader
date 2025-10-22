typedef struct {
    int length;
    char content[];
}flex_array_t;

int read_file(const char* file_name,flex_array_t& value);