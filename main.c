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

void firstWord(char* add){
	FILE *fp;
	char word[30];
	fp = fopen(add, "r");
	if (fp == NULL) {
    	printf("File not found!\n");
	} else {
    	while (!feof(fp)) {
        	fscanf(fp,"%s%*[^\n]",word);
        	printf("%s\n", word);
        	strcpy(word,"");
    	}
	}
	fclose(fp);
}
void highRepeat(char *add){
	FILE *file;
	char ch, *line;
	size_t len = 0, read;
	char words[1000][1000], word[20];
	int i = 0, j, k, maxCount = 0, count;
	file = fopen(add,"r");

	if (file == NULL){
		printf("File not found");
		exit(EXIT_FAILURE);
	}

	while ((read = getline(&line, &len, file)) != -1) {

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
	fclose(file);
}
void rmSpace(){

}
void nonComment(){

}
void lineCounter(char *add){
	FILE *fp;
	int count = 1;
	char c;
	fp = fopen(add, "r");
	if (fp == NULL){
		printf("Could not open file");
		return 0;
	}

	for (c = getc(fp); c != EOF; c = getc(fp))
		if (c == '\n')
			count = count + 1;

	fclose(fp);
	printf("The file has %d lines\n ", count);

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
		
		if(strcmp(parsed[0],"fw")){
			firstWord(parsed[1]);
		} else if(strcmp(parsed[0],"hr")){
			highRepeat(parsed[1]);
		} else if(strcmp(parsed[0],"rmSpace")){
			
		} else if(strcmp(parsed[0],"nonComment")){
			
		} else if(strcmp(parsed[0],"lc")){
			lineCounter(parsed[1]);
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