//Johnathon Love (jal5622)
//EE461S - Yerraballi
//Project 1 - Source Code

#include "yash.h"



int main(int argc, char *argv[]){
	char inputString[2000 + 1];
	int noOfTok;
	pid_t cpid;

	while(1){	
	    Node *head = (Node *)malloc(sizeof(Node));											
		printf("# ");
		noOfTok = createTokenList(inputString, head);
		char** argv;
		createArgvArray(noOfTok, head, argv);
		cpid = fork();
		if(cpid == 0){
			executeCMD(head, noOfTok);
		}else{
			int status;
			waitpid(cpid, &status, 0);
		}

	}
}



/*
*
*Creates a linked list of all tokens in the input
*And returns the # of tokens
*/
int createTokenList(char *inputString, Node *head){
	int count = 0;
	fgets(inputString, 2001, stdin);
	inputString[strcspn(inputString, "\n")] = 0;
	char *commandTokens = strtok(inputString," \t");
	Node *temp = head;
	while(commandTokens != NULL){
		temp->token = commandTokens;
		commandTokens = strtok(NULL, " \t");
		if(commandTokens != NULL){
			temp->next = (Node *)malloc(sizeof(Node));
		}else{
			temp->next = NULL;
		}
		if(temp->next != NULL){
			temp = temp->next;
		}
	}
	temp = head;
	while(temp != NULL){
		count = count + 1;
		temp = temp->next;
	}
	return count;
}


void executeCMD(Node *head, int length){
	char *argv[length];
	int argc = length;
	Node *temp = head;
	for(int i = 0; i < length; i++){
		argv[i] = temp->token;
		temp = temp->next;
	}

	if(execvp(argv[0], argv) < 0){
		printf("FAILURE: Unable to execute.\n");
		exit(1);
	}

	temp = head->next;
	while(temp != NULL){
		free(head->token);
		free(head);
		head = temp;
		temp = temp->next;
	}
	free(head->token);
	free(head);

}

void createArgvArray(int argc, Node* head, char** pointer){
	char* argv[argc];
	Node* temp = head;
	for(int i = 0; i < argc; i++){
		argv[i] = temp->token;
		temp = temp->next;
	}
	pointer = argv;
}

pipeline_t* createPipeline(int argc, char** argv){
	pipeline_t* job = (pipeline_t *)malloc(sizeof(pipeline_t));
	job->ProcessID = 0;
	job->next = 0;
	job->argv = 0;
	job->stdin = 0;
	job->stdout = 1;
	job->stderr = 2;
	job->bg = 0;

	pipeline_t* temp = job;
	for(int i = 0; i < argc; i++){
		if(strcmp(argv[i], "|") == 0){

		}else if(strcmp(argv[i], "&") == 0){

		}else if(strcmp(argv[i], "<") == 0){

		}else if(strcmp(argv[i], ">") == 0){

		}else if(strcmp(argv[i], "2>") == 0){

		}else if(strcmp(argv[i], "2>&1") == 0){

		}
	}
}