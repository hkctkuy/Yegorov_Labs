#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <fcntl.h>

struct list {

	char *element;

	struct list *next;
};

typedef char* array;

int dont_add(char *string) {

	if (strcmp(string, "&") == 0) {

		return 1;

	} else {
		return 0;
	}
}

void add_word_to_list(struct list **List, char *word, int *count) {

	if (!*List) {

		*List = (struct list*)malloc(sizeof(struct list));

		(*List)->element = (char*)malloc(sizeof(char)*(strlen(word) + 1));

		strcpy((*List)->element, word);

		if (!dont_add(word)) {

			(*count)++;
		}
		(*List)->next = NULL;

	} else {

		add_word_to_list(&((*List)->next), word, count);
	}
}

void print_list(struct list *List) {

	if (List) {

		printf("	%s\n", List->element);

		print_list(List->next);
	}
}

void delete_list(struct list *List) {

	if (List) {

		delete_list(List->next);

		free(List->element);

		free(List);
	}
}

char *build_string(char *word, int length) {
	char *help;

	if (!length)
	{
		help = (char*)malloc(sizeof(char) * 2);
	} else
	{
		help = (char*)malloc(sizeof(char) * (length + 2));
		strncpy(help, word, length);
		free(word);
	}
	return help;
}

void add_and_free(struct list **List, char **word, int *count) {

	if (strlen(*word) > 0) {

		add_word_to_list(List, *word, count);

		free(*word);

		*word = (char*)malloc(sizeof(char));

		*word[0] = '\0';
	}
}

int symbol(int ch) {

	if((ch=='&')||(ch=='>')||(ch=='<')||(ch=='|')||(ch==',')) {

		return 1;

	} else {

		return 0;
	}
}

void cd(struct list *List, int count) {

	int d;

	if (count > 2) {

		printf("Wrong number of parameters of command cd! Please, try again\n");

	} else {

		if (List->next) {

			if (!strcmp((List->next)->element, "~")) {

				chdir("/home");

			} else {

				if ((d = chdir((List->next)->element)) == (-1)) {

					printf("Error in command cd!");
				}
			}
		} else {

			chdir("/home");
		}
	}
}

array *make_array(struct list *List, int size) {

	int counter = 0;

	array *new_array;

	struct list *help = List;

	new_array = (array*)malloc(sizeof(array) * (size + 1));

	while (help) {

		if (!dont_add(help->element)) {

			new_array[counter] = help->element;

			counter++;
		}
		help = help->next;
	}
	newArray[counter] = NULL;

	return new_array;
}

int main()
{
	char *word = malloc(sizeof(char)), buf[256];

	word[0] = '\0';

	int length, char_now, count, status = 0;

	struct list *List = NULL;

	array *array_of_words;

	printf("[%s] ", getcwd(buf, 256));

	while (1) {

		List = NULL;

		array_of_words = NULL;

		count = 0;

		charNow = getchar();

		while ((charNow != EOF) && (charNow != '\n')) {

			while (isspace(charNow)) {

				if(charNow == '\n') {

					add_and_free(&List, &word, &count);
				}
				charNow = getchar();
			}
			if (charNow == '"') {

				charNow = getchar();

				while ((charNow != EOF) && (charNow != '\n') && (charNow != '"')) {

					length = strlen(word);

					word = buildString(word, length);

					word[length] = char_now;

					word[length+1] = '\0';

					char_now = getchar();
				}
				if (char_now == '"') {

					char_now = getchar();

					if (isspace(charNow) || (charNow == EOF) || (charNow == '\n')) {

						add_and_free(&List, &word, &count);
					}
				} else {

					add_and_free(&List, &word, &count);
				}
			} else {

				while ((char_now != '"') && (char_now != EOF) && (char_now != '\n') && (!isspace(char_now)) && (char_now != '&') && (!symbol(char_now))) {

					length = strlen(word);

					word = build_string(word, length);

					word[length] = char_now;

					word[length + 1] = '\0';

					char_now = getchar();
				}
				if (char_now != '"') {

					add_and_free(&List, &word, &count);
				}
				if (symbol(char_now))	{

					length = strlen(word);

					word = build_string(word, length);

					word[length] = char_now;

					word[length + 1] = '\0';

					if (char_now == '&') {

						char_now = getchar();

						if (char_now == '&') {

							length = strlen(word);

							word = build_string(word, length);

							word[length] = char_now;

							word[length + 1] = '\0';

						} else {

							ungetc(char_now, stdin);
						}
					}
					if (char_now == '>') {

						char_now = getchar();

						if (char_now == '>') {

							length = strlen(word);

							word = build_string(word, length);

							word[length] = char_now;

							word[length + 1] = '\0';

						} else {

							ungetc(char_now, stdin);
						}
					}
					if (char_now == '|') {

						char_now = getchar();

						if (char_now == '|') {

							length = strlen(word);

							word = build_string(word, length);

							word[length] = char_now;

							word[length + 1] = '\0';

						} else {

							ungetc(char_now, stdin);
						}
					}
					add_and_free(&List, &word, &count);

					char_now = getchar();
				}
			}
		}
		if (List) {

			if (!strcmp(List->element, "cd")) {

				cd(List, count);

			} else {

				array_of_words = make_array(List, count);

				if (fork()) {

					wait(&status);

					if (!status != 0) {

						perror(List->element);
					}
				} else {

					execvp(List->element, array_of_words);

					perror(List->element);

					exit(2);
				}
			}
			free(array_of_words);
		}
		delete_list(List);
		
		printf("[%s] ", getcwd(buf, 256));
	}
	return 0;
}
