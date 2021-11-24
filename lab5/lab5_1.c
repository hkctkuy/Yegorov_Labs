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

void add_word_to_list(struct list **List, char *word, int *count)
{
	if (!*List)
	{
		*List = (struct list*)malloc(sizeof(struct list));
		(*List)->element = (char*)malloc(sizeof(char)*(strlen(word) + 1));
		strcpy((*List)->element, word);
		(*count)++;
		(*List)->next = NULL;
	} else
	{
		add_word_to_list(&((*List)->next), word, count);
	}
	return;
}

void print_list(struct list *List)
{
	if(List)
	{
		printf("	%s\n", List->element);
		print_list(List->next);
	}
	return;
}

void delete_list(struct list *List)
{
	if(List)
	{
		delete_list(List->next);
		free(List->element);
		free(List);
	}
	return;
}

char *build_string(char *word, int length)
{
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

void add_and_free(struct list **List, char **word, int *count)
{
	if (strlen(*word) > 0)
	{
		add_word_to_list(List, *word, count);
		free(*word);
		*word = (char*)malloc(sizeof(char));
		*word[0] = '\0';
	}
	return;
}

int symbol(int c)
{
	if((c=='&')||(c=='>')||(c=='<')||(c=='|')||(c==','))
	{
		return 1;
	} else
	{
		return 0;
	}
}

int main()
{
	char *word = malloc(sizeof(char));
	word[0] = '\0';
	int length, charNow, count;
	struct list *List=NULL;
	while ((charNow = getchar()) != EOF)
	{
		List = NULL;
		count = 0;
		while ((charNow != EOF) && (charNow != '\n'))
		{
			while (isspace(charNow))
			{
				if(charNow == '\n')
				{
					add_and_free(&List, &word, &count);
				}
				charNow = getchar();
			}
			if (charNow == '"')
			{
				charNow = getchar();
				while ((charNow != EOF) && (charNow != '\n') && (charNow != '"'))
				{
					length = strlen(word);
					word = build_string(word, length);
					word[length] = charNow;
					word[length+1] = '\0';
					charNow = getchar();
				}
				if (charNow == '"')
				{
					charNow = getchar();
					if (isspace(charNow) || (charNow == EOF) || (charNow == '\n'))
					{
						add_and_free(&List, &word, &count);
					}
				} else
				{
					add_and_free(&List, &word, &count);
				}
			} else
			{
				while ((charNow != '"') && (charNow != EOF) && (charNow != '\n') && (!isspace(charNow)) && (charNow != '&') && (!symbol(charNow)))
				{
					length = strlen(word);
					word = build_string(word, length);
					word[length] = charNow;
					word[length+1] = '\0';
					charNow = getchar();
				}
				if (charNow != '"')
				{
					add_and_free(&List, &word, &count);
				}
				if (symbol(charNow))
				{
					length = strlen(word);
					word = build_string(word, length);
					word[length] = charNow;
					word[length+1] = '\0';
					if (charNow == '&')
					{
						charNow = getchar();
						if (charNow == '&')
						{
							length = strlen(word);
							word = build_string(word, length);
							word[length] = charNow;
							word[length+1] = '\0';
						} else
						{
							ungetc(charNow, stdin);
						}
					}
					if (charNow == '>')
					{
						charNow = getchar();
						if (charNow == '>')
						{
							length = strlen(word);
							word = build_string(word, length);
							word[length] = charNow;
							word[length+1] = '\0';
						} else
						{
							ungetc(charNow, stdin);
						}
					}
					if (charNow == '|')
					{
						charNow = getchar();
						if (charNow == '|')
						{
							length = strlen(word);
							word = build_string(word, length);
							word[length] = charNow;
							word[length+1] = '\0';
						} else
						{
							ungetc(charNow, stdin);
						}
					}
					add_and_free(&List, &word, &count);
					charNow = getchar();
				}
			}
		}
		print_list(List);
		delete_list(List);
	}
	return 0;
}
