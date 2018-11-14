/* 
NESSE ALGORITMO, ESTOU CONSIDERANDO QUE O N� N�O TEM DIRE��O, CASO QUEIRA QUE SEJA DIRECIONADO, VERIFIQUE AONDE TEM COMENTARIO SOBRE ISSO.

AS FUN��ES QUE PERCORREM A ESTRUTURA DE N�S E DE CAMINHOS N�O ALTERAM A VARIAVEL ORIGINAL POIS ELAS S�O RECURSIVAS, OU SEJA,
SE PRECISAREM IR PARA O PROXIMO N�, ELAS V�O SE CHAMAR PASSANDO O PROXIMO N�.


*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

typedef struct path{
	struct path* prox;
	int a,b,id,flag;
}Path;

typedef struct node{
	struct node* prox;
	int id;
	char nome[40];
}Node;

int gotoNode (int, int, Path*, Node*,int = 0); //FLAG VAI COMO PADR�O OCULTO 0

int getNodeId(Node* N, char nome[40]){ //RETORNA O ID DO N� CUJO NOME FOI PASSADO
	if (N == NULL){
		printf("No recebido e nulo.\n");
		return 0;
	}
	if (strcmp(nome,N->nome) == 0)
		return N->id;
	else
		getNodeId(N->prox,nome);
}

void printNode (Node* N){ //PRINTA O N� PASSADO
	printf("No: %s, Id: %d\n",N->nome,N->id);
}

char* getNodeName (Node* N, int id){ // RETORNA O NOME DO N� COM O ID PASSADO
	if (N == NULL){
		printf("No recebido e nulo.\n");
		return 0;
	}
	if (N->id == id)
		return N->nome;
	else
		getNodeName(N->prox,id);	
}

void printPath (Node* N, Path* P){ //PRINTA TO CAMINHO QUE FOI PASSADO E SEU ID
	printf("Path: %s <-> %s, ID: %d\n",getNodeName(N,P->a),getNodeName(N,P->b),P->id);
}

void printAllPath (Node* N, Path* P){ //MOSTRA TODOS OS CAMINHOS DISPONIVEIS
	if (P == NULL){
		printf("Caminho recebido e nulo.\n");
		exit(0);
	}
	printPath(N,P);
	if (P->prox != NULL)
		printAllPath(N, P->prox);
}

void printAllNode (Node* N){ //MOSTRA TODOS OS N�S EXISTENTES
	if (N == NULL){
		printf("No recebido e nulo.\n");
		exit(0);
	}
	printNode(N);
	if (N->prox != NULL)
		printAllNode(N->prox);
}

Node* f_node (){ //INICIA O PRIMEIRO N�
	Node* N = (Node*) malloc (sizeof(Node));
	N->id = 0;
	strcpy(N->nome,"Nenhum no");
	N->prox = NULL;
	return N;
}

Path* f_path(){ //INICIA O PRIMEIRO CAMINHO
	Path* P = (Path*) malloc (sizeof(Path));
	P->a=0;
	P->b=0;
	P->prox=NULL;
	P->id=0;
	P->flag=0;
	return P;
}

void createPath (Path* P, int a, int b){ //CRIA O CAMINHO DE A AT� B
	int temp=0;	
	if (P == NULL){
		printf("No recebido e nulo.\n");
		exit(0);
	}
	if (P->a == 0){
		P->a = a;
		P->b = b;
		P->prox = NULL;
		P->id=0;
		P->flag=0;
	}
	else{
		temp=1;
		while (P->prox != NULL){
			P = P->prox;
			temp++;
		}
		P->prox = (Path*) malloc (sizeof(Path));
		P->prox->a = a;
		P->prox->b = b;
		P->prox->prox = NULL;
		P->prox->id=temp;
		P->prox->flag=0;
	}
}

void createNode (Node* N, char nome[40]){ //CRIA O N� COM O NOME PASSADO
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

int gotoNode (int my_node, int dest_node, Path* P,Node* N,int flag){ //CAMINHA DO N� A AT� O B
	while (P != NULL){
		if (P->a == my_node)
			if (P->b == dest_node){
				if(P->flag==0){
					P->flag=flag;
					printf("O caminho de %s ate %s e possivel, movendo para %s\n",getNodeName(N,my_node),getNodeName(N,dest_node),getNodeName(N,dest_node));
					return dest_node;
				}
				else
					printf("Caminho encontrado, porem o mesmo esta marcado, procurando outro caminho.\n");
			}
		if (P->b == my_node) //CASO O N� SEJA DIRECIONAL, REMOVER ESSA CONDI��O
			if (P->a == dest_node){
				if (P->flag==0){
					P->flag=flag;
					printf("O caminho de %s ate %s e possivel, movendo para %s\n",getNodeName(N,my_node),getNodeName(N,dest_node),getNodeName(N,dest_node));
					return dest_node;
				}
				else
					printf("Caminho encontrado, porem o mesmo esta marcado, procurando outro caminho.\n");
			}
		if ((P->a != my_node) or (P->b != my_node))
			return (gotoNode(my_node,dest_node,P->prox,N,flag));
	}
		printf("O caminho de %s ate %s nao foi possivel.\n",getNodeName(N,my_node),getNodeName(N,dest_node));
		return my_node;
}

void loadPreSet(Node* N,Path* P){
	createNode(N,"piscina");
	createNode(N,"sala de Jogos");
	createNode(N,"quarto de hospedes");
	createNode(N,"bar");
	createNode(N,"dormitorio");
	createNode(N,"dependencia de empregada");
	createNode(N,"adega");
	createNode(N,"cozinha");
	createNode(N,"dispensa");
	createNode(N,"jardim");
	createPath(P,1,10);
	createPath(P,1,10);
	createPath(P,1,9);
	createPath(P,1,8);
	createPath(P,1,3);
	createPath(P,2,3);
	createPath(P,2,3);
	createPath(P,3,4);
	createPath(P,4,5);
	createPath(P,5,6);
	createPath(P,5,6);
	createPath(P,7,8);
	createPath(P,7,8);
	createPath(P,8,9);
	printf("Estrutura carregada.\n");
}

void isEulerian (Node* N,Path* P,int init){
	
	
}


int main() {
	Node* N = f_node();
	Path* P = f_path();
	int me=10; //ID DO N� AONDE COME�O.
	int opt; //OPCOES QUE SER�O LIDAS COMO INTEIRO
	char opt_char[40]; //OPCOES QUE SERAO LIDAS COMO CHAR
	printf("Voce deseja precarregar a estrutura de nos do trabalho?\n1- Sim\n");
	scanf("%d",&opt);
	printf("\n");
	switch (opt){
		case 1:
			loadPreSet(N,P);
			break;
		default:
			printf("Opcao invalida, iniciando programa com estrutura de nos zerada.\n");
	}
	system("pause");
	system("cls");

	
	while (true){
		printf("O que voce quer fazer?\n1- Aonde eu estou?\n2- Ir para (ID).\n3- Ir para (flag).\n4- Mostrar todos os nos\n5- Mostrar todos os caminhos\nDigite a opcao: ");
		scanf("%d",&opt);
		printf("\n");
		switch (opt){
			case 1:
				printf("Eu estou em %s\n",getNodeName(N,me));
				break;
			case 2:
				printf("digite o id do lugar que voce quer ir: ");
				scanf("%d",&opt);
				me = gotoNode(me,opt,P,N);
				printf("\n");
				break;
			case 3:
				printf("digite o id do lugar que voce quer ir: ");
				scanf("%d",&opt);
				me = gotoNode(me,opt,P,N,1);
				printf("\n");
				break;
			case 4:
				printAllNode(N);
				break;
			case 5:
				printAllPath(N,P);
				break;
			default:
				printf("Opcao invalida.\n");
				break;
		}
		system("pause");
		system("cls");
		
	}
		return 0;
}
