#include <stdio.h>
#include <stdlib.h>
// Made by hkctkuy (Ilya Yegorov)

struct list {

    char *string;

    struct list *next;
};

char * get_string() {  // Get dynamic string

    char *string; char character; int size = 0;

    string = malloc(sizeof(char));

    while ((character = getchar()) != '\n') {  // End of line check

        string[size++] = character;

        string = realloc(string, (size + 1) * sizeof(char));
    }

    string[size] = '\0';

    return string;
}

int lexicographic(char *string1, char *string2) {  // Comparison of string by lexicographic order

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

struct list * find_place(struct list *list_pointer, char *string) {  // Finding place for string to maintain lexicographic order

    struct list *place; int order;

    if (list_pointer == NULL) {

        place = list_pointer;
    }
    else {

        order = lexicographic(list_pointer->string, string);

        if(order) {

            place = find_place(list_pointer->next, string);
        }
        else {

            place = list_pointer;
        }
    }
    return place;
}

struct list * get_list() {  // Creat list with num nodes and return point

    struct list *list_pointer = NULL, *place, *new_node_poiter, *end_node_poiter;

    int num, i; char *new_string;

    printf("%s", "Input number of string: ");

    scanf("%d", &num); getchar();

    if(num != 0) {  // For first node

        new_string = get_string();

        list_pointer = malloc(sizeof(struct list));

        list_pointer->next = NULL;

        list_pointer->string = new_string;

        end_node_poiter = list_pointer;
    }
    for (i = 1; i < num; i++) {  // Add new node

        new_string = get_string();

        place = find_place(list_pointer, new_string);

        new_node_poiter = malloc(sizeof(struct list));

        if(place == NULL) {  // If add to the end

            new_node_poiter->next = NULL;

            new_node_poiter->string = new_string;

            end_node_poiter->next = new_node_poiter;

            end_node_poiter = new_node_poiter;
        }
        else {
            new_node_poiter->next = place->next;

            if (place->next == NULL) {  // Shifting the end if "place" node is last

                end_node_poiter = new_node_poiter;
            }
            new_node_poiter->string = place->string;

            place->next = new_node_poiter;

            place->string = new_string;
        }
    }
    return list_pointer;
}

void print_list(struct list * list_pointer) {  // Print list

    if (list_pointer != NULL) {

        printf("%s\n", list_pointer->string);

        print_list(list_pointer->next);
    }
    return;
}

void free_list(struct list * list_pointer) {

    if (list_pointer != NULL) {

        free_list(list_pointer->next);

        free(list_pointer->string);
    }
    free(list_pointer);

    return;
}

int main() {

    struct list *list_pointer; int repeat;

    do {

        list_pointer = get_list();

        printf("\n");

        print_list(list_pointer);

        free_list(list_pointer);

        printf("%s\n", "Do you want to repeat? (Yes - 1, No - 0) ");

        scanf("%d", &repeat);

        printf("\n");
    }
    while (repeat == 1);

    return 0;
}
