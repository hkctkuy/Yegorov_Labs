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

struct list
{
	char *element;
	struct list *next;
};

typedef char* array;

int dont_add(char *str)
{
	if (strcmp(str, "&") == 0)
	{
		return 1;
	} else
	{
		return 0;
	}
}

void add_word_to_list(struct list **List, char *word, int *count)
{
	if (!*List)
	{
		*List = (struct list*)malloc(sizeof(struct list));
		(*List)->element = (char*)malloc(sizeof(char)*(strlen(word) + 1));
		strcpy((*List)->element, word);
		if(!dont_add(word))
		{
			(*count)++;
		}
		(*List)->next = NULL;
	} else
	{
		add_word_to_list(&((*List)->next), word, count);
	}
}

void print_list(struct list *List)
{
	if(List)
	{
		printf("	%s\n", List->element);
		print_list(List->next);
	}
}

void delete_list(struct list *List)
{
	if(List)
	{
		delete_list(List->next);
		free(List->element);
		free(List);
	}
}

char *build_string(char *word, int length){
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

void add_and_free(struct list **List, char **word, int *count){
	if (strlen(*word) > 0)
	{
		add_word_to_list(List, *word, count);
		free(*word);
		*word = (char*)malloc(sizeof(char));
		*word[0] = '\0';
	}
}

int symbol(int c){
	if((c=='&')||(c=='>')||(c=='<')||(c=='|')||(c==',')){
		return 1;
	} else {
		return 0;
	}
}

void cd(struct list *List, int count)
{
	int d;
	if(count>2){
		printf("Wrong number of parameters of command cd! Please, try again\n");
	} else {
		if(List->next){
			if(!strcmp((List->next)->element, "~")){
				chdir("/home");
			} else {
				if((d=chdir((List->next)->element))==(-1)){
					printf("Error in command cd!");
				}
			}
		} else {
			chdir("/home");
		}
	}
}

array *make_array(struct list *List, int size){
	int counter = 0;
	array *new_array;
	struct list *help = List;
	new_array = (array*)malloc(sizeof(array) * (size + 1));
	while (help)
	{
		if (!dont_add(help->element)){
			new_array[counter] = help->element;
			counter++;
		}
		help = help->next;
	}
	new_array[counter] = NULL;
	return new_array;
}

int is_background_mode(struct list *List)
{
	if (List)
	{
		if (!List->next)
		{
			if (!strcmp(List->element, "&"))
			{
				return 1;
			} else
			{
				return 0;
			}
		} else if (!strcmp(List->element, "&"))
		{
			return 2;
		} else
		{
			return is_background_mode(List->next);
		}
	} else
	{
		return 2;
	}
}

int is_conveyor(struct list *List){
	if (List)
	{
		if (!strcmp(List->element, "|"))
		{
			return 1;
		} else
		{
			return is_conveyor(List->next);
		}
	} else
	{
		return 0;
	}
}

int how_much_elements(struct list *List)
{
	int counter = 0;
	while (List)
	{
		if (!strcmp(List->element, "|"))
		{
			counter++;
		}
		List = List->next;
	}
	return counter + 1;
}

array *make_array_one_proc(struct list **List, char **file_name, int *error)
{
	array *new_array;
	struct list *help = *List;
	int size = 0, counter = 0, flag = 0;
	while ((help) && (strcmp(help->element, "|") != 0))
	{
		if (strcmp(help->element, ">>") != 0)
		{
			size++;
		}
		help = help->next;
	}
	new_array = (array*)malloc(sizeof(array) * (size + 1));
	while ((*List) && (strcmp((*List)->element, "|") != 0))
	{
		if (!strcmp((*List)->element, ">>"))
		{
			flag = 1;
			(*List) = (*List)->next;
			*file_name = (*List)->element;
			(*List) = (*List)->next;
		} else if (!strcmp((*List)->element, "&"))
		{
			flag = -1;
			(*List) = (*List)->next;
		} else
		{
			new_array[counter] = (*List)->element;
			counter++;
			(*List) = (*List)->next;
		}
	}
	if (*List)
	{
		(*List) = (*List)->next;
		if (flag == 1)
		{
			*error = 1;
		} else if (flag == (-1))
		{
			*error = 2;
		}
	}
	new_array[counter] = NULL;
	return new_array;
}

array **make_array_for_conveyor(struct list **List, int *size, char **file_name, int *error)
{
	array **new_array = (array**)malloc(sizeof(array) * how_much_elements(*List));
	int counter = 0;
	while (*List)
	{
		new_array[counter] = make_array_one_proc(List, file_name, error);
		counter++;
	}
	*size = counter;
	return new_array;
}

void execute_conveyor(int process_amount, char **argv[], int flag, char *file_name)
{
	int counter, fd[process_amount - 1][2], file_descriptor = 0;
	pipe(fd[0]);
	if (fork() == 0){
		close(fd[0][0]);
		dup2(fd[0][1], 1);
		close(fd[0][1]);
		printf("[%s]", *argv[0]);
		execvp(*argv[0], argv[0]);
		_exit(0);
	}
	wait(NULL);
	close(fd[0][1]);
	for (counter = 1; counter <= (process_amount - 2); counter++)
	{
		pipe(fd[counter]);
		if (fork() == 0)
		{
			dup2(fd[counter][1], 1);
			close(fd[counter][1]);
			dup2(fd[counter - 1][0], 0);
			close(fd[counter - 1][0]);
			execvp(*argv[counter], argv[counter]);
			_exit(0);
		}
		wait(NULL);
		close(fd[counter][1]);
		close(fd[counter - 1][0]);
	}
	if (flag)
	{
		file_descriptor = open(file_name, O_WRONLY|O_APPEND|O_CREAT, 0666);
		if (fork() == 0)
		{
			close(fd[process_amount - 2][1]);
			dup2(fd[process_amount - 2][0], 0);
			close(fd[process_amount - 2][0]);
			dup2(file_descriptor, 1);
			close(file_descriptor);
			execvp(*argv[process_amount - 1], argv[process_amount - 1]);
			_exit(0);
		}
		wait(NULL);
		close(file_descriptor);
	} else
	{
		if (fork() == 0)
		{
			close(fd[process_amount - 2][1]);
			dup2(fd[process_amount - 2][0], 0);
			close(fd[process_amount - 2][0]);
			execvp(*argv[process_amount - 1], argv[process_amount - 1]);
			_exit(0);
		}
	}
	close(fd[process_amount - 2][0]);
}

int is_add_to_end(struct list *List)
{
	while (List)
	{
		if (!strcmp(List->element, ">>"))
		{
			return 1;
		} else
		{
			return is_add_to_end(List->next);
		}
	}
	return 0;
}

array **make_array_for_end(struct list **List, int *size, char **file_name, int *error)
{
	array **new_array = (array**)malloc(sizeof(array) * how_much_elements(*List));
	int counter = 0;
	while (*List)
	{
		new_array[counter] = make_array_one_proc(List, file_name, error);
		counter++;
	}
	*size = counter;
	return new_array;
}

void add_to_end(int process_amount, char **argv[], char *file_name, int flag_conveyor, int flag_end)
{
	int file_descriptor;
	if (flag_conveyor)
	{
		execute_conveyor(process_amount, argv, flag_end, file_name);
	} else
	{
		file_descriptor = open(file_name, O_WRONLY|O_CREAT|O_APPEND, 0666);
		if (fork() == 0)
		{
			dup2(file_descriptor, 1);
			execvp(*argv[0], argv[0]);
			_exit(0);
		}
		wait(NULL);
		close(file_descriptor);
	}
}

int main(){
	char *word = malloc(sizeof(char)), buf[256], *file_name;
	word[0] = '\0';
	int length, char_now, count, flag, status, size, is_conv = 0, is_end = 0, error = 0;
	pid_t pid, pid1;
	struct list *List = NULL, *help;
	array *array_of_words, **conveyor;
	printf("[%s] ", getcwd(buf, 256));
	while (1)
	{
		List = NULL;
		array_of_words = NULL;
		count = 0;
		char_now = getchar();
		while ((char_now != EOF) && (char_now != '\n'))
		{
			while (isspace(char_now))
			{
				if(char_now == '\n')
				{
					add_and_free(&List, &word, &count);
				}
				char_now = getchar();
			}
			if (char_now == '"')
			{
				char_now = getchar();
				while ((char_now != EOF) && (char_now != '\n') && (char_now != '"'))
				{
					length = strlen(word);
					word = build_string(word, length);
					word[length] = char_now;
					word[length+1] = '\0';
					char_now = getchar();
				}
				if (char_now == '"')
				{
					char_now = getchar();
					if (isspace(char_now) || (char_now == EOF) || (char_now == '\n'))
					{
						add_and_free(&List, &word, &count);
					}
				} else
				{
					add_and_free(&List, &word, &count);
				}
			} else
			{
				while ((char_now != '"') && (char_now != EOF) && (char_now != '\n') && (!isspace(char_now)) && (char_now != '&') && (!symbol(char_now)))
				{
					length = strlen(word);
					word = build_string(word, length);
					word[length] = char_now;
					word[length+1] = '\0';
					char_now = getchar();
				}
				if (char_now != '"')
				{
					add_and_free(&List, &word, &count);
				}
				if (symbol(char_now))
				{
					length = strlen(word);
					word = build_string(word, length);
					word[length] = char_now;
					word[length+1] = '\0';
					if (char_now == '&')
					{
						char_now = getchar();
						if (char_now == '&')
						{
							length = strlen(word);
							word = build_string(word, length);
							word[length] = char_now;
							word[length+1] = '\0';
						} else
						{
							ungetc(char_now, stdin);
						}
					}
					if (char_now == '>')
					{
						char_now = getchar();
						if (char_now == '>')
						{
							length = strlen(word);
							word = build_string(word, length);
							word[length] = char_now;
							word[length+1] = '\0';
						} else
						{
							ungetc(char_now, stdin);
						}
					}
					if (char_now == '|')
					{
						char_now = getchar();
						if (char_now == '|')
						{
							length = strlen(word);
							word = build_string(word, length);
							word[length] = char_now;
							word[length+1] = '\0';
						} else
						{
							ungetc(char_now, stdin);
						}
					}
					add_and_free(&List, &word, &count);
					char_now = getchar();
				}
			}
		}
		if (List)
		{
			if (!strcmp(List->element, "cd"))
			{
				cd(List, count);
			} else	if ((is_conv = is_conveyor(List)) && !is_add_to_end(List))
			{
				help = List;
				conveyor = make_array_for_conveyor(&help, &size, &file_name, &error);
				if (error == 0)
				{
					execute_conveyor(size, conveyor, is_end, file_name);
					for (int counter = 0; counter < size; counter++)
					{
						free(conveyor[counter]);
					}
				} else if (error == 2)
				{
					printf("Wrong position of &!\n");
				}
				error = 0;
				free(conveyor);
			} else if ((isEnd = is_add_to_end(List)))
			{
				help = List;
				conveyor = make_array_for_end(&help, &size, &file_name, &error);
				if (error == 0)
				{
					add_to_end(size, conveyor, file_name, is_conv, is_end);
				} else	if (error == 1)
				{
					printf("Wrong position of >>!\n");
				} else
				{
					printf("Wrong position of &!\n");
				}
				error = 0;
				for (int counter = 0; counter < size; counter++)
				{
					free(conveyor[counter]);
				}
				free(conveyor);
			} else
			{
				array_of_words = make_array(List, count);
				if ((flag = is_background_mode(List)) != 1)
				{
					if ((pid1 = fork()) != 0)
					{
						wait(&status);
						if (!status != 0)
						{
							perror(List->element);
						}
					} else
					{
						execvp(List->element, array_of_words);
						perror(List->element);
						exit(2);
					}
					wait(NULL);
					if(flag == 2)
					{
						printf("Wrong position of & !\n");
					}
				} else
				{
					if ((pid = fork()) != 0 )
					{
						wait(&status);
						if (!status != 0)
						{
							perror(List->element);
						}
					} else
					{
						execvp(List->element, array_of_words);
						perror(List->element);
						exit(2);
					}
				}
			}
			free(array_of_words);
		}
		delete_list(List);
		printf("[%s] ", getcwd(buf, 256));
	}
	return 0;
}
