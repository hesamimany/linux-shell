#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <setjmp.h>

#define MAXSTRINGSIZE 1000
#define MAXSTRINGARRAYSIZE 10

static sigjmp_buf env; //buffer that keeps program data like stack and ...

typedef void (*sighandler_t)(int);

sighandler_t signal(int signum, sighandler_t handler);

void sigintHandler(int sig_num){ // jumps to the setjmp() location and returns 42 in env
    longjmp(env, 42);
}


void printUsrDir(){ //prints username and current directory
	char cwd[1024];
	getcwd(cwd, sizeof(cwd));
	char* username = getenv("USER");
	printf("\033[22;32m%s@\033[0m:\033[22;34m~%s\033[0m\n", username, cwd);
	//printf("%s@:~%s", username, cwd);
}

void parseSpace(char* str, char** parsed){ //parses str by space and put it in parsed
	int i;
	for (i = 0; i < MAXSTRINGARRAYSIZE; i++) {
		parsed[i] = strsep(&str, " ");

		if (parsed[i] == NULL)
			break;
		if (strlen(parsed[i]) == 0)
			i--;
	}
}

void firstWord(char* add){ // function that opens file in the add address and prints first word in every line
	FILE *fp;
	char word[30];
	fp = fopen(add, "r");
	if (fp == NULL) {
    	fprintf(stderr, "Could not open file\n");
		return;
	} else {
    	while (!feof(fp)) {
        	fscanf(fp,"%s%*[^\n]",word);
        	printf("%s\n", word);
        	strcpy(word,"");
    	}
	}
	fclose(fp);
}
void highRepeat(char *add){ //prints the most repeated word in the file
	FILE *fp;
	char ch, *line;
	size_t len = 0, read;
	char words[1000][1000], word[20];
	int i = 0, j, k, maxCount = 0, count;
	fp = fopen(add,"r");

	if (fp == NULL){
		fprintf(stderr, "Could not open file\n");
		return;
	}

	while ((read = getline(&line, &len, fp)) != -1) {

		for(k=0; line[k]!='\0'; k++){
			
			if(line[k] != ' ' && line[k] != '\n' && line[k] != ',' && line[k] != '.' ){
				words[i][j++] = tolower(line[k]);
			}else{
				words[i][j] = '\0';
				i++;
				j = 0;
			}
		}
	}

	int length = i;
	for(i = 0; i < length; i++){
		count = 1;
		for(j = i+1; j < length; j++){
			if(strcmp(words[i], words[j]) == 0 && (strcmp(words[i]," ") != 0)){
				count++;
			}
		}
		if(count > maxCount){
			maxCount = count;
			strcpy(word, words[i]);
		}
	}

	printf("Most repeated word: %s", word);
	fclose(fp);
}
void rmSpace(char *add){ //pritns a file with whitespace removed 
	FILE *fp;
	char c,d;
	char p;

	fp = fopen(add , "r");
	if(!fp){
        fprintf(stderr, "Could not open file\n");
		return;
    }
	while((p=getc(fp))!=EOF){
		if(p!= 32)
			if(p!= 9)
				if(p!= '\n')
					if(p!= '/' && p!= '*')
						fputc(p,stdout);
	}
	fclose(fp);
}
void nonComment(char* add){
	int InComment = 0;
    FILE *fp = fopen(add, "r");
    if(!fp){
        fprintf(stderr, "Could not open file\n");
		return;
    }
    int ch;
    while((ch = fgetc(fp)) != EOF){
        if(ch == '#'){
            InComment = 1;
        } else if (ch == '\n'){
            InComment = 0;
            fputc(ch, stdout);
        }
        else if(!InComment){
            fputc(ch, stdout);
        }
    }
    fclose(fp);
}
void lineCounter(char *add){ // counts number of lines in a file
	FILE *fp;
	int count = 1;
	char c;
	fp = fopen(add, "r");
	if (fp == NULL){
		fprintf(stderr, "Could not open file\n");
		return;
	}

	for (c = getc(fp); c != EOF; c = getc(fp))
		if (c == '\n')
			count = count + 1;

	fclose(fp);
	printf("The file has %d lines\n ", count);
}
void tenLine(char* add){ // prints first ten line in a file
	FILE *fp;
    char content[1000];
    int max = 0;
    fp = fopen(add, "r");
    if (fp == NULL){
        fprintf(stderr, "Could not open file\n");
		return;
    }
    fgets(content, 1000, fp);
    while (content != NULL){
        max++;
        if (max > 10)
            break;
        printf("%s", content);
        fgets(content, 1000, fp);
    }

    fclose(fp);
    return;
}

