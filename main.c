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
	char* username = getenv("USER");
	printf("\033[22;32m%s@\033[0m:\033[22;34m~%s\033[0m", username, cwd);
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
    	printf("Could not open file");
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
void highRepeat(char *add){
	FILE *fp;
	char ch, *line;
	size_t len = 0, read;
	char words[1000][1000], word[20];
	int i = 0, j, k, maxCount = 0, count;
	fp = fopen(add,"r");

	if (fp == NULL){
		printf("Could not open file");
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
void rmSpace(char *add){
	FILE *input;
	char c,d;
	char p;

	input = fopen(add , "r");
	while((p=getc(input))!=EOF){

		if(p!= 32)
		if(p!= 9)
		if(p!= '\n')
		if(p!= '/' && p!= '*')

	fputc(p,stdout);
	}
	fclose(input);
}
void nonComment(char* add){
	int InComment = 0;
    FILE *fp = fopen(add, "r");
    if(!fp){
        printf("Could not open file");
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
void lineCounter(char *add){
	FILE *fp;
	int count = 1;
	char c;
	fp = fopen(add, "r");
	if (fp == NULL){
		printf("Could not open file");
		return;
	}

	for (c = getc(fp); c != EOF; c = getc(fp))
		if (c == '\n')
			count = count + 1;

	fclose(fp);
	printf("The file has %d lines\n ", count);
}
void tenLine(char* add){
	FILE *fp;
    char content[1000];
    int max = 0;
    fp = fopen(add, "r");
    if (fp == NULL){
        printf("Could not open file");
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
	|| !strcmp(command,"cd")){
		return 1;
	} else return 0;
}

void execCommand(char** parsed){
	int check = checkCommand(parsed[0]);
	pid_t pid = fork();
	if (pid == -1) {
		printf("\nFailed forking child..");
		return;
	} else if(pid == 0 && check){
		
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
		}
		exit(0);
	} else if (pid == 0 && !check){
		int status = execvp(parsed[0], parsed);
		if (status < 0) {
			printf("\nCould not execute command..");
		}
		exit(0);
	} else {
		int cdflag;
		waitpid(pid, &cdflag, 0);
		if (WIFEXITED(cdflag) && WEXITSTATUS(cdflag)==100) chdir(parsed[1]);
		return;
	}
}

int takeInput(char* str){
	char* buf;
	buf = readline("$ ");
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
	//tenLine("/home/hesam/Desktop/myFile.txt");
    
    return 0;
}