//Johnathon Love (jal5622)
//EE461S - Yerraballi
//Project 1 - Header File

/*Inclusions*/
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <malloc.h>
#include <fcntl.h>
#include <errno.h>


/*Structures*/
typedef struct NodeTokens{
	char *token;
	struct NodeTokens *next;
} Node;

typedef struct Pipeline{
	pid_t ProcessID;
	struct Pipeline *next;
	char **argv;

	int stdin;
	int stdout;
	int stderr;

	int bg;

} pipeline_t;

/*Function Headers*/
int createTokenList(char *inputString, Node *head);
void executeCMD(Node *head, int length);
void createArgvArray(int argc, Node* head, char** pointer);
pipeline_t* createPipeline(int argc, char** argv);