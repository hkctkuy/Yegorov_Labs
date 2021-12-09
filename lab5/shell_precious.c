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
#include <signal.h>
// Made by hkctkuy (Ilya Yegorov)

struct list {
    char * elem;
    struct list * next;
    int ss;
};

int follow(struct list ** listp);  // Prototypes

int convsize(struct list * List);

int conv(struct list ** listp);

char * getLine() {  // Get current line

    char *line; char ch; int size = 0;

    line = malloc(sizeof(char));

    while (((ch = getchar()) != '\n') && (ch != EOF)) {

        line[size++] = ch;

        line = realloc(line, (size + 1) * sizeof(char));
    }
    if (ch == EOF || size == 0) {

        free(line);

        return NULL;
    }
    line[size] = '\0';

    return line;
}

int isSpec(char ch) {

    return (ch == '(') || (ch == ')') || (ch == '|') || (ch == '&') || (ch == '>') || (ch == ';');
}

void push(char ** strp, int * len, struct list ** listp, struct list ** lastp, int * ss) { // Push cur word and prepair list to next word

  if(*len) {

        (*strp)[*len] = '\0';

        (*listp)->elem = (*strp);

        (*listp)->ss = (*ss);

        (*lastp) = (*listp);

        (*listp)->next = malloc(sizeof(struct list));

        (*listp) = (*listp)->next;

        (*listp)->next = NULL;

        *strp =  malloc(sizeof(char));

        *len = 0; *ss = 0;
    }
    return;
}

struct list * getlist() {

    struct list * List = NULL; struct list * first = NULL; struct list * last = NULL;

    char buf[256];

    printf("%s: ", getcwd(buf, 256));

    char * line = getLine();

    if (line == NULL) {

        return NULL;
    }
    char * cur = malloc(sizeof(char));

    int len = 0; int ss = 0;

    List = malloc(sizeof(struct list));

    List->next = NULL;

    first = List;

    last = List;

    int i = 0;

    while(line[i] != '\0') {

        char ch = line[i];

        if(ch == ' ') {  //  Skip all spaces

            push(&cur, &len, &List, &last, &ss);

            i++;

            continue;
        }
        if(isSpec(ch)) {

            if ((ch == '|') && (line[i + 1] == '|')) {  // Push cur word and push ||

                push(&cur, &len, &List, &last, &ss);

                cur = realloc(cur, 3 * sizeof(char));

                cur[0] = '|'; cur[1] = '|';

                len = 2; int ss = 1;

                push(&cur, &len, &List, &last, &ss);

                i += 2;
            }
            else if((ch == '&') && (line[i + 1] == '&')) {  // Push cur word and push &&

                push(&cur, &len, &List, &last, &ss);

                cur = realloc(cur, 3 * sizeof(char));

                cur[0] = '&'; cur[1] = '&';

                len = 2; int ss = 1;

                push(&cur, &len, &List, &last, &ss);

                i += 2;
            }
            else if((ch == '>') && (line[i + 1] == '>')) {  // Push cur word and push &&

                push(&cur, &len, &List, &last, &ss);

                cur = realloc(cur, 3 * sizeof(char));

                cur[0] = '>'; cur[1] = '>';

                len = 2; int ss = 1;

                push(&cur, &len, &List, &last, &ss);

                i += 2;
            }
            else {  // Push cur word and push SS

                push(&cur, &len, &List, &last, &ss);

                cur = realloc(cur, 2 * sizeof(char));

                cur[0] = ch;

                len = 1; int ss = 1;

                push(&cur, &len, &List, &last, &ss);

                i++;
            }
        }
        else if(ch == '"') { // Push word with "text"

            push(&cur, &len, &List, &last, &ss);

            ch = line[++i];

            while ((ch != '"') && (line[i + 1] != '\0')) {

                cur[len++] = ch;

                cur = realloc(cur, (len + 1) * sizeof(char));

                ch = line[++i];
            }
            i++;

            push(&cur, &len, &List, &last, &ss);
        }
        else {  // Add litter in cur word

            cur[len++] = ch;

            cur = realloc(cur, (len + 1) * sizeof(char));

            i++;
        }
    }
    if(len) {

        cur[len] = '\0';

        List->elem = cur;

        List->ss = ss;

        List->next = NULL;
    }
    else {

        free(cur); free(List); last->next = NULL;
    }
    free(line);

    return first;
}

void printlist(struct list * List) {

    if(List) {

        printf("%s %d\n", List->elem, List->ss);

        printlist(List->next);
    }
    return;
}

void freelist(struct list * List) {

    if(List) {

        freelist(List->next);

        free(List);

        List = NULL;
    }
    return;
}

