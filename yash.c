//Johnathon Love (jal5622)
//EE461S - Yerraballi
//Project 1 - Source Code

#include "yash.h"
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>


int main(int argc, char *argv[]){
	char inputString[2000 + 1];
	int pipefd[3];
	int noOfTok;
	pid_t cpid;

	while(1){	
	    Node *head = (Node *)malloc(sizeof(Node));											
		printf("# ");
		noOfTok = CreateTokenList(inputString, head);
		cpid = fork();
		if(cpid == 0){
			ExecuteCMD(head, noOfTok);
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
int CreateTokenList(char *inputString, Node *head){
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


void ExecuteCMD(Node *head, int length){
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