int checkCommand(char* command){ // return 1 if command is part of our commands
	if(!strcmp(command,"fw") || !strcmp(command,"hr") || !strcmp(command,"rs")
	|| !strcmp(command,"nc") || !strcmp(command,"lc") || !strcmp(command,"tl")
	|| !strcmp(command,"cd") || !strcmp(command,"exit")){
		return 1;
	} else return 0;
}

void execCommand(char** parsed){ //executes the given command in parsed string array
	int check = checkCommand(parsed[0]); //check if the command is ours or not
	pid_t pid = fork(); //fork a child
	
	if (pid == -1) {
		fprintf(stderr, "Failed forking child..\n");
		return;

	} else if(pid == 0 && check){ // our commands
		if(!strcmp(parsed[0], "fw")){
			firstWord(parsed[1]);
		} else if(!strcmp(parsed[0], "hr")){
			highRepeat(parsed[1]);
		} else if(!strcmp(parsed[0], "rs")){
			rmSpace(parsed[1]);
		} else if(!strcmp(parsed[0], "nc")){
			nonComment(parsed[1]);
		} else if(!strcmp(parsed[0], "lc")){
			lineCounter(parsed[1]);
		} else if(!strcmp(parsed[0], "tl")){
			tenLine(parsed[1]);
		} else if(!strcmp(parsed[0], "cd")){
			exit(100);
		} else if(!strcmp(parsed[0], "exit")){
			exit(101);
		}
		exit(0);
	} else if (pid == 0 && !check){ // terminal commands
		int status = execvp(parsed[0], parsed);
		if (status < 0) {
			fprintf(stderr, "Could not execute command..\n");
		}
		exit(0);
	} else { //parent waits here
		int cdflag;
		waitpid(pid, &cdflag, 0);
		if (WIFEXITED(cdflag) && WEXITSTATUS(cdflag)==100) chdir(parsed[1]); // runs if we have cd command
		if (WIFEXITED(cdflag) && WEXITSTATUS(cdflag)==101){
			write_history("./history.txt");
			exit(0);
		} // runs if we enter exit command
		return;
	}
}

int takeInput(char* str){ // read a line from user
	char* buf;
	buf = readline("$ ");
	if (strlen(buf) != 0) {
		add_history(buf); // add entered command to history
		write_history("./history.txt"); // write entered commands to file
		strcpy(str, buf);
		return 0;
	} else {
		return 1;
	}
}

int processString(char* string, char** parsedString){ // process given line
	parseSpace(string,parsedString);
	execCommand(parsedString);
}

int main(){

    char input[MAXSTRINGSIZE], *argsList[MAXSTRINGARRAYSIZE]; // input is a string that keeps the one lie command and argslist is the parsed input by space

	signal(SIGINT, sigintHandler); // calls sigintHandler() when ctrl + c is pressed
	system("clear"); // clears terminal
	read_history("./history.txt"); //raed history from file
    while (1){ // inf loop
		if (sigsetjmp(env, 1) == 42) { // jump here whenever ctrl + c is pressed
            printf("\n");
        }

		printUsrDir(); //prints the current directory and username
        if(takeInput(input)) continue; // read a line
		processString(input,argsList); // pass the read line for process
    }
    
    return 0;
}