int check(struct list * List, int * modep) {  // Checking correct format

    int bracket = 0;

    while (List) {

        if(List->ss) {

            int openBr = !strcmp(List->elem, "("); int closeBr = !strcmp(List->elem, ")");

            if(!strcmp(List->elem, "&")) {

                if(List->next == NULL) {

                    (*modep) = 1;

                    List->elem[0] = ')';
                }
                else {

                    printf("%s\n", "Bad input: &");

                    return 0;
                }
            }
            else if(openBr) {

                bracket++;
            }
            else if(closeBr) {

                bracket--;

                if(bracket < 0) {

                    printf("%s\n", "Bad input: bracket");

                    return 0;
                }
                if((List->next != NULL) && (!List->next->ss)) {

                    printf("%s\n", "Bad input: word after brackets");

                    return 0;
                }
            }
            if((List->next != NULL) && (List->next->ss)) {

                if (!(!strcmp(List->next->elem, "(") || closeBr)) {

                    printf("%s\n", "Bad input: two operators in a row");

                    return 0;
                }
            }
            if((List->next == NULL) && (strcmp(List->elem, "&") && (strcmp(List->elem, ")")))) {

                printf("%s\n", "Bad input: operator in the end");

                return 0;
            }
        }
        else if  ((List->next != NULL) && (!strcmp(List->next->elem, "("))) {

            printf("%s\n", "Bad input: word before brackets");

            return 0;
        }
        List = List->next;
    }
    if (bracket > 0) {

        printf("%s\n", "Bad input: bracket");

        return 0;
    }
    //printf("%s\n", "Good");
    return 1;
}

void skip(struct list ** listp) {  // Skiping process with its arg or expression in brackets

    //printf("%s\n", "skip");

    if ((*listp) && !strcmp((*listp)->elem, "(")) {

        int bracket = 1; (*listp) = (*listp)->next;

        while(bracket) {

            //printf("%s\n", "skipbracket");

            if (!strcmp((*listp)->elem, "(")) bracket++;

            else if (!strcmp((*listp)->elem, ")")) bracket--;

            (*listp) = (*listp)->next;
        }
    }
    else {

          while((*listp) && (!(*listp)->ss)) {

          //printf("%s\n", "skipss");

          (*listp) = (*listp)->next;
        }
    }
    return;
}

void skipconv(struct list ** listp) {

  int size = convsize(*listp), firstElFlag = 1, i;

  for(i = 0; i < size; i++) {

      if(!firstElFlag) {

          (*listp) = (*listp)->next;
      }

      skip(listp);

      firstElFlag = 0;
  }
  if((*listp) && (!strcmp((*listp)->elem, ">") || !strcmp((*listp)->elem, ">>"))) {

      (*listp) = (*listp)->next; skip(listp);
  }
  return;
}

char ** getargv(struct list ** listp) {

    //printf("%s\n", "getargv");

    char ** argv = malloc(sizeof(char*));

    int size = 0;

    while((*listp) && !(*listp)->ss) {

        //rintf("%s %s\n", "getargvwhile", List->elem);

        argv[size++] = (*listp)->elem;

        argv = realloc(argv, (size + 1) * sizeof(char*));

        (*listp) = (*listp)->next;
    }
    argv[size] = NULL;

    //int i; for(i = 0; i <= size; i++) printf("%s\n", argv[i]);

    return argv;
}

int bracket(struct list * List) {  // () processing

    //printf("%s\n", "bracket");

    struct list * first = List; int status = 0;

    while((!status) && (List) && strcmp(List->elem, ")")) {

        //printf("%s\n", "bracketWhile");

        skip(&List);

        if((List) && (!strcmp(List->elem, "||") || !strcmp(List->elem, "&&") || !strcmp(List->elem, ";")
                  || (!strcmp(List->elem, "|") || !strcmp(List->elem, ">") || !strcmp(List->elem, ">>")))) {

            status = follow(&first);
        }
        else {

            if(!strcmp(first->elem, "(")) {

                status = bracket(first->next);

                first = List;  // Crutch
            }
            else {

                char ** argv = getargv(&first);

                if(fork() == 0) {

                    execvp(argv[0], argv);

                    exit(EXIT_FAILURE);
                }
                wait(&status); if(!WIFEXITED(status)) return 1;
            }
        }
        List = first;
    }
    if(List) List = List->next;

    return status;
}

