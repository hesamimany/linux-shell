#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<readline/readline.h>
#include<readline/history.h>

#define MAXSTRINGSIZE 1000
#define MAXSTRINGARRAYSIZE 10

void printDir(){
	char cwd[1024];
	getcwd(cwd, sizeof(cwd));
	printf("\nDir: %s", cwd);
}

void parseSpace(char* str, char** parsed){
	int i;
	for (i = 0; i < MAXSTRINGARRAYSIZE; i++) {
		parsed[i] = strsep(&str, " ");

		if (parsed[i] == NULL)
			break;
		if (strlen(parsed[i]) == 0)
			i--;
	}
}

void firstWord(){

}
void highRepeat(){

}
void rmSpace(){

}
void nonComment(){

}
void lineCounter(){

}
void tenLine(){

}

int checkCommand(){

}

void execCommand(char** parsed){
	int check = checkCommand();
	
	pid_t pid = fork();
	printf("after fork, %d, %s ",pid,parsed[0]);
	if (pid == -1) {
		printf("\nFailed forking child..");
		return;
	} else if(pid == 0 && check ==1){
		
		if(strcmp(parsed[0],"firstWord")){
			
		} else if(strcmp(parsed[0],"highRepeat")){

		} else if(strcmp(parsed[0],"rmSpace")){
			
		} else if(strcmp(parsed[0],"nonComment")){
			
		} else if(strcmp(parsed[0],"lineCounter")){
			
		} else if(strcmp(parsed[0],"tenLine")){

		}
		exit(0);
	} else if(pid == 0 && check!=1){
		int status = execvp(parsed[0], parsed);
		if (status < 0) {
			printf("\nCould not execute command..");
		}
		exit(0);
	} else {
		printf("before WAIT, %d ",pid);
		wait(NULL);
		return;
	}
}

int takeInput(char* str){
	char* buf;

	buf = readline("\n>>> ");
	if (strlen(buf) != 0) {
		add_history(buf);
		strcpy(str, buf);
		return 0;
	} else {
		return 1;
	}
}

int processString(char* string, char** parsedString){
	parseSpace(string,parsedString);
	//printf("before exec ");
	execCommand(parsedString);

}

int main(){

    char input[MAXSTRINGSIZE], *argsList[MAXSTRINGARRAYSIZE];

    while (1){
		printDir();
        if(takeInput(input)) continue;
		processString(input,argsList);
    }
    
    return 0;
}