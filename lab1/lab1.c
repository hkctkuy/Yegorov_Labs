// Input data: unlimited string
// End sign: EOF

#include <stdio.h>
#include <stdlib.h>

void outArray(char **arr);

char * getString() {  // Get dynamic string

    char *string; char character; int size = 0;

    string = malloc(sizeof(char));

    while ((character = getchar()) != '\n' && character != EOF) {

        string[size++] = character;

        string = realloc(string, size);
    }
    if (character == '\n')

        string[size] = '\0';

    else

        string[size] = EOF;

    return string;
}

char **getArray() {  // Get dynamic array of dynamic string

    char **arr; char *string; int size = 0;

    arr = malloc(sizeof(char *));

    while (*(string = getString()) != EOF) {

        arr[size++] = string;

        arr = realloc(arr, size);
    }
    arr[size] = string;

    return arr;
}

void outArray(char **arr) {  //  Array Output

    int i = 0;

    while(*arr[i] != EOF)

        printf("%s\n", arr[i++]);
}

int alf(char *string1, char *string2) {  // Comparison of string by lexicographic order

    int result = 1, i = 0;

    while (string1[i] != '\0') {

        if (string1[i] != string2[i]) {

            if(string1[i] > string2[i])

                result = 0;

            break;
        }
        i++;
    }
    return result;
}

void swap(char **string1, char **string2) {  // Swap string pointers

    char *tmp;

    tmp = *string1; *string1 = *string2; *string2 = tmp;

}

void sort(char **arr) {  // Sort string by lexicographic order

    int size = -1;

    while (*arr[++size] != EOF);

    int i, j;

    for (i = 0; i < size; i++)

        for (j = i + 1; j < size; j++)

            if(!alf(arr[i],arr[j]))

                swap(&arr[i],&arr[j]);
}

int main() {

    char **arr;

    arr = getArray();

    sort(arr);

    outArray(arr);

    return 0;
}
