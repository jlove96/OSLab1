//Johnathon Love (jal5622)
//EE461S - Yerraballi
//Project 1 - Header File

/*Structures*/
typedef struct NodeTokens{
	char *token;
	struct NodeTokens *next;
} Node;



/*Function Headers*/
int CreateTokenList(char *inputString, Node *head);
void ExecuteCMD(Node *head, int length);