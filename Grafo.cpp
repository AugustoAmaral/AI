#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct path{
	struct path* prox;
	int a,b;
}Path;

typedef struct node{
	struct node* prox;
	int id;
	char nome[40];
}Node;

int getNodeId(Node* N, char nome[40]){ 
	if (N == NULL){
		printf("No recebido e nulo.\n");
		return 0;
	}
	if (strcmp(nome,N->nome) == 0)
		return N->id;
	else
		getNodeId(N->prox,nome);
}

void printNode (Node* N){ //FUNFANDO
	printf("No: %s, Id: %d\n",N->nome,N->id);
}

char* getNodeName (Node* N, int id){
	if (N == NULL){
		printf("No recebido e nulo.\n");
		return 0;
	}
	if (N->id == id)
		return N->nome;
	else
		getNodeName(N->prox,id);	
}

void printPath (Node* N, Path* P){
	printf("Path: %s <-> %s\n",getNodeName(N,P->a),getNodeName(N,P->b));
}

void printAllPath (Node* N, Path* P){ //FUNCIONANDO
	if (P == NULL){
		printf("Caminho recebido e nulo.\n");
		exit(0);
	}
	printPath(N,P);
	if (P->prox != NULL)
		printAllPath(N, P->prox);
}

void printAllNode (Node* N){ //FUNFANDO
	if (N == NULL){
		printf("No recebido e nulo.\n");
		exit(0);
	}
	printNode(N);
	if (N->prox != NULL)
		printAllNode(N->prox);
}

Node* f_node (){ //FUNFANDO
	Node* N = (Node*) malloc (sizeof(Node));
	N->id = 0;
	return N;
}

Path* f_path(){
	Path* P = (Path*) malloc (sizeof(Path));
	P->a=0;
	return P;
}

void createPath (Path* P, int a, int b){	
	if (P == NULL){
		printf("No recebido e nulo.\n");
		exit(0);
	}
	if (P->a == 0){
		P->a = a;
		P->b = b;
		P->prox = NULL;	
	}
	else{
		while (P->prox != NULL)
			P = P->prox;
		P->prox = (Path*) malloc (sizeof(Path));
		P->prox->a = a;
		P->prox->b = b;
		P->prox->prox = NULL;
	}
}

void createNode (Node* N, char nome[40]){ //FUNFANDO
	if (N == NULL){
		printf("No recebido e nulo.\n");
		exit(0);
	}
	if (N->id == 0){
		N->prox = NULL;
		strcpy(N->nome,nome);
		N->id = (N->id+1);		
	}
	else{
		while (N->prox != NULL)
			N = N->prox;
		N->prox = (Node*) malloc (sizeof(Node));
		N->prox->prox = NULL;
		strcpy(N->prox->nome,nome);
		N->prox->id = (N->id+1);
	}
}

int main() {
	Node* N = f_node();
	Path* P = f_path();
	
	createNode(N,"Um");
	createNode(N,"Dois");
	createNode(N,"Tres");
	createNode(N,"Quatro");
	createNode(N,"Cinco");
	createPath(P,1,2);
	createPath(P,1,3);
	createPath(P,1,4);
	createPath(P,2,3);
	createPath(P,2,5);
	//printAllNode(N);
	printAllPath(N,P);
	
	
		return 0;
}
