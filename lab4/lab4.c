#include <stdio.h>
#include <string.h>
// Made by hkctkuy (Ilya Yegorov)

void find_most_common_string(char *most_common_string, int max_length, FILE *file_pointer) {  // Finding the most common string int file

    int max_number = 0, current_number, current_offset, most_common_string_current;
    char current_string[max_length], actual_string[max_length];

    fseek(file_pointer, 0, SEEK_SET);

    while (fgets(current_string, max_length, file_pointer) != NULL) {

        current_offset = ftell(file_pointer);

        current_number = 0;

        while (fgets(actual_string, max_length, file_pointer) != NULL) {

            if (strcmp(current_string, actual_string) == 0) {

                current_number++;
            }
        }
        if (current_number > max_number) {

            max_number = current_number;

            most_common_string_current = current_offset;
        }
        fseek(file_pointer, current_offset, SEEK_SET);
    }
    fseek(file_pointer, most_common_string_current, SEEK_SET);

    fgets(most_common_string, max_length, file_pointer);

    printf("%s\n", most_common_string);

    return;
}


void length_sort_file(FILE *file_pointer, int max_length) {  // Sorting string of file by string length increase

    long max_length_offset, current_offset, start_sorted_part_offset;
    int current_max_length = 0, current_length;
    char current_string[max_length], longest_string[max_length];

    fseek(file_pointer, 0, SEEK_END);

    start_sorted_part_offset = ftell(file_pointer);

    while (start_sorted_part_offset != 0) {

        fseek(file_pointer, 0, SEEK_SET);

        current_offset = 0;

        max_length_offset = 0;

        current_max_length = 0;

        while (current_offset != start_sorted_part_offset) {  // Finding string with max lenght

            fgets(current_string, max_length, file_pointer);

            current_length = strlen(current_string);

            if (current_max_length <= current_length) {

                current_max_length = current_length;

                max_length_offset = current_offset;
            }
            current_offset = ftell(file_pointer);
        }

        fseek(file_pointer, max_length_offset, SEEK_SET);

        fgets(longest_string, max_length, file_pointer);

        long put_offset = max_length_offset, get_offset = ftell(file_pointer);

        while(get_offset != start_sorted_part_offset) {  // Shifthig strings after the longest

            fgets(current_string, max_length, file_pointer);

            get_offset = ftell(file_pointer);

            fseek(file_pointer, put_offset, SEEK_SET);

            fputs(current_string, file_pointer);

            put_offset = ftell(file_pointer);

            fseek(file_pointer, get_offset, SEEK_SET);
        }
        start_sorted_part_offset = put_offset;  // Move longest string to the end

        fseek(file_pointer, put_offset, SEEK_SET);

        fputs(longest_string, file_pointer);
    }
    return;
}

int main() {

    char file_name[80];

    printf("%s\n", "Input name of file");

    scanf("%s", file_name);

    FILE *file_pointer = fopen(file_name, "r+");

    if (file_pointer != NULL) {

        int max_length = 80;

        printf("%s\n", "Input max length of file string");

        scanf("%d", &max_length);

        char most_common_string[max_length];

        find_most_common_string(most_common_string, max_length, file_pointer);

        printf("%s\n", most_common_string);

        length_sort_file(file_pointer, max_length);

        fclose(file_pointer);
    }
    else {

        printf("%s\n", "Error: No such file exists!");
    }

    return 0;
}
