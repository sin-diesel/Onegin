
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include "hamlet.h"


struct string {
    char* str;
    int length;
};

struct input {
    char* name_in;
    char* type_in;
    char* name_out;
    char* type_out;
};

struct input acquire_input(char** argv) {
    struct input data = {};
        ++argv;
        data.name_in = *argv;
        ++argv;
        data.type_in= *argv;
        ++argv;
        data.name_out= *argv;
        ++argv;
        data.type_out = *argv;
        return data;
}


void close_file(FILE* file) {
    if (fclose(file)) {
        printf("File1 cannot be closed, error\n");
    }
    return;
}

void swap(struct string* a, struct string* b) {
    struct string temp = *a;
    *a = *b;
    *b = temp;
    return;
}

int is_letter(const char c) {
    if ((c <= 'Z' && c >= 'A') || (c <= 'z' && c >= 'a')) {
        return 1;
    } else {
        return 0;
    }
}

int str_cmp1(struct string* s1, struct string* s2) {

    int count1 = s1->length;
    int count2 = s2->length;

    while (count1 >= 0 && count2 >= 0) {
        if (is_letter(s1->str[count1]) && is_letter(s2->str[count2])) {
            if (s1->str[count1] > s2->str[count2]) {
                return 1;
            }
            if (s1->str[count1] < s2->str[count2]) {
                return -1;
            }
            --(count1);
            --(count2);
        } else {
            while (!is_letter(s1->str[count1])) {
                --(count1);
            }
            while (!is_letter(s2->str[count2])) {
                --(count2);
            }
        }
    }
    if (count1 == -1 && count2 == -1) {
        return 0;
    }
    if (count1 == -1) {
        return -1;
    }
    if (count2 == -1) {
        return 1;
    }


    return 0;
}

int str_cmp2(struct string* s1, struct string* s2) {

    int count1 = s1->length;
    int count2 = s2->length;
    int i = 0;
    int j = 0;

    while (i < count1 && j < count2) {
            if (s1->str[i] > s2->str[j]) {
                return 1;
            }
            if (s1->str[i] < s2->str[j]) {
                return -1;
            }
            ++i;
            ++j;
    }


    return 0;
}



void delete_spaces(FILE* file1, FILE* file2) {
    char c;
    while ((c = fgetc(file1)) != EOF) {
        while (c == ' ') {
            c = fgetc(file1);
        }
        fputc(c, file2);
        while ((c = fgetc(file1)) == ' ') {
            c = fgetc(file1);
        }
        fputc(c, file2);
        while ((c = fgetc(file1)) != '\n' && c != EOF) {
            fputc(c, file2);
        }
        fputc('\n', file2);
    }
    rewind(file1);
    rewind(file2);
    return;
}


void copy_file(char* place, FILE* file) {
    int size = 0;
    fseek(file, 0, SEEK_END);
    size = ftell(file);
    rewind(file);
    fread(place, sizeof(char), size, file);
    return;
}

void print_array(const char* arr, const int size) {
    for (int i = 0; i < size; ++i) {
        printf("%d: %d '%c'\n", i, arr[i], arr[i]);
    }
    return;
}

void print_array_infile(const FILE* file, const struct string* p) {
    while(p->str != NULL) {
        fprintf(file, "%s\n", p->str);
        ++p;
    }
    return;
}

void quick_sort(struct string* p, int left, int right,  int (*comp)(struct string* s1, struct string* s2)) {
    struct string pivot = p[(left + right) / 2];

    int i = left;
    int j = right;
    while (i <= j) {
        while (comp(&p[i], &pivot) < 0) {
            ++i;
        }
        while (comp(&p[j], &pivot) > 0) {
            --j;
        }
        if (i <= j) {
            swap(&p[i], &p[j]);
            ++i;
            --j;
        }
    }
    if (left < j) {
        quick_sort(p, left, j, comp);
    }
    if (i < right) {
        quick_sort(p, i, right, comp);
    }
}

int count_file(const FILE* file) {
    int count = 0;
    fseek(file, 0, SEEK_END);
    count = ftell(file);
    rewind(file);
    return count;
}


void get_str(char* buffer, struct string* place) {
    place->str = buffer;
    char* old = buffer;
    char* neww = strchr(buffer, '\n');
    while (place != NULL && neww != NULL) {
        *(neww) = '\0';
        ++neww;
        place->length = neww - old - 1;
        old = neww;
        neww = strchr(neww, '\n');
        ++place;
        place->str = old;
    }
}

int count_str (char* buffer, const int size) {
    int count = 1;
    char* p = strchr(buffer, '\n');
    while (p - buffer < size && p != NULL) {
        p = strchr(p + 1, '\n');
        ++count;
    }
    return count;
}

FILE* open_file (const char* name, const char* type) {
    FILE* file;
    file = fopen(name, type);
    if (file == NULL) {
        printf("%s cannot be opened", name);
    }
    return file;
}

char* create_buffer(FILE* file) {
    /* How to open file using FILE* file ? */
    int size = count_file(file);
    char* buffer = (char*) calloc(size, sizeof(char));
    copy_file(buffer, file);
    /* How to close file using FILE* file ? */
    return buffer;
}
