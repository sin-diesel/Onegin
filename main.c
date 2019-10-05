#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

#include "hamlet.h"

int main (int argc, char** argv) {
    struct input data = acquire_input(argv);

    FILE* file1 =  open_file(data.name_in, data.type_in); /* Opening files */
    FILE* file2 =  open_file(data.name_out, data.type_out);
    char* buffer = create_buffer(file1); /* Work with file, passing FILE* file1 as argument */
    int size = count_file(file1);



    int str_size = count_str(buffer, size); /* Counting strings */

    struct string* strings = (struct string*) calloc(str_size + 1, sizeof(struct string));
    strings[str_size].str = '\0';

    get_str(buffer, strings); /* Obtain strings from buffer and place them in strings struct */


    fprintf(file2, "NOT SORTED -----------------------------------------\n"); /* Printing not sorted array */

    print_array_infile(file2, strings);

    quick_sort(strings, 0, str_size - 1, str_cmp1); /* Sorting from end */

    fprintf(file2, "SORTED FROM THE END-----------------------------------------\n");

    print_array_infile(file2, strings);


    fprintf(file2, "SORTED FROM BEGINNING-----------------------------------------\n");

    quick_sort(strings, 0, str_size - 1, str_cmp2); /* Sorting from beginning */

    print_array_infile(file2, strings);

    free(strings); /* Freeing arrays and closing files */
    free(buffer);

    close_file(file1);
    close_file(file2);

    return 0;
}

//TODO
// 1 int main(int argc, char** argv)  done
// 2 work with files when it's appropriate well not quite
// 3 create buffer done
// 4 look for code repeating done
// 5 headers and linking (ask Artem) waiting for Artem's answer but for now considering it done
// 6 use while instead of for (without str_size) done