int follow(struct list ** listp) {  // || && ; porcessing

    //printf("%s\n", "follow");

    struct list * first; int status, execflag = 1, firstElFlag = 1;

    while ((*listp) && strcmp((*listp)->elem, ")")) {

        if(!firstElFlag) (*listp) = (*listp)->next;

        else firstElFlag = 0;

        first = (*listp);

        skip(listp);

        if((*listp) && (!strcmp((*listp)->elem, "|") || !strcmp((*listp)->elem, ">") || !strcmp((*listp)->elem, ">>"))) {  // Execute current operand

            if(execflag) status = conv(&first);

            else skipconv(&first);
        }
        else if(execflag) {

            if(!strcmp(first->elem, "(")) {

                status = bracket(first->next);

                first = (*listp);  // Crutch
            }
            else {

                char ** argv = getargv(&first);

                if(fork() == 0) {

                    execvp(argv[0], argv);

                    exit(EXIT_FAILURE);
                }
                wait(&status);
            }
        }
        else skip(&first);

        (*listp) = first;

        if((*listp) && strcmp((*listp)->elem, ")")) {  // Processing status

            if(!strcmp((*listp)->elem, "||")) {

                if(!status) execflag = 0;

                else execflag = 1;
            }
            else if(!strcmp((*listp)->elem, "&&")) {

                if(!status) execflag = 1;

                else execflag = 0;
            }
            else  {  // ; porcessing

                execflag = 1;
            }
        }
        else break;
    }
    return status;
}

int convsize(struct list * List) {

    int size = 1;

    skip(&List);

    while (List && !strcmp(List->elem, "|")) {

        List = List->next; skip(&List); size++;
    }
    return size;
}

int conv(struct list ** listp) {  // | > >> processing

    //printf("%s\n", "conv");

    struct list * first; int size = convsize(*listp), fd[size][2], firstElFlag = 1, i;

    for(i = 0; i < size; i++) {

        pipe(fd[i]);

        if(!firstElFlag) {

            (*listp) = (*listp)->next;
        }
        first = (*listp);

        skip(listp);

        if(fork() == 0) {

            if(!firstElFlag) {

                dup2(fd[i - 1][0], 0); close(fd[i - 1][0]); close(fd[i - 1][1]);
            }
            if((i == size - 1) && (*listp) && (!strcmp((*listp)->elem, ">") || !strcmp((*listp)->elem, ">>"))) {

                int f;

                if(!strcmp((*listp)->elem, ">")) {

                    (*listp) = (*listp)->next;

                    f = open((*listp)->elem, O_WRONLY|O_CREAT, 0666);
                }
                else {

                    (*listp) = (*listp)->next;

                    f = open((*listp)->elem, O_WRONLY|O_CREAT|O_APPEND, 0666);
                }
                dup2(f, 1); close(f);
            }
            else if(i < size - 1) {

                dup2(fd[i][1], 1);
            }
            close(fd[i][0]); close(fd[i][1]);

            if(!strcmp(first->elem, "(")) {

                bracket(first->next); exit(EXIT_SUCCESS);
            }
            else {

                char ** argv = getargv(&first);

                execvp(argv[0], argv);

                exit(EXIT_FAILURE);
            }
        }
        int status; wait(&status); if(!WIFEXITED(status)) return 1;

        if(!firstElFlag) {

            close(fd[i - 1][0]); close(fd[i - 1][1]);
        }
        else firstElFlag = 0;
    }
    if((*listp) && (!strcmp((*listp)->elem, ">") || !strcmp((*listp)->elem, ">>"))) {

        (*listp) = (*listp)->next; skip(listp);
    }
    close(fd[i - 1][0]); close(fd[i - 1][1]);

    return 0;
}

void cd(struct list * List) {  // cd processing

    if(List && (List->next == NULL)) {

        if(!strcmp(List->elem, "~")) {

            chdir("/home");
        }
        else if((chdir(List->elem)) == -1) {

            printf("Error in command cd!");
        }
    }
    else {

        printf("%s\n", "Error: Wrong cd format");
    }
    return;
}

int shl(struct list * List) {

    int mode = 0;

    if(List && check(List, &mode)) {

        if(!strcmp(List->elem, "cd")) cd(List->next);

        else {

            pid_t pid;

            if((pid = fork()) == 0) {

                if(bracket(List)) printf("%s\n", "Error: bad names");

                freelist(List);

                exit(EXIT_SUCCESS);
            }
            else if(!mode) waitpid(pid, NULL, 0);
        }
    }
    freelist(List);

    return 0;
}

int main() {

    struct list * List = NULL;

    while(1) {

        List = getlist();

        //printlist(List);

        shl(List);
    }
    signal(SIGCHLD, SIG_IGN);

    return 0;
}
