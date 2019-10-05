
#ifndef HAMLET_HAMLET_H
#define HAMLET_HAMLET_H


struct string;
struct input;

void close_file(FILE* file);

void swap(struct string* a, struct string* b);

int is_letter(const char c);

int str_cmp1(struct string* s1, struct string* s2);

int str_cmp2(struct string* s1, struct string* s2);

void delete_spaces(FILE* file1, FILE* file2);


void copy_file(char* place, FILE* file);

void print_array(const char* arr, const int size);

struct input acquire_input(char** argv);

void print_array_infile(const FILE* file, const struct string* p);

void quick_sort(struct string* p, int left, int right, int (*comp)(struct string* s1, struct string* s2));

int count_file(const FILE* file);


void get_str(char* buffer, struct string* place);

int count_str(char* arr, const int size);

FILE* open_file (const char* name, const char* type);

char* create_buffer(FILE* file);

#endif //HAMLET_HAMLET_H
